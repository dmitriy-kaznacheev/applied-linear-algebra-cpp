// Упражнение 2.5: Транспонирование циклом.
// Раздел книги: "Operations on Vectors" (Transpose).
//
// Задача: написать цикл for для транспонирования вектора-строки
// в вектор-столбец (или наоборот) без использования встроенных
// функций вроде .transpose() или v.T.
//
// В C++ вектор — это матрица N×1, а его транспонирование — 1×N.
// Реализация transpose_manual создаёт матрицу 1×N и заполняет
// её элементами исходного вектора через цикл.

#include <iostream>
#include <string>

#include "ch02.hpp"

namespace {

// выводит матрицу и её размер
void print_matrix(const std::string &label, const Eigen::MatrixXd &m) {
    std::cout << label << ":\n" << m << "\n";
    std::cout << "Размер: " << m.rows() << "x" << m.cols() << "\n\n";
}

}  // namespace

int main() {
    Eigen::VectorXd v(5);
    v << 1.0, 2.0, 3.0, 4.0, 5.0;

    print_matrix("Исходный вектор (столбец)", v);

    // ручное транспонирование циклом
    Eigen::MatrixXd manual = ch02::transpose_manual(v);
    print_matrix("После transpose_manual (строка)", manual);

    // сравнение со встроенным .transpose()
    Eigen::MatrixXd builtin = v.transpose();
    print_matrix("Встроенный .transpose()", builtin);

    std::cout << "Совпадает? " << (manual.isApprox(builtin) ? "да" : "НЕТ") << "\n";

    // поэлементная проверка
    std::cout << "\nПоэлементная проверка:\n";
    for (Eigen::Index i = 0; i < v.size(); ++i) {
        std::cout << "  manual(0," << i << ") = " << manual(0, i) << "   v(" << i << ") = " << v(i)
                  << "\n";
    }

    return 0;
}