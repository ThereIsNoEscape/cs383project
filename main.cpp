// CS383 HW 3
#include <iostream>

#include "stack.cpp"

int main {
	Stack s;
	int c, t;
	std::cout << "Enter number count: ";
	std::cin >> c;
	while (c --> 0) {
		std::cout << "Next Number: ";
		std::cin >> t;
		s.Push(t);
	}
	c = 0;
	while (!s.IsEmpty()) {
		c += s.Pop();
	}
	std::cout << c << std::endl;
}

