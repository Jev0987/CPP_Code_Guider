/*
 * @Descripttion: 生产者消费者模型-条件变量和锁
 * @Author: jev
 * @Date: 2025-06-27
 */
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>

std::queue<int> products;
int max_size = 10;
size_t product_num = 0;
std::mutex mtx;
std::condition_variable cv;
bool done = false;

void producer() {
    while (true) {
        std::unique_lock<std::mutex> lck(mtx);

        if (product_num >= max_size) {
            done = true;
            cv.notify_all(); // 通知消费者退出
            break;
        }

        products.push(product_num + 1);
        product_num += 1;

        cv.notify_all();
    }
    std::cout << "producer done." << std::endl;

}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lck(mtx);

        // 等待有产品可消费或生产结束
        cv.wait(lck, [&]() {
            return product_num > 0 || done;
        });

        if (products.empty() && done) {
            // 所有产品已消费且生产结束
            break;
        }

        if (!products.empty()) {
            int ans = products.front();
            products.pop();
            product_num -= 1;
            std::cout << ans << std::endl;
        }
    }
    std::cout << "consumer done." << std::endl;
}

void demo_producer_consumer_mtx_cv() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
    return;
}

int main() {
    demo_producer_consumer_mtx_cv();
    return 0;
}