// Упражнение 2.4: Вектор заданного модуля.
// Раздел книги: "Vector Magnitude and Unit Vectors".
//
// Задача: написать функцию, которая принимает вектор и желаемый модуль
// и возвращает вектор в том же направлении, но с заданным модулем.
//
// Реализация: set_magnitude(v, m) = (m / |v|) * v.
// Для нулевого вектора направление не определено — возвращаем нулевой.

#include <iostream>
#include <vector_info.hpp>

#include "ch02.hpp"

namespace {

// выводит результат set_magnitude и проверяет, что направление сохранено.
void print_result(const std::string &label, const Eigen::VectorXd &original,
                  const Eigen::VectorXd &result) {
    std::cout << label << ":\n";
    info::vector_compact(result, "  result");
    std::cout << "  направление = " << ch02::unit_vector(result).transpose() << "\n";
    std::cout << "  совпадает с unit(v)? "
              << (ch02::unit_vector(result).isApprox(ch02::unit_vector(original)) ? "да" : "НЕТ")
              << "\n\n";
}

}  // namespace

int main() {
    Eigen::Vector3d v(3.0, 4.0, 0.0);

    info::vector_compact(v, "v");
    std::cout << "\n";

    for (double m : {1.0, 2.5, 10.0, 0.5}) {
        print_result("Желаемый модуль " + std::to_string(m), v, ch02::set_magnitude(v, m));
    }

    // граничный случай: нулевой вектор
    Eigen::Vector3d zero = Eigen::Vector3d::Zero();
    print_result("Нулевой вектор с модулем 5", zero, ch02::set_magnitude(zero, 5));
    std::cout << "  Вывод: направление не определено — вернули нулевой вектор\n";

    return 0;
}