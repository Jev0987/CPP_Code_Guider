/*
 * @Descripttion:
 * @Author: jev
 * @Date: 2026-02-25
 */
#include <cstdio>
#include <filesystem>  // c++17
#include <fstream>
#include <sys/stat.h>

#include <iostream>

// 性能最差
void using_fstream_to_check(const std::string& path) {
    std::ifstream file{path};
    if (file.good()) {
        std::cout << "using fstream check file exist, file path: " << path << " exist" << std::endl;
        file.close();
    }
}

void using_filesystem_to_check(const std::string& path) {
    std::filesystem::path p{path};
    if (std::filesystem::exists(p)) {
        std::printf("using filesystem to check file exist, file path: %s exist", path.c_str());

        if (std::filesystem::is_regular_file(p)) {
            std::printf("它是一个普通的文件");
        } else if (std::filesystem::is_directory(p)) {
            std::printf("它是一个文件夹");
        }
    }
}

void using_stat_to_check(const std::string& path) {
    struct stat buffer;
    // stat() 返回 0 表示成功读取状态，说明文件/目录存在
    if (stat(path.c_str(), &buffer) == 0) {
        std::cout << "路径存在: " << path << std::endl;

        // 区分文件和目录的宏
        if (S_ISDIR(buffer.st_mode)) {
            std::cout << " -> 这是一个文件夹。" << std::endl;
        } else if (S_ISREG(buffer.st_mode)) {
            std::cout << " -> 这是一个普通文件。" << std::endl;
            std::cout << " -> 文件大小: " << buffer.st_size << " bytes" << std::endl;
        }
    } else {
        std::cout << "路径不存在: " << path << std::endl;
    }
}

// 跨平台处理头文件
#ifdef _WIN32
#include <io.h>
#define access _access
#define F_OK 0  // Windows 下 0 表示检查存在性
#else
#include <unistd.h>
#endif
// 性能最快
void using_access_to_check(const std::string& path) {
    // F_OK 用于检查文件是否存在
    // 还可以用 R_OK(可读), W_OK(可写), X_OK(可执行)
    if (access(path.c_str(), F_OK) == 0) {
        std::cout << "路径存在: " << path << std::endl;
    } else {
        std::cout << "路径不存在: " << path << std::endl;
    }
}

int main() {
    std::string path = "";

    return 0;
}