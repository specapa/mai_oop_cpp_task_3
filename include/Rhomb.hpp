#ifndef RHOMB_HPP
#define RHOMB_HPP

#include "Figure.hpp"

class Rhomb : public Figure {
private:
    std::array<Point<double>, 4> vert;
    double cx, cy;
    double d1, d2;
    double angle;

public:
    Rhomb();
    Rhomb(double cx, double cy, double d1, double d2, double angle = 0);

    std::vector<std::pair<double, double>> GetVertices() const;

    std::pair<double, double> Center() const override;
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;
    operator double() const override;

    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) noexcept override;
    bool operator==(const Figure& other) const override;
};

#endif // RHOMB_HPP