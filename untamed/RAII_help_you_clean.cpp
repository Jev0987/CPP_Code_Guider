/*
 * @Descripttion: 使用 RAII 来帮助你退出时设置状态位
 * @Author: jev
 * @Date: 2025-11-26
 */
#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

class RAIIClean {
public:
    explicit RAIIClean(std::function<void()> cleanup)
        : cleanup_(cleanup) {}
    ~RAIIClean() {
        if (cleanup_) cleanup_();
    }

    RAIIClean(const RAIIClean&) = delete;
    RAIIClean& operator=(const RAIIClean&) = delete;

private:
    std::function<void()> cleanup_;
};

// 程序正在运行标志
std::atomic<bool> process_flag(false);

void user_function() {
    RAIIClean raii_clean([&]() { process_flag.store(false); });
    process_flag.store(true);

    // mission 1
    int sum = 0;
    for (int i = 0; i < 1000000; ++i) {
        sum += i;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // mission 2
    int product = 1;
    for (int i = 1; i <= 1000000; ++i) {
        product *= i;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // 函数退出后，程序运行标志为置为false
}

int main() {

    std::thread t1(user_function);

    t1.join();

    return 0;
}