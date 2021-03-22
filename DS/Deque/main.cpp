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
    std::cout << de;
    auto it = de.begin();
    std::cout <<  *it << std::endl; // seems to work until operator*. Then suddenly the pointer points somewhere
#else
    Vector<int> vec;
    vec.push_back(0);
    vec.push_back(1);
    Deque<int> de(vec);
    std::cout << de.front() << std::endl;
    std::cout << de.back() << std::endl;
    std::cout << "testing the push functions" << std::endl;
    de.push_front(-1);
    de.push_back(2);
    std::cout << de[0] << std::endl;
    std::cout << de[1] << std::endl;
    std::cout << de[2] << std::endl;
    std::cout << de[3] << std::endl;
    std::cout << "front=" << de.front() << std::endl;
    std::cout << "back=" << de.back() << std::endl;
    std::cout << de;
    std::cout << "testing the pop's" << std::endl;
    std::cout <<  de.pop_front() << std::endl;
    std::cout <<  de.pop_back() << std::endl;
    std::cout << de;
    std::cout << "filling up deque again:" << std::endl;
    de.push_front(-1);
    de.push_front(-2);
    de.push_back(2);
    std::cout << de;
    std::cout << "testing rotate(1)" << std::endl;
    de.rotate(1);
    std::cout << de;std::cout << "testing rotate(-3)" << std::endl;
    de.rotate(-3);
    std::cout << de;
#endif

#if 0
    std::cout << "testing copy constructor" << std::endl;
    Vector<int> vec2;
    Vector<Vector<int>> vecvec;
    vecvec.push_back(vec2);
    vecvec.push_back(vec2);
    vecvec.push_back(vec2);

    Deque<Vector<int>> de2(vecvec);
    de2.push_front(vec2);
    de2.push_front(vec2);
    std::cout << de2;
#endif
    return 0;
}