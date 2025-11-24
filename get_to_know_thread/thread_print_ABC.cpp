/*
 * @Descripttion: 多线程交替打印ABC
 * @Author: jev
 * @Date: 2025-06-25
 */
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
int state = 0;  // 0 for A, 1 for B, 2 for C

void printA(int max_count) {
    for (int i = 0; i < max_count; ++i) {
        std::unique_lock<std::mutex> lck(mtx);

        // state == 0 拿锁，往下执行，否则解锁，直接返回（减少资源占用）
        cv.wait(lck, [] { return state == 0; });
        std::cout << "A";
        state = 1;
        lck.unlock();
        cv.notify_all();
    }
}

void printB(int max_count) {
    for (int i = 0; i < max_count; ++i) {
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, [] { return state == 1; });
        std::cout << "B";
        state = 2;
        lck.unlock();
        cv.notify_all();
    }
}

void printC(int max_count) {
    for (int i = 0; i < max_count; ++i) {
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, [] { return state == 2; });
        std::cout << "C";
        state = 0;
        std::cout << std::endl;  // 换行以便观察循环
        lck.unlock();
        cv.notify_all();
    }
}

void demo_mutil_thread_print() {
    int max_count = 10;  // 打印10组ABC

    std::thread t1(printA, max_count);
    std::thread t2(printB, max_count);
    std::thread t3(printC, max_count);

    t1.join();
    t2.join();
    t3.join();
}

int main() {
    demo_mutil_thread_print();
    return 0;
}