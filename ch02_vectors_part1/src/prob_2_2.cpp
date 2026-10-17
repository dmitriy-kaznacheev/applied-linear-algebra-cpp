// Упражнение 2.2: Норма через явную формулу.
// Раздел книги: "Vector Magnitude and Unit Vectors".
//
// Задача: написать алгоритм, вычисляющий норму вектора через уравнение 2.7
// (sqrt(Σvᵢ²)), и подтвердить на случайных векторах разных размерностей,
// что результат совпадает с встроенной нормой.
//
// В C++ роль np.linalg.norm() играет v.norm() из Eigen.

#include <cmath>
#include <iostream>
#include <random>

#include "ch02.hpp"

namespace {

// выводит сравнение ручной нормы и Eigen::norm()
// возвращает true, если результаты совпадают в пределах допуска
bool print_comparison(const std::string &label, const Eigen::VectorXd &v,
                      double tolerance = 1e-10) {
    const double manual = ch02::vector_norm_manual(v);
    const double eigen = ch02::vector_norm(v);
    const double diff = std::abs(manual - eigen);
    const bool ok = diff < tolerance;

    std::cout << label << ":\n";
    std::cout << "  ручная норма  = " << manual << "\n";
    std::cout << "  Eigen::norm() = " << eigen << "\n";
    std::cout << "  |разница|     = " << diff << "\n";
    std::cout << "  совпадает     : " << (ok ? "да" : "НЕТ") << "\n\n";

    return ok;
}

}  // namespace

int main() {
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    std::cout << "Сравнение ручной нормы (sqrt(Σvᵢ²)) с Eigen::norm()\n\n";

    for (int dim : {2, 3, 5, 10, 100}) {
        Eigen::VectorXd v(dim);
        std::generate(v.data(), v.data() + v.size(), [&]() { return dist(rng); });
        print_comparison("Размерность " + std::to_string(dim), v);
    }

    std::cout << "Граничные случаи:\n\n";

    Eigen::Vector3d zero = Eigen::Vector3d::Zero();
    print_comparison("  нулевой вектор", zero);

    Eigen::Vector3d ones = Eigen::Vector3d::Ones();
    print_comparison("  вектор из единиц", ones);

    return 0;
}