/*
 * @Descripttion: 利用智能指针实现资源管理缓存类
 * @Author: zhanjiewen
 * @Date: 2025-10-20
 * @LastEditors: zhanjiewen
 * @LastEditTime: 2025-10-20
 */
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
class Resource {
   public:
    Resource() : data_(1024, 'A') {}  // 初始化一些数据
    ~Resource() { std::cout << "Resource destroyed\n"; }

   private:
    std::vector<char> data_;
};

class Cache {
   public:
    std::shared_ptr<Resource> get(int key) {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            auto resource = it->second.lock();
            if (resource) {
                std::cout << "Cache hit for key: " << key << std::endl;
                return resource;
            } else {
                // 资源已被销毁，从缓存中移除
                cache_.erase(it);
                std::cout << "Resource expired for key: " << key << std::endl;
            }
        }
        std::cout << "Cache miss for key: " << key << std::endl;
        return nullptr;
    }

    void store(int key, std::shared_ptr<Resource> res) {
        cache_[key] = res;
        std::cout << "Stored resource for key: " << key << std::endl;
    }

    size_t size() const { return cache_.size(); }

   private:
    std::unordered_map<int, std::weak_ptr<Resource>> cache_;
};

// 测试函数
void test_cache() {
    Cache cache;

    // 创建资源并存储
    auto res1 = std::make_shared<Resource>();
    auto res2 = std::make_shared<Resource>();

    cache.store(1, res1);
    cache.store(2, res2);

    std::cout << "Cache size: " << cache.size() << std::endl;

    // 测试缓存命中
    auto retrieved = cache.get(1);
    if (retrieved) {
        std::cout << "Successfully retrieved resource 1" << std::endl;
    }

    // 释放一个资源
    res1.reset();
    std::cout << "Released resource 1" << std::endl;

    // 尝试获取已释放的资源
    auto expired = cache.get(1);
    if (!expired) {
        std::cout << "Resource 1 is no longer available" << std::endl;
    }

    std::cout << "Final cache size: " << cache.size() << std::endl;
}

int main() {
    test_cache();
    return 0;
}