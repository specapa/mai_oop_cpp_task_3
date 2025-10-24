#include "Pentagon.hpp"
#include <cmath>
#include <iomanip>

Pentagon::Pentagon() : cx(0), cy(0), a(1) {}

Pentagon::Pentagon(double cx, double cy, double a) : cx(cx), cy(cy), a(a) {}

std::vector<std::pair<double, double>> Pentagon::GetVertices() const {
    std::vector<std::pair<double, double>> vertices;
    double R = a / (2 * std::sin(M_PI / 5.0));
    
    for (int i = 0; i < 5; ++i) {
        double angle = -M_PI / 2 + 2 * M_PI * i / 5.0;
        double x = cx + R * std::cos(angle);
        double y = cy + R * std::sin(angle);
        vertices.push_back({x, y});
    }
    return vertices;
}

std::pair<double, double> Pentagon::Center() const {
    return {cx, cy};
}

void Pentagon::Print(std::ostream& os) const {
    auto vertices = GetVertices();
    os << "Pentagon (center: " << std::fixed << std::setprecision(2) 
       << cx << ", " << cy << "; side: " << a << ")\n";
    os << "Vertices:\n";
    for (size_t i = 0; i < vertices.size(); ++i) {
        os << "  V" << i << ": (" << vertices[i].first 
           << ", " << vertices[i].second << ")\n";
    }
}

void Pentagon::Read(std::istream& is) {
    std::cout << "Enter center coordinates (cx cy): ";
    is >> cx >> cy;
    std::cout << "Enter side length (a): ";
    is >> a;
    if (a <= 0) {
        throw std::invalid_argument("Side length must be positive");
    }
}

Pentagon::operator double() const {
    return (5.0 * a * a) / (4.0 * std::tan(M_PI / 5.0));
}

Figure& Pentagon::operator=(const Figure& other) {
    if (this == &other) {
        return *this;
    }
    
    if (auto* pent = dynamic_cast<const Pentagon*>(&other)) {
        cx = pent->cx;
        cy = pent->cy;
        a = pent->a;
    }
    return *this;
}

Figure& Pentagon::operator=(Figure&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    
    if (auto* pent = dynamic_cast<Pentagon*>(&other)) {
        cx = pent->cx;
        cy = pent->cy;
        a = pent->a;
    }
    return *this;
}

bool Pentagon::operator==(const Figure& other) const {
    if (auto* pent = dynamic_cast<const Pentagon*>(&other)) {
        return std::fabs(cx - pent->cx) < 1e-9 &&
               std::fabs(cy - pent->cy) < 1e-9 &&
               std::fabs(a - pent->a) < 1e-9;
    }
    return false;
}