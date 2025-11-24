/*
 * @Descripttion: 交替打印ABC2
 * @Author: jev
 * @Date: 2025-06-30
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

const int max_count = 10;
int state = 0;

void printData(std::mutex &cur_mtx, std::condition_variable &cv, int target_state, int next_state, char c) {
    for (int i = 0; i < max_count; ++i) {
        std::unique_lock<std::mutex> lck(cur_mtx);

        cv.wait(lck, [target_state]() {return state == target_state; });

        std::cout << c;

        state = next_state;

        if (c == 'C') {
            std::cout << std::endl;
        }

        cv.notify_all();
    }
}

void demo_thread_print_ABC2() {
    std::mutex mtx;
    std::condition_variable cv;

    std::thread t1(printData, std::ref(mtx), std::ref(cv), 0, 1, 'A');
    std::thread t2(printData, std::ref(mtx), std::ref(cv), 1, 2, 'B');
    std::thread t3(printData, std::ref(mtx), std::ref(cv), 2, 0, 'C');

    t1.join();
    t2.join();
    t3.join();
}

int main() {
    demo_thread_print_ABC2();
    return 0;
}