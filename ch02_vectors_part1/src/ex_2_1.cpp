// Глава 2, пример 1: Создание и визуализация векторов.
// Раздел книги: "Creating and Visualizing Vectors".

#include <iostream>

#include "ch02.hpp"
#include "plot_helpers.hpp"
#include "vector_info.hpp"

int main() {
    Eigen::Vector3d v(2.0, -1.0, 3.5);
    info::vector(v, "Вектор");

    Eigen::Vector2d v2d = v.head<2>();
    plot::show_vector(v2d, "v = (2, -1)", "Вектор (2, -1)", {-4, 4}, {-4, 4});

    return 0;
}