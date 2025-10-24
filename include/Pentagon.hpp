#ifndef PENTAGON_HPP
#define PENTAGON_HPP

#include "Figure.hpp"
#include <vector>

class Pentagon : public Figure {
private:
    double cx, cy;
    double a;
    double angle;

public:
    Pentagon();
    Pentagon(double cx, double cy, double a, double angle = 0);

    std::vector<std::pair<double, double>> GetVertices() const;

    std::pair<double, double> Center() const override;
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;
    operator double() const override;

    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) noexcept override;
    bool operator==(const Figure& other) const override;
};

#endif // PENTAGON_HPP