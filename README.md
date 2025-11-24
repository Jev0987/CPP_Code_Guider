<!--
 * @Descripttion: C++ 代码学习指南
 * @Author: jev
 * @Date: 2025-11-24
-->

# C++ 代码学习指南

这是一个 C++ 学习与实践的代码仓库，包含了指针、线程、设计模式等多个方面的示例代码和最佳实践。

## 📚 目录结构

```
Cpp_code_guider/
├── get_to_know_pointer/      # 指针相关示例
├── get_to_know_thread/        # 线程相关示例
├── design_pattern/            # 设计模式示例
├── untamed/                   # 其他知识点示例
└── beautiful_code_preview/    # 优秀代码预览
```

## 🎯 主要内容

### 1. 指针学习 (get_to_know_pointer)

- **循环引用问题** (`loop_reference_demo.cpp`)
  - 演示 `shared_ptr` 可能导致的循环引用问题
  - 展示如何使用 `weak_ptr` 避免内存泄漏

- **资源缓存** (`resource_cache_demo.cpp`)
  - 资源管理的实践示例

### 2. 线程学习 (get_to_know_thread)

- **Future/Promise** (`use_future_promise_control_thread.cpp`)
  - 使用 `std::future` 和 `std::promise` 进行线程间通信

- **条件变量** (`use_condition_variable_control_thread.cpp`)
  - 使用条件变量控制线程执行

- **异步任务** (`use_async_create_mission.cpp`)
  - 使用 `std::async` 创建异步任务

- **生产者消费者** (`producer_consumer_mutex_cond.cpp`)
  - 经典的生产者-消费者模式实现

- **线程通知** (`notify_thread.cpp`)
  - 线程间通知机制

- **线程交替打印** (`thread_print_ABC.cpp`, `thread_print_ABC2.cpp`)
  - 多线程交替执行的示例

### 3. 设计模式 (design_pattern)

- **单例模式** (`singleton/`)
  - 线程安全的单例模式实现

- **观察者模式** (`Observer/simple_observer.cpp`)
  - 观察者模式的简单实现

- **策略模式** (`Strategy/`)
  - 策略模式的使用示例（包含对比代码）

- **依赖注入** (`DI/car_1.cpp`)
  - 依赖注入模式的示例

### 4. 其他知识点 (untamed)

- 构造和析构时机
- 友元函数
- 枚举类
- 引用和指针的使用
- 内存管理（malloc/free）

### 5. 优秀代码预览 (beautiful_code_preview)

- **FastDDS MPSC 队列** (`fastdds_MPSC/DBQueue.hpp`)
  - 多生产者单消费者队列的优秀实现

## 🚀 编译和运行

所有示例代码都可以使用以下方式编译：

```bash
g++ <filename>.cpp -o <output_name> -std=c++11
./<output_name>
```

或者使用 C++14/17/20：

```bash
g++ <filename>.cpp -o <output_name> -std=c++17
./<output_name>
```

## 📝 使用说明

1. 每个目录下的示例代码都是独立的，可以直接编译运行
2. 代码中包含详细的中文注释，说明关键概念和注意事项
3. 建议按照目录顺序学习，从基础到进阶

## ⚠️ 注意事项

- 部分示例代码演示了常见错误（如循环引用），请注意区分正确和错误的用法
- 线程相关的示例需要注意线程安全问题
- 建议在理解代码的基础上进行实验和修改

## 📖 学习建议

1. **指针学习**：先理解基本概念，再学习智能指针的使用
2. **线程学习**：从简单的线程创建开始，逐步学习同步机制
3. **设计模式**：对比使用和不使用设计模式的代码，理解其优势
4. **实践**：运行代码，观察输出，修改参数，加深理解

## 🔗 相关资源

- [C++ 参考文档](https://zh.cppreference.com/)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)

---

**作者**: jev  
**最后更新**: 2025-11-24
