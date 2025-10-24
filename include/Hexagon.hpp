#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include "Figure.hpp"
#include <vector>

class Hexagon : public Figure {
private:
    double cx, cy;
    double a;

public:
    Hexagon();
    Hexagon(double cx, double cy, double a);

    std::vector<std::pair<double, double>> GetVertices() const;

    std::pair<double, double> Center() const override;
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;
    operator double() const override;

    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) noexcept override;
    bool operator==(const Figure& other) const override;
};

#endif // HEXAGON_HPP