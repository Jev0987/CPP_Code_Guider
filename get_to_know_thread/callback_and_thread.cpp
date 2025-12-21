/*
 * @Descripttion: 类中的回调和线程资源问题
 * @Author: jev
 * @Date: 2025-12-19
 */
#include <functional>
#include <iostream>
#include <memory>
#include <thread>
// 对象释放时，回调中带有参数[&] 会出现崩溃吗？
// 写个demo验证一下

class CallBackObject {
    using CallBackType = std::function<void(const std::shared_ptr<int>&)>;

public:
    CallBackObject(CallBackType callback)
        : callback_(callback) {
        resource_ = std::make_shared<int>(1);
        std::cout << "callback object construction" << std::endl;
    }

    ~CallBackObject() { callback_ = nullptr; }

private:
    CallBackType callback_;
    std::shared_ptr<int> resource_;
};

int main() { return 0; }