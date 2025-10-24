#include <iostream>
#include <memory>
#include "Figure.hpp"
#include "Rhomb.hpp"
#include "Pentagon.hpp"
#include "Hexagon.hpp"
#include "Array.hpp"

void printMenu() {
    std::cout << "\n=== Figure Manager ===\n";
    std::cout << "1. Add Rhombus\n";
    std::cout << "2. Add Pentagon\n";
    std::cout << "3. Add Hexagon\n";
    std::cout << "4. Print all figures\n";
    std::cout << "5. Calculate total area\n";
    std::cout << "6. Remove figure by index\n";
    std::cout << "7. Exit\n";
    std::cout << "Choice: ";
}

int main() {
    Array<Figure> figures;
    int choice;
    
    while (true) {
        printMenu();
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input!\n";
            continue;
        }
        
        try {
            switch (choice) {
                case 1: {
                    Rhomb* rhomb = new Rhomb();
                    std::cin >> *rhomb;
                    figures.add(rhomb);
                    std::cout << "Rhombus added!\n";
                    break;
                }
                case 2: {
                    Pentagon* pent = new Pentagon();
                    std::cin >> *pent;
                    figures.add(pent);
                    std::cout << "Pentagon added!\n";
                    break;
                }
                case 3: {
                    Hexagon* hex = new Hexagon();
                    std::cin >> *hex;
                    figures.add(hex);
                    std::cout << "Hexagon added!\n";
                    break;
                }
                case 4: {
                    figures.printAll(std::cout);
                    break;
                }
                case 5: {
                    std::cout << "Total area: " << figures.getTotalArea() << "\n";
                    break;
                }
                case 6: {
                    size_t index;
                    std::cout << "Enter index to remove: ";
                    std::cin >> index;
                    figures.remove(index);
                    std::cout << "Figure removed!\n";
                    break;
                }
                case 7: {
                    std::cout << "Goodbye!\n";
                    return 0;
                }
                default: {
                    std::cout << "Invalid choice!\n";
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
    
    return 0;
}