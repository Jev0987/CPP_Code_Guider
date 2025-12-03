/*
 * @Descripttion: 
 * @Author: jev
 * @Date: 2025-12-03
 */
#include "shared_memory.hpp"
#include <iostream>

int main() {
    constexpr char SHM_NAME[] = "/my_shm_demo";
    constexpr size_t SHM_SIZE = 1024;

    try {
        SharedMemory shm(SHM_NAME, SHM_SIZE, false);

        const char* data = static_cast<const char*>(shm.data());
        std::cout << "Reader received: " << data << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Reader error: " << e.what() << '\n';
    }

    return 0;
}
