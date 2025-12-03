#include "Hexagon.hpp"
#include <cmath>
#include <iomanip>

Hexagon::Hexagon() : cx(0), cy(0), a(1), angle(0) {
    auto vertices = GetVertices();
    for (size_t i = 0; i < vert.size() && i < vertices.size(); ++i) {
        vert[i] = Point<double>{vertices[i].first, vertices[i].second};
    }
}

Hexagon::Hexagon(double cx, double cy, double a, double angle) 
    : cx(cx), cy(cy), a(a), angle(angle) {
    auto vertices = GetVertices();
    for (size_t i = 0; i < vert.size() && i < vertices.size(); ++i) {
        vert[i] = Point<double>{vertices[i].first, vertices[i].second};
    }
}

std::vector<std::pair<double, double>> Hexagon::GetVertices() const {
    std::vector<std::pair<double, double>> vertices;
    double R = a;
    
    for (int i = 0; i < 6; ++i) {
        double vertexAngle = M_PI / 3.0 * i + angle;
        double x = cx + R * std::cos(vertexAngle);
        double y = cy + R * std::sin(vertexAngle);
        vertices.push_back({x, y});
    }
    return vertices;
}

std::pair<double, double> Hexagon::Center() const {
    double sum_x = 0.0, sum_y = 0.0;
    for (size_t i = 0; i < vert.size(); ++i) {
        sum_x += vert[i].x;
        sum_y += vert[i].y;
    }
    const double n = static_cast<double>(vert.size());
    return {sum_x / n, sum_y / n};
}

void Hexagon::Print(std::ostream& os) const {
    // Use stored vertices when printing
    std::vector<std::pair<double,double>> vertices;
    for (size_t i = 0; i < vert.size(); ++i) {
        vertices.push_back({vert[i].x, vert[i].y});
    }
    double angleDeg = angle * 180.0 / M_PI;
    os << "Hexagon (center: " << std::fixed << std::setprecision(2) 
       << cx << ", " << cy << "; side: " << a 
       << "; rotation: " << angleDeg << "°)\n";
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
    std::cout << "Enter rotation angle in degrees: ";
    double angleDeg;
    is >> angleDeg;
    angle = angleDeg * M_PI / 180.0;
    // store vertices
    auto vertices = GetVertices();
    for (size_t i = 0; i < vert.size() && i < vertices.size(); ++i) {
        vert[i] = Point<double>{vertices[i].first, vertices[i].second};
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
        angle = hex->angle;
        auto vertices = GetVertices();
        for (size_t i = 0; i < vert.size() && i < vertices.size(); ++i) {
            vert[i] = Point<double>{vertices[i].first, vertices[i].second};
        }
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
        angle = hex->angle;
        auto vertices = GetVertices();
        for (size_t i = 0; i < vert.size() && i < vertices.size(); ++i) {
            vert[i] = Point<double>{vertices[i].first, vertices[i].second};
        }
    }
    return *this;
}

bool Hexagon::operator==(const Figure& other) const {
    if (auto* hex = dynamic_cast<const Hexagon*>(&other)) {
        return std::fabs(cx - hex->cx) < 1e-9 &&
               std::fabs(cy - hex->cy) < 1e-9 &&
               std::fabs(a - hex->a) < 1e-9 &&
               std::fabs(angle - hex->angle) < 1e-9;
    }
    return false;
}