#include <iostream>
#include "Deque.h"

int main() {
#if 1
    Deque<int> de;
    for (int i = 0; i < 10; ++i) {
        de.push_back(1);
    }
    de.push_back(-1);
    for (int i = 0; i < 10; ++i) {
        de.push_front(2);
    }
    de.push_front(-2);
    std::cout <<  *de.begin() << std::endl; // seems to work until operator*. Then suddenly the pointer points somewhere
#else
    Vector<int> vec;
    vec.push_back(0);
    vec.push_back(1);
    Deque<int> de(vec);
    std::cout << de.front() << std::endl;
    std::cout << de.back() << std::endl;
    de.push_front(-1);
    de.push_back(2);
    std::cout << de[0] << std::endl;
    std::cout << de[1] << std::endl;
    std::cout << de[2] << std::endl;
    std::cout << de[3] << std::endl;
    std::cout << de.front() << std::endl;
    std::cout << de.back() << std::endl;
    de.pop_back();
    de.pop_front();
#endif
    return 0;
}
