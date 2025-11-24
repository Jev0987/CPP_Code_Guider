/*
 * @Descripttion: 友元函数 是全局函数，通过全局函数访问类中成员变量
 * @Author: Jev
 * @Date: 25-6-15
 */
#include <iostream>
#include <string>
#include <utility>

class People {
public:
    explicit People(std::string name)
        : m_name_(std::move(name)) {}

    friend void show(const People* people);

private:
    std::string m_name_;
};

void show(const People* people) { std::cout << people->m_name_ << std::endl; }

void demo_friend_method() {
    auto* people = new People("XiaoMing");
    show(people);
    delete people;
}

int main() {
    demo_friend_method();
    return 0;
}