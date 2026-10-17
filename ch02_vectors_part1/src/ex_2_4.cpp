// Глава 2, пример 4: Скалярное произведение.
// Раздел книги: "The Vector Dot Product".
//
// Демонстрирует:
//   - вычисление a · b
//   - коммутативность: a·b == b·a
//   - дистрибутивность: a·(b+c) == a·b + a·c
//   - ортогональность: a·b == 0 для перпендикулярных векторов

#include <iostream>

#include "ch02.hpp"
#include "vector_info.hpp"

int main() {
    Eigen::Vector3d a(1.0, 2.0, 3.0);
    Eigen::Vector3d b(4.0, 5.0, 6.0);
    Eigen::Vector3d c(1.0, 0.0, -1.0);

    info::vector_compact(a, "a");
    info::vector_compact(b, "b");
    info::vector_compact(c, "c");

    std::cout << "\nскалярное произведение:\n";
    std::cout << "a · b = " << ch02::dot_product(a, b) << "\n";
    std::cout << "b · a = " << ch02::dot_product(b, a) << "\n";

    std::cout << "\nдистрибутивность:\n";
    {
        double lhs = ch02::dot_product(a, b + c);
        double rhs = ch02::dot_product(a, b) + ch02::dot_product(a, c);
        std::cout << "a · (b + c) = " << lhs << "\n";
        std::cout << "a·b + a·c   = " << rhs << "\n";
    }

    std::cout << "\nскалярное произведение перпендикулярных векторов равно 0:\n";
    {
        Eigen::Vector3d x(1.0, 0.0, 0.0);
        Eigen::Vector3d y(0.0, 1.0, 0.0);
        info::vector_compact(x, "x");
        info::vector_compact(y, "y");
        std::cout << "x · y = " << ch02::dot_product(x, y) << "\n";
    }

    return 0;
}