<!--
 * @Descripttion: 
 * @Author: jev
 * @Date: 2025-12-03
-->
typeid(T).name() - 获取类型T的编译器内部名称（mangled name）

abi::__cxa_demangle() - C++ ABI提供的反混淆函数


### 参数说明：
- 第一个参数：要反混淆的名称
- 第二个参数：输出缓冲区（nullptr表示自动分配）
- 第三个参数：输出缓冲区大小（nullptr表示自动计算）
- 第四个参数：状态码指针

### 关键说明
- 使用 std::unique_ptr 管理动态分配的内存
- char[] 表示字符数组
- void (*)(void *) 是自定义删除器类型（函数指针）
- std::free 是删除器，用于释放内存