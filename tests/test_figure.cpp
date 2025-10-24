#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include "../include/Figure.hpp"
#include "../include/Rhomb.hpp"
#include "../include/Pentagon.hpp"
#include "../include/Hexagon.hpp"
#include "../include/Array.hpp"

bool doubleEquals(double a, double b, double epsilon = 1e-6) {
    return std::fabs(a - b) < epsilon;
}

//  ТЕСТЫ ДЛЯ Rhomb 

TEST(RhombTest, DefaultConstructor) {
    Rhomb rhomb;
    auto center = rhomb.Center();
    EXPECT_DOUBLE_EQ(center.first, 0.0);
    EXPECT_DOUBLE_EQ(center.second, 0.0);
}

TEST(RhombTest, ParameterizedConstructor) {
    Rhomb rhomb(5.0, 3.0, 8.0, 6.0);
    auto center = rhomb.Center();
    EXPECT_DOUBLE_EQ(center.first, 5.0);
    EXPECT_DOUBLE_EQ(center.second, 3.0);
}

TEST(RhombTest, AreaCalculation) {
    Rhomb rhomb(0, 0, 8.0, 6.0);
    double area = static_cast<double>(rhomb);
    EXPECT_DOUBLE_EQ(area, 24.0); // (8 * 6) / 2 = 24
}

TEST(RhombTest, GetVertices) {
    Rhomb rhomb(0, 0, 4.0, 2.0);
    auto vertices = rhomb.GetVertices();
    EXPECT_EQ(vertices.size(), 4);
    
    // Проверяем вершины
    EXPECT_DOUBLE_EQ(vertices[0].first, 2.0);   // Правая
    EXPECT_DOUBLE_EQ(vertices[0].second, 0.0);
    EXPECT_DOUBLE_EQ(vertices[1].first, 0.0);   // Верхняя
    EXPECT_DOUBLE_EQ(vertices[1].second, 1.0);
    EXPECT_DOUBLE_EQ(vertices[2].first, -2.0);  // Левая
    EXPECT_DOUBLE_EQ(vertices[2].second, 0.0);
    EXPECT_DOUBLE_EQ(vertices[3].first, 0.0);   // Нижняя
    EXPECT_DOUBLE_EQ(vertices[3].second, -1.0);
}

TEST(RhombTest, CopyAssignment) {
    Rhomb rhomb1(1, 2, 6.0, 4.0);
    Rhomb rhomb2;
    rhomb2 = rhomb1;
    
    auto center1 = rhomb1.Center();
    auto center2 = rhomb2.Center();
    
    EXPECT_DOUBLE_EQ(center1.first, center2.first);
    EXPECT_DOUBLE_EQ(center1.second, center2.second);
    EXPECT_DOUBLE_EQ(static_cast<double>(rhomb1), static_cast<double>(rhomb2));
}

TEST(RhombTest, MoveAssignment) {
    Rhomb rhomb1(1, 2, 6.0, 4.0);
    Rhomb rhomb2;
    rhomb2 = std::move(rhomb1);
    
    auto center = rhomb2.Center();
    EXPECT_DOUBLE_EQ(center.first, 1.0);
    EXPECT_DOUBLE_EQ(center.second, 2.0);
}

TEST(RhombTest, EqualityOperator) {
    Rhomb rhomb1(1, 2, 6.0, 4.0);
    Rhomb rhomb2(1, 2, 6.0, 4.0);
    Rhomb rhomb3(1, 2, 6.0, 5.0);
    
    EXPECT_TRUE(rhomb1 == rhomb2);
    EXPECT_FALSE(rhomb1 == rhomb3);
}

TEST(RhombTest, OutputOperator) {
    Rhomb rhomb(0, 0, 4.0, 2.0);
    std::ostringstream oss;
    oss << rhomb;
    
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Rhomb") != std::string::npos);
    EXPECT_TRUE(output.find("Vertices") != std::string::npos);
}

TEST(RhombTest, InputOperator) {
    Rhomb rhomb;
    std::istringstream iss("5 3 8 6");
    iss >> rhomb;
    
    auto center = rhomb.Center();
    EXPECT_DOUBLE_EQ(center.first, 5.0);
    EXPECT_DOUBLE_EQ(center.second, 3.0);
}

TEST(RhombTest, InvalidDiagonals) {
    Rhomb rhomb;
    std::istringstream iss("0 0 -4 6");
    
    EXPECT_THROW(iss >> rhomb, std::invalid_argument);
}

// ТЕСТЫ ДЛЯ PENTAGON 

TEST(PentagonTest, DefaultConstructor) {
    Pentagon pent;
    auto center = pent.Center();
    EXPECT_DOUBLE_EQ(center.first, 0.0);
    EXPECT_DOUBLE_EQ(center.second, 0.0);
}

TEST(PentagonTest, ParameterizedConstructor) {
    Pentagon pent(2.0, 3.0, 5.0);
    auto center = pent.Center();
    EXPECT_DOUBLE_EQ(center.first, 2.0);
    EXPECT_DOUBLE_EQ(center.second, 3.0);
}

TEST(PentagonTest, AreaCalculation) {
    Pentagon pent(0, 0, 5.0);
    double area = static_cast<double>(pent);
    double expectedArea = (5.0 * 25.0) / (4.0 * std::tan(M_PI / 5.0));
    EXPECT_TRUE(doubleEquals(area, expectedArea));
}

TEST(PentagonTest, GetVertices) {
    Pentagon pent(0, 0, 5.0);
    auto vertices = pent.GetVertices();
    EXPECT_EQ(vertices.size(), 5);
}

TEST(PentagonTest, VerticesFormRegularPentagon) {
    Pentagon pent(0, 0, 5.0);
    auto vertices = pent.GetVertices();
    
    // Проверяем, что все стороны примерно равны
    for (size_t i = 0; i < 5; ++i) {
        size_t next = (i + 1) % 5;
        double dx = vertices[next].first - vertices[i].first;
        double dy = vertices[next].second - vertices[i].second;
        double side = std::sqrt(dx * dx + dy * dy);
        EXPECT_TRUE(doubleEquals(side, 5.0, 0.01));
    }
}

TEST(PentagonTest, CopyAssignment) {
    Pentagon pent1(1, 2, 6.0);
    Pentagon pent2;
    pent2 = pent1;
    
    EXPECT_TRUE(pent1 == pent2);
}

TEST(PentagonTest, EqualityOperator) {
    Pentagon pent1(1, 2, 6.0);
    Pentagon pent2(1, 2, 6.0);
    Pentagon pent3(1, 2, 7.0);
    
    EXPECT_TRUE(pent1 == pent2);
    EXPECT_FALSE(pent1 == pent3);
}

TEST(PentagonTest, OutputOperator) {
    Pentagon pent(0, 0, 5.0);
    std::ostringstream oss;
    oss << pent;
    
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Pentagon") != std::string::npos);
}

TEST(PentagonTest, InputOperator) {
    Pentagon pent;
    std::istringstream iss("2 3 5");
    iss >> pent;
    
    auto center = pent.Center();
    EXPECT_DOUBLE_EQ(center.first, 2.0);
    EXPECT_DOUBLE_EQ(center.second, 3.0);
}

TEST(PentagonTest, InvalidSideLength) {
    Pentagon pent;
    std::istringstream iss("0 0 -5");
    
    EXPECT_THROW(iss >> pent, std::invalid_argument);
}

//  ТЕСТЫ ДЛЯ HEXAGON 

TEST(HexagonTest, DefaultConstructor) {
    Hexagon hex;
    auto center = hex.Center();
    EXPECT_DOUBLE_EQ(center.first, 0.0);
    EXPECT_DOUBLE_EQ(center.second, 0.0);
}

TEST(HexagonTest, ParameterizedConstructor) {
    Hexagon hex(3.0, 4.0, 6.0);
    auto center = hex.Center();
    EXPECT_DOUBLE_EQ(center.first, 3.0);
    EXPECT_DOUBLE_EQ(center.second, 4.0);
}

TEST(HexagonTest, AreaCalculation) {
    Hexagon hex(0, 0, 4.0);
    double area = static_cast<double>(hex);
    double expectedArea = (3.0 * std::sqrt(3.0) * 16.0) / 2.0;
    EXPECT_TRUE(doubleEquals(area, expectedArea));
}

TEST(HexagonTest, GetVertices) {
    Hexagon hex(0, 0, 4.0);
    auto vertices = hex.GetVertices();
    EXPECT_EQ(vertices.size(), 6);
}

TEST(HexagonTest, VerticesFormRegularHexagon) {
    Hexagon hex(0, 0, 4.0);
    auto vertices = hex.GetVertices();
    
    // Проверяем, что все стороны примерно равны
    for (size_t i = 0; i < 6; ++i) {
        size_t next = (i + 1) % 6;
        double dx = vertices[next].first - vertices[i].first;
        double dy = vertices[next].second - vertices[i].second;
        double side = std::sqrt(dx * dx + dy * dy);
        EXPECT_TRUE(doubleEquals(side, 4.0, 0.01));
    }
}

TEST(HexagonTest, EqualityOperator) {
    Hexagon hex1(1, 2, 5.0);
    Hexagon hex2(1, 2, 5.0);
    Hexagon hex3(1, 2, 6.0);
    
    EXPECT_TRUE(hex1 == hex2);
    EXPECT_FALSE(hex1 == hex3);
}

TEST(HexagonTest, OutputOperator) {
    Hexagon hex(0, 0, 4.0);
    std::ostringstream oss;
    oss << hex;
    
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Hexagon") != std::string::npos);
}

TEST(HexagonTest, InputOperator) {
    Hexagon hex;
    std::istringstream iss("3 4 6");
    iss >> hex;
    
    auto center = hex.Center();
    EXPECT_DOUBLE_EQ(center.first, 3.0);
    EXPECT_DOUBLE_EQ(center.second, 4.0);
}

//  ТЕСТЫ ДЛЯ ARRAY 

TEST(ArrayTest, DefaultConstructor) {
    Array<Figure> arr;
    EXPECT_EQ(arr.getSize(), 0);
    EXPECT_TRUE(arr.isEmpty());
}

TEST(ArrayTest, AddElements) {
    Array<Figure> arr;
    
    arr.add(new Rhomb(0, 0, 4, 2));
    arr.add(new Pentagon(0, 0, 5));
    arr.add(new Hexagon(0, 0, 3));
    
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_FALSE(arr.isEmpty());
}

TEST(ArrayTest, GetElement) {
    Array<Figure> arr;
    Rhomb* rhomb = new Rhomb(1, 2, 6, 4);
    arr.add(rhomb);
    
    Figure* fig = arr.get(0);
    EXPECT_NE(fig, nullptr);
    
    auto* retrievedRhomb = dynamic_cast<Rhomb*>(fig);
    EXPECT_NE(retrievedRhomb, nullptr);
}

TEST(ArrayTest, OperatorBrackets) {
    Array<Figure> arr;
    arr.add(new Pentagon(2, 3, 5));
    
    Figure* fig = arr[0];
    EXPECT_NE(fig, nullptr);
    
    auto center = fig->Center();
    EXPECT_DOUBLE_EQ(center.first, 2.0);
    EXPECT_DOUBLE_EQ(center.second, 3.0);
}

TEST(ArrayTest, RemoveElement) {
    Array<Figure> arr;
    arr.add(new Rhomb(0, 0, 4, 2));
    arr.add(new Pentagon(0, 0, 5));
    arr.add(new Hexagon(0, 0, 3));
    
    EXPECT_EQ(arr.getSize(), 3);
    
    arr.remove(1);
    EXPECT_EQ(arr.getSize(), 2);
    
    // Проверяем, что элементы сдвинулись
    auto* hex = dynamic_cast<Hexagon*>(arr[1]);
    EXPECT_NE(hex, nullptr);
}

TEST(ArrayTest, RemoveInvalidIndex) {
    Array<Figure> arr;
    arr.add(new Rhomb(0, 0, 4, 2));
    
    EXPECT_THROW(arr.remove(5), std::out_of_range);
}

TEST(ArrayTest, GetInvalidIndex) {
    Array<Figure> arr;
    arr.add(new Rhomb(0, 0, 4, 2));
    
    EXPECT_THROW(arr.get(10), std::out_of_range);
}

TEST(ArrayTest, TotalAreaCalculation) {
    Array<Figure> arr;
    
    arr.add(new Rhomb(0, 0, 8, 6));    // Area = 24
    arr.add(new Rhomb(0, 0, 4, 2));    // Area = 4
    
    double totalArea = arr.getTotalArea();
    EXPECT_DOUBLE_EQ(totalArea, 28.0);
}

TEST(ArrayTest, TotalAreaEmpty) {
    Array<Figure> arr;
    EXPECT_DOUBLE_EQ(arr.getTotalArea(), 0.0);
}

TEST(ArrayTest, Clear) {
    Array<Figure> arr;
    arr.add(new Rhomb(0, 0, 4, 2));
    arr.add(new Pentagon(0, 0, 5));
    
    EXPECT_EQ(arr.getSize(), 2);
    
    arr.clear();
    EXPECT_EQ(arr.getSize(), 0);
    EXPECT_TRUE(arr.isEmpty());
}

TEST(ArrayTest, AutoResize) {
    Array<Figure> arr(2);
    
    arr.add(new Rhomb(0, 0, 4, 2));
    arr.add(new Pentagon(0, 0, 5));
    arr.add(new Hexagon(0, 0, 3));
    arr.add(new Rhomb(1, 1, 2, 2));
    
    EXPECT_EQ(arr.getSize(), 4);
}

TEST(ArrayTest, MoveConstructor) {
    Array<Figure> arr1;
    arr1.add(new Rhomb(0, 0, 4, 2));
    arr1.add(new Pentagon(0, 0, 5));
    
    Array<Figure> arr2(std::move(arr1));
    EXPECT_EQ(arr2.getSize(), 2);
    EXPECT_EQ(arr1.getSize(), 0);
}

TEST(ArrayTest, PrintAll) {
    Array<Figure> arr;
    arr.add(new Rhomb(0, 0, 4, 2));
    arr.add(new Pentagon(0, 0, 5));
    
    std::ostringstream oss;
    arr.printAll(oss);
    
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Figure #0") != std::string::npos);
    EXPECT_TRUE(output.find("Figure #1") != std::string::npos);
    EXPECT_TRUE(output.find("Total area") != std::string::npos);
}

TEST(ArrayTest, AddNullPointer) {
    Array<Figure> arr;
    EXPECT_THROW(arr.add(nullptr), std::invalid_argument);
}

TEST(ArrayTest, MixedFigures) {
    Array<Figure> arr;
    
    arr.add(new Rhomb(1, 1, 6, 4));
    arr.add(new Pentagon(2, 2, 5));
    arr.add(new Hexagon(3, 3, 4));
    
    EXPECT_EQ(arr.getSize(), 3);
    
    // Проверяем типы
    EXPECT_NE(dynamic_cast<Rhomb*>(arr[0]), nullptr);
    EXPECT_NE(dynamic_cast<Pentagon*>(arr[1]), nullptr);
    EXPECT_NE(dynamic_cast<Hexagon*>(arr[2]), nullptr);
}

//  MAIN 

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}