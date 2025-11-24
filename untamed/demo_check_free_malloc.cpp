/*
 * @Descripttion: 使用free释放空间后，对应的指针是否还有效 if(void*)
 * @Author: jev
 * @version:
 * @Date: 2025-02-08
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2025-11-24
 */
#include <iostream>

void check_free_malloc() {
    std::cout << __func__ << std::endl;
    void* buff = malloc(10);

    free(buff);

    if (buff) {
        std::cout << "free 后 指针仍然不为 nullptr" << std::endl;
        // 这里如果继续进行 free，会出现重复 free的错误
        // free(buff);
    }
}

int main() {
    check_free_malloc();
    return 0;
}