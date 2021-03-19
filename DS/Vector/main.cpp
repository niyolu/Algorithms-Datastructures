//
// Created by Nils Lübben on 16.03.2021.
//

#include <iostream>
#include "Vector.h"

int main(int argc, char** argv) {
#ifdef REVERSE
    Vector<int> bla;
    bla.push_back(10);
    bla.push_back(20);
    bla.push_back(30);
    bla.push_back(40);
    bla.push_back(50);
    bla.push_back(60);
    bla.push_back(70);
    bla.push_back(80);
    bla.push_back(90);
    bla.push_back(100);
    for (auto it = bla.rbegin(), end = bla.rend(); it != end; ++it) {
        std::cout << *it << std::endl;
    }
#else
    Vector<int> vec;
    vec.push_back(0);
    vec.push_back(1);
    std::cout << vec;
    vec.pop_back();
    std::cout << vec;

    Vector<int> vec2(100);
    std::cout << vec2;
    vec2.push_back(200);
    vec2.emplace_back(100);
    vec2.emplace_back(100);
    vec2.emplace_back(100);
    vec2.emplace_back(100);
    vec2.emplace_back(100);
    std::cout << vec2;
    vec2.clear();
    std::cout << vec2;
    vec2.push_back(200);
    vec2.emplace_back(100);
    vec2.emplace_back(100);
    vec2.emplace_back(100);
    vec2.emplace_back(100);
    vec2.emplace_back(100);
    Vector<int> vec3(vec2);
    std::cout << vec3;
    vec3.clear();
    std::cout << vec2;
    std::cout << vec3;
    vec3 = vec2;
    std::cout << vec3;
#endif
    return 0;
}