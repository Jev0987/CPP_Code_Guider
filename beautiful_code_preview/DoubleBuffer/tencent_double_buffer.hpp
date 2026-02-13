/*
 * @Descripttion: 腾讯版本db，单写多读 (SWMR)
 * @Author: jev
 * @Date: 2026-02-12
 */
#include <memory>

namespace jev_beauty_code {
template <typename T>
class DoubleBuffer {
public:
    DoubleBuffer() {
        buffers_[0] = std::make_shared<T>();
        buffers_[1] = std::make_shared<T>();
    }

    /**
     * 更新 backup 后台的 buffer 数据，并进行切换
     * @param new_value
     */
    void UpdateAndSwap(const T& new_value) {
        auto t = std::make_shared<T>(new_value);
        UpdateAndSwap(t);
    }

    /**
     * 更新 backup 后台的 buffer 数据，并进行切换
     * @param new_value
     */
    void UpdateAndSwap(const std::shared_ptr<T>& new_value) {
        // Update backup.
        buffers_[!index_] = new_value;
        Swap();
    }

    /**
     * 更新 current/backup 前后后台的 buffer 数据
     * @param new_value
     */
    void UpdateAll(const T& new_value) {
        auto t = std::make_shared<T>(new_value);
        UpdateAll(t);
    }

    /**
     * 更新 current/backup 前后后台的 buffer 数据
     * @param new_value
     */
    void UpdateAll(const std::shared_ptr<T>& new_value) {
        // Update backup.
        buffers_[!index_] = new_value;
        // Update current.
        buffers_[index_] = new_value;
    }

    /**
     * 获取前台buffer数据
     * @return 前台buffer智能指针
     */
    std::shared_ptr<T> GetCurrent() { return buffers_[index_]; }

    /**
     * 获取后台buffer数据
     * @return 后台buffer智能指针
     */
    std::shared_ptr<T> GetBackup() { return buffers_[!index_]; }

    /**
     * 进行 buffer 切换
     */
    void Swap() { index_ = !index_; }

    /**
     * 获取当前切换的值
     * @return
     */
    uint32_t Index() { return index_; }

private:
    // 存储双buffer的两份数据
    std::shared_ptr<T> buffers_[2] = {nullptr, nullptr};

    // 双buffer下标切换计数器
    volatile uint32_t index_ = 0;
};
}  // namespace jev_beauty_code