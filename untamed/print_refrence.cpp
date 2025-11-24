/*
 * @Descripttion: 打印 引用 看看
 * @Author: zhanjiewen
 * @Date: 2025-09-25
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2025-11-24
 */

#include <iostream>

void demo_print_refrence() {
    int num = 20;

    int& num_ref = num;

    std::cout << "print: &num_ref: " << &num_ref << std::endl;
    std::cout << "print: num_ref: " << num_ref << std::endl;

    // print: &num_ref: 0x7ffd28f6302c
    // print: num_ref: 20
}

int main() {
    demo_print_refrence();
    return 0;
}