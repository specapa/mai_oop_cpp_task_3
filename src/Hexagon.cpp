#include "Hexagon.hpp"
#include <cmath>
#include <iomanip>

Hexagon::Hexagon() : cx(0), cy(0), a(1) {}

Hexagon::Hexagon(double cx, double cy, double a) : cx(cx), cy(cy), a(a) {}

std::vector<std::pair<double, double>> Hexagon::GetVertices() const {
    std::vector<std::pair<double, double>> vertices;
    // Для правильного шестиугольника R = a
    double R = a;
    
    // Генерация вершин (начинаем с правой точки)
    for (int i = 0; i < 6; ++i) {
        double angle = M_PI / 3.0 * i;  // 60 между вершинами
        double x = cx + R * std::cos(angle);
        double y = cy + R * std::sin(angle);
        vertices.push_back({x, y});
    }
    return vertices;
}

std::pair<double, double> Hexagon::Center() const {
    return {cx, cy};
}

void Hexagon::Print(std::ostream& os) const {
    auto vertices = GetVertices();
    os << "Hexagon (center: " << std::fixed << std::setprecision(2) 
       << cx << ", " << cy << "; side: " << a << ")\n";
    os << "Vertices:\n";
    for (size_t i = 0; i < vertices.size(); ++i) {
        os << "  V" << i << ": (" << vertices[i].first 
           << ", " << vertices[i].second << ")\n";
    }
}

void Hexagon::Read(std::istream& is) {
    std::cout << "Enter center coordinates (cx cy): ";
    is >> cx >> cy;
    std::cout << "Enter side length (a): ";
    is >> a;
    if (a <= 0) {
        throw std::invalid_argument("Side length must be positive");
    }
}

Hexagon::operator double() const {
    return (3.0 * std::sqrt(3.0) * a * a) / 2.0;
}

Figure& Hexagon::operator=(const Figure& other) {
    if (this == &other) {
        return *this;
    }
    
    if (auto* hex = dynamic_cast<const Hexagon*>(&other)) {
        cx = hex->cx;
        cy = hex->cy;
        a = hex->a;
    }
    return *this;
}

Figure& Hexagon::operator=(Figure&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    
    if (auto* hex = dynamic_cast<Hexagon*>(&other)) {
        cx = hex->cx;
        cy = hex->cy;
        a = hex->a;
    }
    return *this;
}

bool Hexagon::operator==(const Figure& other) const {
    if (auto* hex = dynamic_cast<const Hexagon*>(&other)) {
        return std::fabs(cx - hex->cx) < 1e-9 &&
               std::fabs(cy - hex->cy) < 1e-9 &&
               std::fabs(a - hex->a) < 1e-9;
    }
    return false;
}