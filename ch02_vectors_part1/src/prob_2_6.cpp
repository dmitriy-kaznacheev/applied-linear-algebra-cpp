// Упражнение 2.6: Квадрат нормы = скалярное произведение на себя.
// Раздел книги: "The Vector Dot Product".
//
// Задача: показать, что ||v||² = v·v (уравнение 2.8),
// и подтвердить это численно на разных векторах.

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <string>

#include "ch02.hpp"

namespace {

// проверяет тождество ||v||² == v·v и возвращает true, если совпало
bool check_identity(const std::string &label, const Eigen::VectorXd &v, double tolerance = 1e-10) {
    const double norm_sq = ch02::vector_norm(v) * ch02::vector_norm(v);
    const double dot_self = ch02::dot_product(v, v);
    const double diff = std::abs(norm_sq - dot_self);
    const bool ok = diff < tolerance;

    std::cout << label << " = " << v.transpose() << "\n";
    std::cout << "  ||v||²    = " << norm_sq << "\n";
    std::cout << "  v · v     = " << dot_self << "\n";
    std::cout << "  |разница| = " << diff << "\n";
    std::cout << "  совпадает: " << (ok ? "да" : "НЕТ") << "\n\n";

    return ok;
}

}  // namespace

int main() {
    std::cout << "Проверка тождества: ||v||² == v·v\n\n";

    check_identity("a", Eigen::Vector3d(3.0, 4.0, 0.0));
    check_identity("b", Eigen::Vector3d(1.0, 2.0, 3.0));
    check_identity("c", Eigen::Vector3d(-1.0, 0.0, 1.0));

    std::cout << "Случайные векторы:\n\n";

    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    for (int dim : {2, 5, 20}) {
        Eigen::VectorXd v(dim);
        std::generate(v.data(), v.data() + v.size(), [&]() { return dist(rng); });

        check_identity("размерность " + std::to_string(dim), v);
    }

    std::cout << "Геометрически: v·v = |v|·|v|·cos(0°) = |v|².\n";

    return 0;
}