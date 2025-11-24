/*
 * @Descripttion: 枚举总是忘记， 打印看看枚举类和普通枚举的差别
 * @Author: jev
 * @Date: 2025-06-18
 */

#include <iostream>

// 枚举类
enum class Flag { Start, Processing, End };

// 普通枚举
enum Flag2 { Start, Processing, End };

void demo_use_enum() {
    // 打印枚举类
    std::cout << "enum class value: " << std::endl;
    std::cout << "Flag::Start = " << static_cast<int>(Flag::Start) << std::endl;
    std::cout << "Flag::Processing = " << static_cast<int>(Flag::Processing) << std::endl;
    std::cout << "Flag::End = " << static_cast<int>(Flag::End) << std::endl;

    // 打印普通枚举
    std::cout << "\nnormal enum value: " << std::endl;
    std::cout << "Start = " << Start << std::endl;
    std::cout << "Processing = " << Processing << std::endl;
    std::cout << "End = " << End << std::endl;
}

int main() {
    demo_use_enum();
    return 0;
}