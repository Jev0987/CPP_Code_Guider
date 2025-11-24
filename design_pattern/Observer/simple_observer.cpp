/*
 * @Descripttion: 简单的观察者模式
 * @Author: jev
 * @Date: 2025-08-17
 */
#include <list>
#include <mutex>
#include <string>
class IObserver {
public:
    virtual ~IObserver() {};
    virtual void Update(const std::string &msg) = 0;
};

class ISubject {
public:
    virtual ~ISubject() {};
    virtual void attach(IObserver *observer) = 0;
    virtual void deatach(IObserver *observer) = 0;
    virtual void Notify() = 0;
};

class Subject : public ISubject {
private:
    std::list<IObserver *> ob_lists;
    std::mutex mtx;
    std::string msg_;

public:
    void attach(IObserver *observer) override {
        std::unique_lock<std::mutex> lck(mtx);
        ob_lists.push_back(observer);
    }

    void deatach(IObserver *observer) override {
        std::unique_lock<std::mutex> lck(mtx);
        ob_lists.remove(observer);
    }

    void Notify() override {
        std::unique_lock<std::mutex> lck(mtx);
        std::list<IObserver *>::iterator it = ob_lists.begin();

        while (it != ob_lists.end()) {
            (*it)->Update(msg_);
            ++it;
        }
    }

    void createMessage(const std::string &message) { msg_ = message; }
};

class Observer1 : public IObserver {
public:
    virtual void Update(const std::string &msg) {
        // observer 1 update
    }
};

class Observer2 : public IObserver {
public:
    virtual void Update(const std::string &msg) {
        // observer 2 update
    }
};
