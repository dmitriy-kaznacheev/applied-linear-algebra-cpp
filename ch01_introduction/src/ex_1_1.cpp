#include <iostream>

#include "ch01.hpp"

int main() {
    Eigen::Vector3d v(3.0, 4.0, 0.0);

    std::cout << "Вектор:    " << v.transpose() << "\n";
    std::cout << "Норма:     " << ch01::vector_norm(v) << "\n";
    std::cout << "Единичный: " << ch01::unit_vector(v).transpose() << "\n";

    return 0;
}