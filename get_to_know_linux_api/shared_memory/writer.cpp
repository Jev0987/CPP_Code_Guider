/*
 * @Descripttion: 
 * @Author: jev
 * @Date: 2025-12-03
 */
#include "shared_memory.hpp"
#include <cstring>
#include <iostream>

int main() {
    constexpr char SHM_NAME[] = "/my_shm_demo";
    constexpr size_t SHM_SIZE = 1024;

    try {
        SharedMemory shm(SHM_NAME, SHM_SIZE, true);

        const char* message = "Hello from shared memory!";
        std::memcpy(shm.data(), message, std::strlen(message) + 1);

        std::cout << "Writer: message written.\n";
    } catch (const std::exception& e) {
        std::cerr << "Writer error: " << e.what() << '\n';
    }

    return 0;
}
