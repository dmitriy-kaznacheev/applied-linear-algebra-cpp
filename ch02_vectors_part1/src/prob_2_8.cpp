// Упражнение 2.8: Код для рис. 2.6 (геометрия скалярного произведения).
// Раздел книги: "Geometry of the Dot Product".
//
// Два вектора, проекция и перпендикуляр от конца b к прямой a.

#include <cmath>
#include <iostream>

#include "ch02.hpp"
#include "plot_helpers.hpp"
#include "vector_info.hpp"

int main() {
    Eigen::Vector2d a(2.0, 4.0);
    Eigen::Vector2d b(4.0, 1.0);

    const double dot = ch02::dot_product(a, b);
    const double angle_rad = ch02::angle_between(a, b);
    const double angle_deg = angle_rad * 180.0 / M_PI;

    info::vector_compact(a, "a");
    info::vector_compact(b, "b");
    std::cout << "a · b = " << dot << "\n";
    std::cout << "Угол:  " << angle_rad << " рад = " << angle_deg << "°\n";

    const Eigen::Vector2d proj = ch02::project_onto(b, a);
    const Eigen::Vector2d error = b - proj;

    std::cout << "\n";
    info::vector_compact(proj, "proj");
    info::vector_compact(error, "error");
    std::cout << "proj · error = " << ch02::dot_product(proj, error) << "\n";

    plot::show_projection_with_onto(b, a, "Проекция b на a", {-1, 4}, {-1, 4});

    return 0;
}