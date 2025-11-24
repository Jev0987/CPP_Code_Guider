/*
 * @Descripttion: fastdds里日志模块用到的双缓冲队列, 适配 MPSC(多生产者,单个消费者) 场景
 * @Author: zhanjiewen
 * @Date: 2025-09-25
 * @LastEditors: zhanjiewen
 * @LastEditTime: 2025-09-25
 */
#include <mutex>
#include <queue>

namespace jev_beauty_code {
template <class T>
class DBQueue {
   public:
    DBQueue() : mFrontQueue(&mAphaQueue), mBackQueue(&mBetaQueue) {}
    ~DBQueue() {}

    void swap() {
        std::unique_lock<std::mutex> frontlck(mFrontQMtx);
        std::unique_lock<std::mutex> backlck(mBackQMtx);

        std::queue<T>().swap(*mFrontQueue);

        // 小细节, auto *
        auto *swap = mBackQueue;
        mBackQueue = mFrontQueue;
        mFrontQueue = swap;
    }

    void pop() {
        std::unique_lock<std::mutex> frontlck(mFrontQMtx);
        mFrontQueue->pop();
    }

    void push(cosnt T &item) {
        std::unique_lock<std::mutex> backlck(mBackQMtx);
        mBackQueue->push(item);
    }

    T &front() {
        std::unique_lock<std::mutex> frontlck(mFrontQMtx);
        return mFrontQueue->front();
    }

    const T &front() {
        std::unique_lock<std::mutex> frontlck(mFrontQMtx);
        return mFrontQueue->front();
    }

    size_t size() const {
        std::unique_lock<std::mutex> frontlck(mFrontQMtx);
        return mFrontQueue->size();
    }

    void clear() {
        std::unique_lock<std::mutex> frontlck(mFrontQMtx);
        std::unique_lock<std::mutex> backlck(mBackQMtx);

        std::queue<T>().swap(*mFrontQueue);
        std::queue<T>().swap(*mBackQueue);
    }

    bool Empty() const {
        std::unique_lock<std::mutex> frontlck(mFrontQMtx);
        return mFrontQueue->empty();
    }

    bool BothEmpty() const {
        std::unique_lock<std::mutex> frontlck(mFrontQMtx);
        std::unique_lock<std::mutex> backlck(mBackQMtx);

        return mFrontQueue->empty() && mBackQueue->empty();
    }

   private:
    // 实际队列数据
    std::queue<T> mAphaQueue;
    std::queue<T> mBetaQueue;

    std::queue<T> *mFrontQueue;  // 前置队列指针, 提供给消费者使用
    std::queue<T> *mBackQueue;   // 后置队列指针, 提供给生产者使用

    mutable std::mutex mFrontQMtx;
    mutable std::mutex mBackQMtx;
};
}  // namespace jev_beauty_code