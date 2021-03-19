//
// Created by NiJoL on 16.03.2021.
//

#ifndef DEQUE_DEQUE_H
#define DEQUE_DEQUE_H

#endif //DEQUE_DEQUE_H

#include "../Vector/Vector.h"

template <typename T>
class Deque {
protected:
    Vector<T> m_left;
    Vector<T> m_right;

public:
    Deque() : Deque(16) {}

    Deque(std::size_t capacity) : m_left(0), m_right(capacity) {}

    Deque(const Deque& other) : m_left(other.m_left), m_right(other.m_right) {}

    Deque(const Vector<T>& vec) : m_left(0), m_right(vec) {}

    ~Deque() = default;

    T& front() {
        return m_left.empty() ? m_right[0] : m_left[m_left.Size() - 1];
    }

    T& back() {
        return m_right.empty() ? m_left[0] :  m_right[m_right.Size() - 1];
    }

#if 0
    T& operator[](std::size_t);

    void push_back(const T&);
    void emplace_back(const T&);
    void pop_back();

    void push_front(const T&);
    void emplace_front(const T&);
    void pop_font();

    void clear();
#endif
};