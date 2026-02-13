<!--
 * @Descripttion: 
 * @Author: jev
 * @Date: 2025-12-03
-->
# Fast-DDS 双缓冲队列（DBQueue）详细说明

## 双缓冲机制原理

### 1. 基本概念

双缓冲队列（Double Buffered Queue）是一种高性能的线程安全数据结构，专门为 MPSC（多生产者，单消费者）场景设计。

### 2. 核心思想

- **分离读写操作**：生产者和消费者操作不同的队列，避免锁竞争
- **原子交换**：通过 Swap() 操作原子性地交换前台和后台队列
- **无锁生产**：生产者之间只需要竞争后台队列锁，不影响消费者

### 3. 数据结构

```cpp
// 两个底层队列
std::queue<T> mQueueAlpha;  // Alpha 队列
std::queue<T> mQueueBeta;   // Beta 队列

// 指针引用（实现双缓冲的关键）
std::queue<T>* mForegroundQueue;   // 前台队列指针（消费者读取）
std::queue<T>* mBackgroundQueue;   // 后台队列指针（生产者写入）

// 线程同步
std::mutex mForegroundMutex;  // 前台队列锁
std::mutex mBackgroundMutex;  // 后台队列锁
```

## 工作流程详解

### 阶段 1：初始状态
```
前台队列 → Alpha 队列（空）
后台队列 → Beta 队列（空）
```

### 阶段 2：生产者写入
```
生产者1: Push(item1) → Beta 队列
生产者2: Push(item2) → Beta 队列
生产者3: Push(item3) → Beta 队列

结果：
前台队列 → Alpha 队列（空）
后台队列 → Beta 队列 [item1, item2, item3]
```

### 阶段 3：消费者处理
```
消费者调用 Swap()：
1. 清空 Alpha 队列（已经是空的）
2. 交换指针：
   - 前台队列 → Beta 队列 [item1, item2, item3]
   - 后台队列 → Alpha 队列（空）

消费者开始处理：
- Front() → item1
- Pop() → 移除 item1
- Front() → item2
- Pop() → 移除 item2
- Front() → item3
- Pop() → 移除 item3
```

### 阶段 4：新的生产周期
```
生产者继续写入：
生产者4: Push(item4) → Alpha 队列（现在是后台队列）
生产者5: Push(item5) → Alpha 队列

结果：
前台队列 → Beta 队列（空，已处理完）
后台队列 → Alpha 队列 [item4, item5]
```

## 性能优势

### 1. 减少锁竞争
- **传统队列**：生产者和消费者竞争同一个锁
- **双缓冲队列**：生产者和消费者使用不同的锁

### 2. 提高吞吐量
- 生产者可以持续写入后台队列
- 消费者可以批量处理前台队列
- Swap() 操作是原子性的，开销很小

### 3. 内存局部性
- 消费者连续处理同一队列中的数据
- 减少缓存未命中的概率

## 在 Fast-DDS 日志系统中的应用

### 1. 日志生产者
```cpp
// 多个线程同时调用日志宏
logInfo(CATEGORY, "消息1");  // 线程1
logWarning(CATEGORY, "消息2"); // 线程2
logError(CATEGORY, "消息3");   // 线程3
```

### 2. 日志消费者
```cpp
// 日志处理线程
void Log::run() {
    while (logging) {
        // 交换队列，获取新的日志数据
        resources_.logs.Swap();
        
        // 批量处理前台队列中的所有日志
        while (!resources_.logs.Empty()) {
            Log::Entry& entry = resources_.logs.Front();
            // 处理日志条目
            for (auto& consumer : resources_.consumers) {
                consumer->Consume(entry);
            }
            resources_.logs.Pop();
        }
    }
}
```

## 关键操作说明

### 1. Push() 操作
```cpp
void Push(const T& item) {
    std::unique_lock<std::mutex> guard(mBackgroundMutex);
    mBackgroundQueue->push(item);
}
```
- 只锁定后台队列
- 多个生产者可以竞争，但不会阻塞消费者

### 2. Swap() 操作
```cpp
void Swap() {
    std::unique_lock<std::mutex> fgGuard(mForegroundMutex);
    std::unique_lock<std::mutex> bgGuard(mBackgroundMutex);
    
    // 清空前台队列
    std::queue<T>().swap(*mForegroundQueue);
    
    // 交换指针
    auto* swap = mBackgroundQueue;
    mBackgroundQueue = mForegroundQueue;
    mForegroundQueue = swap;
}
```
- 同时锁定两个队列
- 原子性地交换队列角色
- 清空已处理的数据

### 3. Front() 和 Pop() 操作
```cpp
T& Front() {
    std::unique_lock<std::mutex> guard(mForegroundMutex);
    return mForegroundQueue->front();
}

void Pop() {
    std::unique_lock<std::mutex> guard(mForegroundMutex);
    mForegroundQueue->pop();
}
```
- 只锁定前台队列
- 消费者独占前台队列，无竞争

## 使用注意事项

### 1. 线程安全
- 生产者线程安全：多个生产者可以同时调用 Push()
- 消费者线程安全：只有一个消费者线程调用 Front()/Pop()
- Swap() 操作需要独占访问

### 2. 性能考虑
- 适合高频率的生产者写入场景
- 消费者应该批量处理数据
- 避免频繁的 Swap() 调用

### 3. 内存管理
- 使用 swap() 清空队列，避免内存碎片
- 队列大小动态增长，无需预分配

## 总结

双缓冲队列是 Fast-DDS 日志系统高性能的关键组件，通过分离读写操作和原子交换机制，实现了：

1. **高并发性能**：生产者和消费者无锁竞争
2. **批量处理**：消费者可以高效处理大量数据
3. **线程安全**：通过细粒度锁保证数据一致性
4. **内存效率**：避免不必要的内存分配和拷贝

这种设计特别适合日志系统这种"多写少读"的场景，能够显著提高系统的整体性能。
