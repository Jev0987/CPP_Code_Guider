/*
 * @Descripttion: 条件变量使用
 * @Author: jev
 * @Date: 2025-06-25
 */
#include <thread>
#include <iostream>
#include <condition_variable>
#include <mutex>

using namespace std;

void waitting_thread(mutex &cur_mtx, condition_variable &cv, bool &ready) {
    unique_lock<mutex> lck(cur_mtx);

//     cv.wait(lck, predicate) 时，如果 predicate 为 false，线程会自动解锁 lck 并进入等待状态。
//     其他线程可以通过 cv.notify_one() 或 cv.notify_all() 唤醒等待的线程。
//     被唤醒后，线程会重新加锁 lck，并再次检查 predicate。
//     只有当 predicate 返回 true 时，wait 才会返回，线程继续执行后续代码
    cv.wait(lck, [&]() {return ready;});

    cout << "get condition variable, doing something..." << endl;
}

void notify_thread(mutex &cur_mtx, condition_variable &cv, bool &ready) {
    
    {
        unique_lock<mutex> lck(cur_mtx);
        cout << "get mutex, change state" << endl;
        ready = true;
        lck.unlock();
    }

    cv.notify_all();
}

void demo_condition_variable() {
    mutex mtx;
    condition_variable cv;
    bool ready = false;
    thread t1(waitting_thread, std::ref(mtx), std::ref(cv), std::ref(ready));
    thread t2(notify_thread, std::ref(mtx), std::ref(cv), std::ref(ready));

    t1.join();
    t2.join();
}

int main() {
    demo_condition_variable();
    return 0;
}