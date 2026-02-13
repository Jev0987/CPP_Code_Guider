/*
 * @Descripttion:  AI帮我生成的无锁双缓冲队列。单生产者、单消费者
 * @Author: jev
 * @Date: 2026-02-12
 */
#include <atomic>
#include <vector>

namespace jev_beauty_code {
template <typename T>
class LockFreeDoubleBuffer {
public:
    LockFreeDoubleBuffer() {
        // 初始化三个缓冲区：
        // 1. 生产者正在写
        write_buffer_ = new std::vector<T>();
        write_buffer_->reserve(1024);

        // 2. 消费者正在读
        read_buffer_ = new std::vector<T>();
        read_buffer_->reserve(1024);

        // 3. 交换区
        shared_buffer_.store(new std::vector<T>());
    }

    ~LockFreeDoubleBuffer() {
        // 清理缓冲区
        delete write_buffer_;
        delete read_buffer_;
        delete shared_buffer_;
    }

    // 生产者线程调用
    void push(const T& item) {
        // 1. 往 write buffer 里写，无锁
        write_buffer_->push_back(item);
    }

    /**
     * @brief 提交数据（Publish）
     * 将当前写满的 buffer 挂到共享区，并换回一个空的（或者旧的）buffer 继续写
     */
    void commit() {
        // atomic_exchange:
        // 1. 把 write_buffer_（满的） 放入交换区 shared_buffer_
        // 2. 把 shared_buffer_ 原来的值（可能是空的，也可能是消费者刚还回来的）拿出来赋值给
        // write_buffer_
        write_buffer_ = shared_buffer_.exchange(write_buffer_, std::memory_order_acq_rel);

        // 拿回的 buffer 可能是脏的（上次消费者用过的），需要清理以便下次写入
        // 注意：clear() 只重置size，不释放 capacity, 效率很高
        write_buffer_->clear();
    }

    // 消费者线程使用
    /**
     * @brief 获取数据
     * 尝试从共享区拿数据到私有 read buffer
     * @return bool 是否拿到了新数据
     */
    bool fetch() {
        // 1. 如果当前的 read buffer 还没处理完，继续处理，不需要去拿新的
        if (!read_buffer_->empty()) { return true; }

        // 2. 尝试交换： 空的 buffer 去换共享区的 buffer
        // 这里有一个假设：共享区里一定有生产者提交的数据吗？不一定。
        // 如果生产者还没 commit，我们换回来的可能是一个空 buffer。
        read_buffer_ = shared_buffer_.exchange(read_buffer_, std::memory_order_acq_rel);

        // 3. 检查换回来的是不是空的
        return !read_buffer_->empty();
    }

    // 消费者处理数据的接口
    T* front() {
        if (read_buffer_->empty()) return nullptr;

        return &(*read_buffer_)[0];
    }

private:
    // 生产者私有指针（无需原子）
    std::vector<T>* write_buffer_;

    // 消费者私有指针（无需原子）
    std::vector<T>* read_buffer_;

    // 核心：共享的原子指针
    std::atomic<std::vector<T>*> shared_buffer_;
};
}  // namespace jev_beauty_code