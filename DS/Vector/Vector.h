//
// Created by Nils Lübben on 16.03.2021.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#endif //VECTOR_VECTOR_H

#include <iterator>
#include <exception>

//#define REVERSE

template <typename Vector>
class VectorIterator {
public:
    using ValueType = typename Vector::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
protected:
    PointerType m_ptr;
public:

    virtual VectorIterator& operator++() = 0;

    const virtual VectorIterator& operator++(int) = 0;

    virtual VectorIterator& operator--() = 0;

    const virtual VectorIterator& operator--(int) = 0;

    virtual VectorIterator& operator+(int) = 0;

    virtual VectorIterator& operator-(int) = 0;

    virtual VectorIterator& operator+=(int) = 0;

    virtual VectorIterator& operator-=(int) = 0;

    ReferenceType operator[](std::size_t index) {
        return *(m_ptr + index);
    }

    PointerType operator->() {
        return m_ptr;
    }

    ReferenceType operator*() {
        return *m_ptr;
    }

    VectorIterator& operator=(const VectorIterator& other) {
        m_ptr = other.m_ptr;
        return *this;
    }

    bool operator==(const VectorIterator& other) {
        return m_ptr == other.m_ptr;
    }

    bool operator!=(const VectorIterator& other) {
        return !(*this == other);
    }
};


template <typename Vector>
class FVectorIterator : public VectorIterator<Vector> {
public:
    using ValueType = typename Vector::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;

public:

    FVectorIterator() {
        this->m_ptr = nullptr;
    }

    FVectorIterator(const FVectorIterator& other) {
        this->m_ptr = other.m_ptr;
    }

    FVectorIterator(PointerType ptr) {
        this->m_ptr = ptr;
    }

    FVectorIterator& operator++() {
        this->m_ptr++;
        return *this;
    }

    const FVectorIterator& operator++(int) {
        FVectorIterator temp = *this;
        ++(*this);
        return temp;
    }

    FVectorIterator& operator--() {
        this->m_ptr--;
        return *this;
    }

    const FVectorIterator& operator--(int) {
        FVectorIterator temp = *this;
        --(*this);
        return temp;
    }

    FVectorIterator& operator+(int index) {
        PointerType ptr = this->m_ptr + index;
        FVectorIterator *it = new FVectorIterator(ptr);
        return *it;
    }

    FVectorIterator& operator-(int index) {
        return (*this) + (-index);
    }

    FVectorIterator& operator+=(int index) {
        this->m_ptr += index;
        return *this;
    }

    FVectorIterator& operator-=(int index) {
        return (*this) += -index;
    }
};


#ifdef REVERSE
template <typename Vector>
class RVectorIterator : public VectorIterator<Vector> {
public:

    using ValueType = typename Vector::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;

    RVectorIterator() {
        this->m_ptr = nullptr;
    }

    RVectorIterator(const RVectorIterator& other) {
        this->m_ptr = other.m_ptr;
    }

    RVectorIterator(PointerType ptr) {
        this->m_ptr = ptr;
    }

    RVectorIterator& operator++() {
        (this->m_ptr)--;
        return *this;
    }

    const RVectorIterator& operator++(int) {
        RVectorIterator temp = *this;
        ++(*this);
        return temp;
    }

    RVectorIterator& operator--() {
        (this->m_ptr)++;
        return *this;
    }

    const RVectorIterator& operator--(int) {
        RVectorIterator temp = *this;
        --(*this);
        return temp;
    }

    RVectorIterator& operator+(int index) {
        PointerType ptr = this->m_ptr - index;
        RVectorIterator *it = new RVectorIterator(ptr);
        return *it;
    }

    RVectorIterator& operator-(int index) {
        return (*this) + (-index);
    }

    RVectorIterator& operator+=(int index) {
        this->m_ptr -= index;
        return *this;
    }

    RVectorIterator& operator-=(int index) {
        return (*this) += -index;
    }
};
#endif


template <typename T>
class Vector {
public:
    using ValueType = T;
    using Iterator = FVectorIterator<Vector<T>>;
#ifdef REVERSE
    using ReverseIterator = RVectorIterator<Vector<T>>;
#endif
    static const std::size_t MIN_SIZE = 16;

private:
    T *m_data;
    std::size_t m_capacity;
    std::size_t m_size;

public:
    explicit Vector(int cap)
            : m_size(0), m_capacity(std::max(cap, 0))
    {
        reAlloc(m_capacity);
    }

    Vector() : Vector(MIN_SIZE) {}

    Vector(const Vector& other)
            : m_size(0), m_capacity(other.m_capacity) {
        reAlloc(m_capacity);
        for (auto value : other)
            push_back(value);
        m_size = other.m_size;
    }

    ~Vector() {
        clear();
        ::operator delete(m_data, m_capacity * sizeof(T));
    }

private:
    void reAlloc(std::size_t new_capacity) {
        T* new_data = (T*) ::operator new(new_capacity * sizeof(T));
        std::size_t size = std::min(new_capacity, m_size);

        for (std::size_t i = 0; i < size; i++)
            new (&new_data[i]) T(std::move(m_data[i]));    // can't assign-construct complex types with new operator

        for (std::size_t i = 0; i < size; i++)
            m_data[i].~T();

        if (m_size > 0)
            ::operator delete(m_data, m_capacity * sizeof(T));

        m_data = new_data;
        m_capacity = new_capacity;
    }

public:

    void push_back(const T& value) {
        if (m_size > m_capacity)
            reAlloc(std::max((int)(m_capacity + m_capacity / 2), (int) MIN_SIZE));
        m_data[m_size++] = value;
    }

    void push_back(T&& value) {
        if (m_size > m_capacity)
            reAlloc(std::max((int)(m_capacity + m_capacity / 2), (int) MIN_SIZE));
        m_data[m_size++] = std::move(value);
    }

    // variadic templates
    template<typename... Args>
    T& emplace_back(Args&&... args) {
        if (m_size >= m_capacity)
            reAlloc(std::max((int)(m_capacity + m_capacity / 2), (int) MIN_SIZE));
        new(&m_data[m_size]) T(std::forward<Args>(args)...);
        return m_data[m_size++];
    }

    void pop_back() {
        if (m_size <= 0) return;
        m_data[--m_size].~T();
    }

    void clear() {
        for (auto& value : *this)
            value.~T();
        m_size = 0;
    }

    std::size_t Size() const {
        return m_size;
    }

    std::size_t Capacity() const {
        return m_capacity;
    }

    bool empty() const {
        return m_size == 0;
    }

    T& operator[](std::size_t index) {
        if (index >= m_size || index < 0 || m_capacity == 0) {
            std::string msg = "m_data[" + std::to_string(index) + "], cap=" + std::to_string(m_capacity);
            throw std::out_of_range(msg);
        }
        return m_data[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= m_size || index < 0 || m_capacity == 0) {
            std::string msg = "m_data[" + std::to_string(index) + "], cap=" + std::to_string(m_capacity);
            throw std::out_of_range(msg);
        }
        return m_data[index];
    }

    Vector& operator=(const Vector& other) {
        if (this == &other)
            return *this;
        clear();
        reAlloc(other.m_capacity);
        for (auto val : other)
            push_back(val);
        return *this;
    }

public:

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        for (auto el : vec)
            os << el << " ";
        return  os << std::endl << "size=" << vec.m_size << " cap=" << vec.m_capacity << std::endl << std::endl;
    }

    Iterator begin() const {
        return Iterator(m_data);
    }

    Iterator end() const {
        return Iterator(m_data + m_size);
    }

#ifdef REVERSE
    ReverseIterator rbegin() {
        return ReverseIterator(m_data + (m_size - 1));
    }

    ReverseIterator rend() {
        return ReverseIterator(m_data - 1);
    }
#endif
};