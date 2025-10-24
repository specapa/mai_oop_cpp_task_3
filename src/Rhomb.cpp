#include "Rhomb.hpp"
#include <cmath>
#include <iomanip>

Rhomb::Rhomb() : cx(0), cy(0), d1(1), d2(1) {}

Rhomb::Rhomb(double cx, double cy, double d1, double d2) : cx(cx), cy(cy), d1(d1), d2(d2) {}

std::vector<std::pair<double, double>> Rhomb::GetVertices() const {
    std::vector<std::pair<double, double>> vertices;
    vertices.push_back({cx + d1/2, cy});
    vertices.push_back({cx, cy + d2/2});
    vertices.push_back({cx - d1/2, cy});
    vertices.push_back({cx, cy - d2/2});
    return vertices;
}

std::pair<double, double> Rhomb::Center() const {
    return {cx, cy};
}

void Rhomb::Print(std::ostream& os) const {
    auto vertices = GetVertices();
    os << "Rhomb (center: " << std::fixed << std::setprecision(2) 
       << cx << ", " << cy << "; diagonals: " << d1 << ", " << d2 << ")\n";
    os << "Vertices:\n";
    for (size_t i = 0; i < vertices.size(); ++i) {
        os << "  V" << i << ": (" << vertices[i].first 
           << ", " << vertices[i].second << ")\n";
    }
}

void Rhomb::Read(std::istream& is) {
    std::cout << "Enter center coordinates (cx cy): ";
    is >> cx >> cy;
    std::cout << "Enter diagonals (d1 d2): ";
    is >> d1 >> d2;
    if (d1 <= 0 || d2 <= 0) {
        throw std::invalid_argument("Diagonals must be positive");
    }
}

Rhomb::operator double() const {
    return (d1 * d2) / 2.0;
}

Figure& Rhomb::operator=(const Figure& other) {
    if (this == &other) {
        return *this;
    }
    
    if (auto* rhomb = dynamic_cast<const Rhomb*>(&other)) {
        cx = rhomb->cx;
        cy = rhomb->cy;
        d1 = rhomb->d1;
        d2 = rhomb->d2;
    }
    return *this;
}

Figure& Rhomb::operator=(Figure&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    
    if (auto* rhomb = dynamic_cast<Rhomb*>(&other)) {
        cx = rhomb->cx;
        cy = rhomb->cy;
        d1 = rhomb->d1;
        d2 = rhomb->d2;
    }
    return *this;
}

bool Rhomb::operator==(const Figure& other) const {
    if (auto* rhomb = dynamic_cast<const Rhomb*>(&other)) {
        return std::fabs(cx - rhomb->cx) < 1e-9 &&
               std::fabs(cy - rhomb->cy) < 1e-9 &&
               std::fabs(d1 - rhomb->d1) < 1e-9 &&
               std::fabs(d2 - rhomb->d2) < 1e-9;
    }
    return false;
}