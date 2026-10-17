// Упражнение 2.3: Единичный вектор и поведение для нулевого вектора.
// Раздел книги: "Vector Magnitude and Unit Vectors".
//
// Задача: создать функцию, которая принимает вектор и возвращает
// единичный вектор того же направления. Что происходит при вводе
// вектора нулей?
//
// В моей реализации ch02::unit_vector для нулевого вектора
// возвращает нулевой вектор — безопасное поведение без NaN.

#include <iostream>

#include "ch02.hpp"
#include "vector_info.hpp"

namespace {

// выводит исходный вектор и его единичный вектор
void print_unit(const std::string &label, const Eigen::VectorXd &v) {
    std::cout << label << ":\n";
    info::vector_compact(v, "v");
    info::vector_compact(ch02::unit_vector(v), "unit(v)");
    std::cout << "\n";
}

}  // namespace

int main() {
    std::cout << "Единичные векторы для разных направлений:\n\n";

    print_unit("стандартный (3, 4, 0)", Eigen::Vector3d(3.0, 4.0, 0.0));
    print_unit("единичный по оси X", Eigen::Vector3d(1.0, 0.0, 0.0));
    print_unit("отрицательный по оси X", Eigen::Vector3d(-2.0, 0.0, 0.0));

    // граничный случай: нулевой вектор
    print_unit("граничный случай — нулевой вектор:", Eigen::Vector3d::Zero());
    std::cout << "Вывод: для нулевого вектора направление не определено,\n";
    std::cout << "поэтому возвращаем нулевой вектор — это безопаснее, чем NaN.\n";

    return 0;
}