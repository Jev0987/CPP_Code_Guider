/*
 * @Descripttion: 最常见的单例模式
 * @Author: jev
 * @Date: 2025-07-22
 */
#include <iostream>

class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;  // 局部静态变量，确保线程安全
        return instance;
    }

    void doSomething() {
        std::cout << "print some words" << std::endl;
    }

    // Singleton(const Singleton &other)


private:
    Singleton() {
        std::cout << "Singleton instance created!" << std::endl;
    }

    ~Singleton() {
        std::cout << "Singleton instance destoryed!" << std::endl;
    }

};