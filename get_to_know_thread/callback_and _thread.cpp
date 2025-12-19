/*
 * @Descripttion:  一个小demo，验证一下回调调用时，类如果在析构会发生什么
 * @Author: jev
 * @Date: 2025-12-19
 */
#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <ratio>
#include <thread>

// 工作中遇到的问题
// 如果类中注册了回调，回调在另一个线程执行
// 回调会使用类中的资源
// 此时如果发生析构，会发生什么
// 然而并没有崩溃。。。
class CallBackObj {
    using CallBackType = std::function<void(std::shared_ptr<int>)>;

public:
    CallBackObj(int num) { resource_ = std::make_shared<int>(num); }
    void resgiterCallback(CallBackType callback) { callback_ = callback; }
    void unregiterCallback() { callback_ = nullptr; }
    void stop() {
        run_.store(false);
        if (data_handler_thread_ && data_handler_thread_->joinable()) {
            data_handler_thread_->join();
        }
        data_handler_thread_.reset();
    }
    ~CallBackObj() {
        stop();
        callback_ = nullptr;
    }

    void run() {
        stop();
        run_.store(true);
        if (!data_handler_thread_) {
            data_handler_thread_ = std::make_shared<std::thread>([&]() {
                while (run_.load()) {
                    plus_num(resource_);

                    if (callback_) { callback_(resource_); }

                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            });
        }
    }

    void plus_num(std::shared_ptr<int> num) { (*num)++; }

private:
    std::shared_ptr<int> resource_;
    std::shared_ptr<std::thread> data_handler_thread_;
    CallBackType callback_;
    std::atomic<bool> run_{false};
};

void getData(std::shared_ptr<int> num) {
    std::cout << "[getData] current num is: " << *num << std::endl;
}

int main() {

    // 创建对象，初始化资源
    std::shared_ptr<CallBackObj> obj = std::make_shared<CallBackObj>(0);

    // 注册回调
    obj->resgiterCallback([&](std::shared_ptr<int> num) { getData(num); });

    // 运行回调
    obj->run();

    // 等待执行
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // 主动执行析构
    obj.reset();

    return 0;
}