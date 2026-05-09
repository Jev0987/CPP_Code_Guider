#include <iostream>

int g_init = 10;
int g_uninit;

int main(int argc, char** argv) {
	static int local_static = 5;
	std::cout << "hello world" << std::endl;
	return 0;
}
