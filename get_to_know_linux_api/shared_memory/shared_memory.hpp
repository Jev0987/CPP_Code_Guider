/*
 * @Descripttion: 共享内存类
 * @Author: jev
 * @Date: 2025-12-03
 */
#pragma once
#include <string>
#include <stdexcept>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

class SharedMemory {
public:
    SharedMemory(const std::string& name, size_t size, bool create)
        : name_(name), size_(size)
    {
        int flags = create ? (O_CREAT | O_RDWR) : O_RDWR;
        fd_ = shm_open(name_.c_str(), flags, 0666);
        if (fd_ == -1) {
            throw std::runtime_error("Failed to open shared memory");
        }

        if (create) {
            if (ftruncate(fd_, size_) == -1) {
                throw std::runtime_error("Failed to resize shared memory");
            }
        }

        ptr_ = mmap(nullptr, size_, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
        if (ptr_ == MAP_FAILED) {
            throw std::runtime_error("Failed to mmap shared memory");
        }
    }

    ~SharedMemory() {
        if (ptr_) munmap(ptr_, size_);
        if (fd_ != -1) close(fd_);
        // 这个demo中，读写在不同的进程（会结束），如果shm_unlink 后，会导致读失败
        // shm_unlink(name_.c_str());
    }

    void* data() { return ptr_; }

private:
    std::string name_;
    size_t size_;
    int fd_{-1};
    void* ptr_{nullptr};
};
