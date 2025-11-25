/*
 * @Descripttion: 简单的观察者模式
 * @Author: jev
 * @Date: 2025-08-17
 */
#include <iostream>
#include <list>
#include <mutex>
#include <string>

// 观察者抽象基类
class IObserver {
public:
    virtual ~IObserver(){};
    virtual void Update(const std::string& msg) = 0;  // 更新观察者状态
};

// 订阅者抽象基类
class ISubject {
public:
    virtual ~ISubject(){};
    virtual void attach(IObserver* observer) = 0;   // 添加观察者
    virtual void deatach(IObserver* observer) = 0;  // 删除观察者
    virtual void Notify() = 0;                      // 通知观察者
};

// 订阅者实现类
class Subject : public ISubject {
private:
    std::list<IObserver*> ob_lists;
    std::mutex mtx;
    std::string msg_;

public:
    void attach(IObserver* observer) override {
        std::unique_lock<std::mutex> lck(mtx);
        ob_lists.push_back(observer);  // 添加观察者到列表
    }

    void deatach(IObserver* observer) override {
        std::unique_lock<std::mutex> lck(mtx);
        ob_lists.remove(observer);  // 从列表删除观察者
    }

    void Notify() override {
        std::unique_lock<std::mutex> lck(mtx);
        std::list<IObserver*>::iterator it = ob_lists.begin();

        while (it != ob_lists.end()) {
            (*it)->Update(msg_);  // 通知观察者更新状态
            ++it;
        }
    }

    void createMessage(const std::string& message) { msg_ = message; }  // 创建消息
};

// 观察者实现类1
class Observer1 : public IObserver {
public:
    virtual void Update(const std::string& msg) {
        // observer 1 update
        std::cout << "observer 1 update: " << msg << std::endl;
    }
};

class Observer2 : public IObserver {
public:
    virtual void Update(const std::string& msg) {
        // observer 2 update
        std::cout << "observer 2 update: " << msg << std::endl;
    }
};

int main() {
    Subject subject;
    Observer1 observer1;
    Observer2 observer2;
    subject.attach(&observer1);
    subject.attach(&observer2);
    subject.createMessage("Hello, Observer!");
    subject.Notify();
    return 0;
}