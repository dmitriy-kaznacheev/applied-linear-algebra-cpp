// Упражнение 2.1: Код для рис. 2.2 — сумма и разность двух векторов.
// Раздел книги: "Creating and Visualizing Vectors" / "Geometry of Vector
// Addition and Subtraction".
//
// Демонстрирует:
//   - два исходных вектора a и b из начала координат
//   - сумму a + b (правило параллелограмма)
//   - разность a - b (от головы b к голове a)

#include <iostream>

#include "ch02.hpp"
#include "plot_helpers.hpp"
#include "vector_info.hpp"

int main() {
    Eigen::Vector2d v(1.0, 2.0);
    Eigen::Vector2d w(4.0, -6.0);

    info::two_vectors(v, w, "v", "w");

    plot::show_sum_and_diff(v, w, "Сумма и разность двух векторов", {-6, 6}, {-6, 6});

    return 0;
}