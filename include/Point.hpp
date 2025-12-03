#ifndef POINT_HPP
#define POINT_HPP

#include <concepts>
#include <iostream>
#include <type_traits>

template <typename T>
struct Point {
    T x{};
    T y{};

    Point();
    Point(T x_val, T y_val);

    Point(const Point& other);
    Point& operator=(const Point& other);

    bool operator==(const Point& other) const;

    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;
    Point operator/(T value) const;

    double distance(const Point& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }
};

#include "Point.tpp"
#endif // POINT_HPP
