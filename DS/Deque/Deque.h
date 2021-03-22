//
// Created by Nils Lübben on 16.03.2021.
//

#ifndef DEQUE_DEQUE_H
#define DEQUE_DEQUE_H

#endif //DEQUE_DEQUE_H

#include "../Vector/Vector.h"
#include <cmath>

//#define DREVERSE

template <typename Deque>
class DequeIterator {
public:
    using VectorIterator = typename Deque::Vector::AbstractIterator;
    using ValueType = typename Deque::Vector::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;

protected:
    VectorIterator* m_current;
    VectorIterator* m_L_iterator;
    const VectorIterator* m_end;
    VectorIterator* m_R_iterator;

public:

    virtual DequeIterator& operator++() = 0;

#if 0

    const virtual DequeIterator& operator++(int) = 0;

    virtual DequeIterator& operator--() = 0;

    const virtual DequeIterator& operator--(int) = 0;

#endif

    ReferenceType operator[](std::size_t index) {
        return (*m_current)[index];
    }

    PointerType operator->() {
        return *m_current;
    }

    ReferenceType operator*() {
        return **m_current;
    }

    bool operator==(const VectorIterator& other) {
        return m_current == other.current;
    }

    bool operator!=(const VectorIterator& other) {
        return !(*this == other);
    }
};

template <typename Deque>
class FDequeIterator : public DequeIterator<Deque> {
public:
    using VectorIterator = typename Deque::Vector::AbstractIterator;
    using ValueType = typename Deque::Vector::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;

public:

    FDequeIterator(const FDequeIterator& other) {
        this->m_current = other.m_current;
        this->m_L_iterator = other.m_L_iterator;
        this->m_R_iterator = other.m_R_iterator;
        this->m_end = other.m_end;  // points to left Vector end
    }

    FDequeIterator(VectorIterator* L_iterator,
                   VectorIterator* R_iterator,
                   VectorIterator* current,
                   VectorIterator* end) {
        this->m_L_iterator = L_iterator;
        this->m_R_iterator = R_iterator;
        this->m_current = current;
        this->m_end = end;
    }

    FDequeIterator& operator++() {
        if (this->m_L_iterator != nullptr && this->m_current + 1 == this->m_end)
            this->m_current = this->m_R_iterator;
        else
            this->m_current++;
        return *this;
    }
};

template <typename T>
class Deque {
public:
    using Vector = Vector<T>;
    using VectorIterator = typename Vector::AbstractIterator ;
    using VectorFIterator = typename Vector::Iterator;
    using VectorRIterator = typename Vector::ReverseIterator;
    using Iterator = FDequeIterator<Deque<T>>;
#ifdef DREVERSE
    using ReverseIterator = RDequeIterator<Vector>;
#elif defined REVERSE
    using ReverseVectorIterator = typename Vector::ReverseIterator;
#endif
protected:
    Vector m_left;
    Vector m_right;

public:
    Deque() : Deque(Vector::MIN_SIZE) {}

    Deque(std::size_t capacity)
    : m_left(std::floor((double) capacity/2.0f)), m_right((std::ceil((double) capacity/2.0f))) {}

    Deque(const Deque& other) : m_left(other.m_left), m_right(other.m_right) {}

    Deque(const Vector& vec) : m_left(0), m_right(vec) {}

    ~Deque() = default;

    T& front() {
        return m_left.empty() ? m_right[0] : m_left[m_left.Size() - 1];
    }

    T& back() {
        return m_right.empty() ? m_left[0] :  m_right[m_right.Size() - 1];
    }

    T& operator[](std::size_t index) {
        return (index < m_left.Size()) ? m_left[m_left.Size() - index - 1] : m_right[index - m_left.Size()];
    }

    void push_back(const T& value) {
        m_right.push_back(value);
    }

    void emplace_back(const T& value) {
        m_right.emplace_back(value);
    }

    T pop_back() {
        if (m_right.empty()) {
            return m_left.remove(0);
        }
        return m_right.pop_back();
    }

    void push_front(const T& value) {
        m_left.push_back(value);
    }

    void emplace_front(const T& value) {
        m_left.emplace_back(value);
    }

    T pop_front() {
        if (m_left.empty()) {
            return m_right.remove(0);
        }
        return m_left.pop_back();
    }

    void clear() {
        m_right.clear();
        m_left.clear();
    }

    void rotate(int rotations) {
        if (rotations == 0) return;
        if (rotations > 0) {    // a,b,c -1> c,a,b
            for (unsigned int i = 0; i < rotations; i++)
                this->push_front(this->pop_back());
        }
        else {                  // a,b,c -(-1)> b,c,a
            for (unsigned int i = 0; i < -rotations; i++)
                this->push_back(this->pop_front());
        }
    }

    std::size_t Size() {
        return m_left.Size() + m_right.Size();
    }

    std::size_t Capacity() {
        return m_left.Capacity() + m_right.Capacity();
    }

    bool empty() {
        return m_left.empty() && m_right.empty();
    }

#ifdef REVERSE
    Iterator begin() {
        VectorIterator *L_it, *R_it, *current, *end;
        if (!m_left.empty()) {
            L_it = new VectorRIterator(&(*m_left.rbegin()));
            R_it = new VectorFIterator(&(*m_right.begin()));
            current = new VectorRIterator(&(*m_left.rbegin()));
            end = new VectorFIterator (&(*m_left.rend()));
        }
        else {
            L_it = nullptr;
            R_it = new VectorFIterator(&(*m_right.begin()));
            current = new VectorFIterator(&(*m_right.begin()));
            end = nullptr;
        }
        return Iterator(L_it, R_it, current, end);
    }
#endif
    /*
    Iterator end() const {
        if (m_right.empty())
            return Iterator(&(m_left.begin()), nullptr, &(m_left.end()), nullptr);
        else
            return Iterator(&(m_left.begin()), &(m_right.begin()), &(m_right.end()), &(m_left.end()));
    }
     */

    friend std::ostream& operator<<(std::ostream& os, const Deque& de) {
        Deque::Vector L_reverse = de.m_left;
        L_reverse.reverse();
        return os << L_reverse.to_string() << " | " << de.m_right.to_string() << std::endl << std::endl;
    }
};