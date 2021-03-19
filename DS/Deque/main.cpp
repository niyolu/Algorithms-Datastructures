#include <iostream>
#include "Deque.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Vector<int> vec;
    vec.push_back(1);
    Deque<int> de(vec);
    std::cout << de.back() << std::endl;
    return 0;
}
