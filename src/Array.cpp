#include "Array.hpp"
#include <iostream>
#include <iomanip>



template<typename T>
Array<T>::Array() : capacity(4), count(0), elements(nullptr) {
    elements = new T* [capacity];
    for (size_t i = 0; i < capacity; ++i) {
        elements[i] = 0; 
    }
}

template<typename T>
Array<T>::Array(size_t init_cap) 
    : count(0), elements(nullptr) {
    if (init_cap < 1) { 
        init_cap = 1;
    }
    capacity = init_cap;
    elements = new T*[capacity];
    
    size_t i = capacity;
    while (i > 0) {
        --i;
        elements[i] = nullptr; 
    }
}

template<typename T>
Array<T>::Array(const Array& rhs) 
    : capacity(rhs.capacity), count(rhs.count) {
    
    elements = new T*[capacity];
    
    for (size_t i = 0; i < count; ++i) {
        
        if (rhs.elements[i] != NULL) { 
            elements[i] = rhs.elements[i];
        } else {
            elements[i] = NULL;
        }
    }
    for (size_t i = count; i < capacity; ++i) {
        elements[i] = NULL;
    }
}

template<typename T>
Array<T>::Array(Array&& other) noexcept 
    : elements(other.elements), capacity(other.capacity), count(other.count) {
    other.elements = nullptr;
    other.capacity = 0;
    other.count = 0;
}

template<typename T>
Array<T>::~Array() {
    
    if (elements) { 
        clear();
        delete[] elements;
    }
}

template<typename T>
void Array<T>::resize() {
    size_t new_cap = capacity + capacity; 
    T** new_arr = new T*[new_cap];
    
    for (size_t i = 0; i < count; ++i) {
        new_arr[i] = elements[i];
    }
    
    for (size_t i = count; i < new_cap; ++i) {
        new_arr[i] = nullptr;
    }
    
    delete[] elements; 
    elements = new_arr;
    capacity = new_cap;
}

template<typename T>
void Array<T>::validateIndex(size_t index) const { 
    if (index < 0 || index >= count) { 
        throw std::out_of_range("Bad index"); 
    }
}

template<typename T>
void Array<T>::add(T* item) { 
    if (!item) { 
        throw std::invalid_argument("Cannot add null item");
    }
    if (count == capacity) { 
        resize();
    }
    elements[count] = item;
    count++;
}

template<typename T>
void Array<T>::remove(size_t index) {
    validateIndex(index);
    
    delete elements[index];
    
    
    size_t i = index;
    while (i < count - 1) {
        elements[i] = elements[i + 1];
        i++;
    }
    
    count--;
    elements[count] = nullptr; 
}

template<typename T>
void Array<T>::clear() {
    for (size_t i = 0; i < count; ++i) {
        if (elements[i]) { 
            delete elements[i];
            elements[i] = NULL; 
        }
    }
    count = 0;
}

template<typename T>
T* Array<T>::get(size_t index) const { 
    validateIndex(index);
    return elements[index];
}

template<typename T>
T* Array<T>::operator[](size_t index) const {
    
    return get(index);
}

template<typename T>
size_t Array<T>::getSize() const { 
    return count;
}

template<typename T>
bool Array<T>::isEmpty() const { 
    return count == 0;
}

template<typename T>
double Array<T>::getTotalArea() const {
    double area_sum = 0.0f; 
    
    for (size_t i = 0; i < count; ++i) {
        auto* fig = dynamic_cast<Figure*>(elements[i]);
        if (fig) { 
            area_sum += static_cast<double>(*fig);
        }
    }
    return area_sum;
}

template<typename T>
void Array<T>::printAll(std::ostream& os) const {
    if (isEmpty()) { 
        os << "empty array :(\n"; 
        return;
    }
    
    os << "=== Array of Figures (" << getSize() << " elements) ===\n\n";
    
    for (size_t i = 0; i < getSize(); ++i) {
        os << "Figure #" << i << ":\n";
        
        T* el = get(i); 
        if (auto* fig = dynamic_cast<Figure*>(el)) {
            
            os << *fig; 
            
            auto center = fig->Center();
            
            os << "Center: (" << std::setprecision(2) << std::fixed 
               << center.first << ", " << center.second << ")\n";
            
            double area = static_cast<double>(*fig);
            os << "Area: " << area << "\n";
        } else {
            os << "  Invalid figure\n";
        }
        os << "\n";
    }
    
    os << "Total area of all figures: " 
       << std::setprecision(2) << std::fixed 
       << getTotalArea() << "\n";
}

template class Array<Figure>;