/*
 * @Descripttion: fastdds里日志模块用到的双缓冲队列, 适配 MPSC(多生产者,单个消费者) 场景
 * @Author: zhanjiewen
 * @Date: 2025-09-25
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2026-02-12
 */
#include <mutex>
#include <queue>

namespace jev_beauty_code {
template <class T>
class DBQueue {
public:
    DBQueue()
        : mFrontQueue(&mAphaQueue)
        , mBackQueue(&mBetaQueue) {}
    ~DBQueue() {}

    // 禁用拷贝构造和赋值，防止锁被错误拷贝
    DBQueue(const DBQueue&) = delete;
    DBQueue& operator=(const DBQueue&) = delete;

    void swap() {
        std::unique_lock<std::mutex> frontlck(mFrontQMtx);
        std::unique_lock<std::mutex> backlck(mBackQMtx);

        std::queue<T>().swap(*mFrontQueue);

        // 小细节, auto *
        auto* swap = mBackQueue;
        mBackQueue = mFrontQueue;
        mFrontQueue = swap;
    }

    void pop() {
        std::unique_lock<std::mutex> frontlck(mFrontQMtx);
        mFrontQueue->pop();
    }

    /**
     * @brief 生产者：只往 BackQueue 写数据
     * 只需要锁住 Back 锁，不影响正在读 Front 的消费者
     */
    void push(const T& item) {
        std::unique_lock<std::mutex> backlck(mBackQMtx);
        mBackQueue->push(item);
    }

    T& front() {
        std::unique_lock<std::mutex> frontlck(mFrontQMtx);
        return mFrontQueue->front();
    }

    const T& front() {
        std::unique_lock<std::mutex> frontlck(mFrontQMtx);
        return mFrontQueue->front();
    }

    T front_copy() {
        std::unique_lock<std::mutex> frontlck(mFrontQMtx);
        return mFrontQueue->front();
    }

    /**
     * @brief 获取当前积压的总大小 (大概值)
     */
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

    /**
     * @brief 判断是否全空
     */
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

    std::queue<T>* mFrontQueue;  // 前置队列指针, 提供给消费者使用
    std::queue<T>* mBackQueue;   // 后置队列指针, 提供给生产者使用

    mutable std::mutex mFrontQMtx;
    mutable std::mutex mBackQMtx;
};
}  // namespace jev_beauty_code