/*
 * @Descripttion:  char * 和 string
 * @Author: jev
 * @Date: 2026-02-09
 */

#include <cstring>
#include <string>
using std::string;

class Base {
    Base(string tag) {
        TAG = new char[tag.size() + 1];
        strcpy(TAG, tag.c_str());
    }

    ~Base() { delete[] TAG; }

private:
    char* TAG;
};

int main() { return 0; }
