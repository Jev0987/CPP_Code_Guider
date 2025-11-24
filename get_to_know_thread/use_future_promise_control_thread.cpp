/*
 * @Descripttion: 普通线程 std::thread，使用future promise 简单示例
 * @Author: jev
 * @version: 
 * @Date: 2025-02-22
 * @LastEditors: jev
 * @LastEditTime: 2025-02-22
 */

#include <iostream>
#include <future>
#include <chrono>
#include <thread>

// 异步，将结果通过promise传递
void onAdd(std::promise<int> p, int a, int b) {
    p.set_value(a + b);
}

void demo_future_promise() {
    std::cout << __func__ << std::endl;
    // “承诺”，在某个时刻会提供一个值或者异常
    std::promise<int> promise_;

    // 用来获取这个值的 “未来对象”
    std::future<int> future_ = promise_.get_future();

    // 新线程调用onAdd函数，将promise_作为参数传递
    std::thread t(onAdd, std::move(promise_), 1, 2);

    // 主线程通过future_获取结果
    std::cout << "future get: " << future_.get() << std::endl;

    // 等待子线程结束
    t.join();
}

int main() {
    demo_future_promise();
    return 0;
}