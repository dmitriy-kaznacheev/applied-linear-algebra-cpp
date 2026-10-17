// Глава 2, пример 3: Длина вектора и единичные векторы.
// Раздел книги: "Vector Magnitude and Unit Vectors".
//
// Демонстрирует:
//   - вычисление нормы (длины) вектора
//   - получение единичного вектора (нормализация)
//   - проверку, что норма единичного вектора равна 1

#include <iostream>

#include "ch02.hpp"
#include "vector_info.hpp"

int main() {
    Eigen::Vector3d v(3.0, 4.0, 0.0);
    info::vector(v, "Вектор");

    Eigen::Vector3d u = ch02::unit_vector(v);
    info::vector(u, "Единичный");

    Eigen::Vector3d zero(0.0, 0.0, 0.0);
    info::vector(zero, "Нулевой");

    return 0;
}