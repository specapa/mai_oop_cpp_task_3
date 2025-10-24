#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "Figure.hpp"
#include <memory>
#include <stdexcept>

template<typename T>
class Array {
private:
    T** elements;
    size_t capacity;
    size_t count;
    
    void resize();
    void validateIndex(size_t index) const;

public:
    Array();
    Array(size_t initialCapacity);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    ~Array();
    
    void add(T* element);
    void remove(size_t index);
    T* get(size_t index) const;
    T* operator[](size_t index) const;
    
    size_t getSize() const;
    bool isEmpty() const;
    void clear();
    
    // Специальные методы для фигур
    double getTotalArea() const;
    void printAll(std::ostream& os) const;
};

#endif // ARRAY_HPP