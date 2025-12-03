#include "Pentagon.hpp"
#include <cmath>
#include <iomanip>

Pentagon::Pentagon() : cx(0), cy(0), a(1), angle(0) {
    auto vertices = GetVertices();
    for (size_t i = 0; i < vert.size() && i < vertices.size(); ++i) {
        vert[i] = Point<double>{vertices[i].first, vertices[i].second};
    }
}

Pentagon::Pentagon(double cx, double cy, double a, double angle) 
    : cx(cx), cy(cy), a(a), angle(angle) {
    auto vertices = GetVertices();
    for (size_t i = 0; i < vert.size() && i < vertices.size(); ++i) {
        vert[i] = Point<double>{vertices[i].first, vertices[i].second};
    }
}

std::vector<std::pair<double, double>> Pentagon::GetVertices() const {
    std::vector<std::pair<double, double>> vertices;
    double R = a / (2 * std::sin(M_PI / 5.0));
    
    for (int i = 0; i < 5; ++i) {
        double vertexAngle = -M_PI / 2 + 2 * M_PI * i / 5.0 + angle;
        double x = cx + R * std::cos(vertexAngle);
        double y = cy + R * std::sin(vertexAngle);
        vertices.push_back({x, y});
    }
    return vertices;
}

std::pair<double, double> Pentagon::Center() const {
    double sum_x = 0.0, sum_y = 0.0;
    for (size_t i = 0; i < vert.size(); ++i) {
        sum_x += vert[i].x;
        sum_y += vert[i].y;
    }
    const double n = static_cast<double>(vert.size());
    return {sum_x / n, sum_y / n};
}

void Pentagon::Print(std::ostream& os) const {
    // Use stored vertices to print (store points after Read/ctor)
    std::vector<std::pair<double,double>> vertices;
    for (size_t i = 0; i < vert.size(); ++i) {
        vertices.push_back({vert[i].x, vert[i].y});
    }
    double angleDeg = angle * 180.0 / M_PI;
    os << "Pentagon (center: " << std::fixed << std::setprecision(2) 
       << cx << ", " << cy << "; side: " << a 
       << "; rotation: " << angleDeg << "°)\n";
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
    std::cout << "Enter rotation angle in degrees: ";
    double angleDeg;
    is >> angleDeg;
    angle = angleDeg * M_PI / 180.0;
    // After reading parameters, generate and store vertices
    auto vertices = GetVertices();
    for (size_t i = 0; i < vert.size() && i < vertices.size(); ++i) {
        vert[i] = Point<double>{vertices[i].first, vertices[i].second};
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
        angle = pent->angle;
        // update stored vertices
        auto vertices = GetVertices();
        for (size_t i = 0; i < vert.size() && i < vertices.size(); ++i) {
            vert[i] = Point<double>{vertices[i].first, vertices[i].second};
        }
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
        angle = pent->angle;
        auto vertices = GetVertices();
        for (size_t i = 0; i < vert.size() && i < vertices.size(); ++i) {
            vert[i] = Point<double>{vertices[i].first, vertices[i].second};
        }
    }
    return *this;
}

bool Pentagon::operator==(const Figure& other) const {
    if (auto* pent = dynamic_cast<const Pentagon*>(&other)) {
        return std::fabs(cx - pent->cx) < 1e-9 &&
               std::fabs(cy - pent->cy) < 1e-9 &&
               std::fabs(a - pent->a) < 1e-9 &&
               std::fabs(angle - pent->angle) < 1e-9;
    }
    return false;
}