// Упражнение 2.7: Коммутативность скалярного произведения.
// Раздел книги: "The Vector Dot Product".
//
// Задача: написать код, демонстрирующий, что a·b == b·a.
// Затем применить уравнение 2.9, чтобы понять, почему это так.
//
// Уравнение 2.9: a·b = Σ aᵢ·bᵢ. Поскольку умножение чисел
// коммутативно (aᵢ·bᵢ = bᵢ·aᵢ), сумма тоже не меняется.

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <string>

#include "ch02.hpp"
#include "vector_info.hpp"

namespace {

// проверяет a·b == b·a и выводит результат
bool check_commutative(const std::string &label, const Eigen::VectorXd &a, const Eigen::VectorXd &b,
                       double tolerance = 1e-12) {
    const double ab = ch02::dot_product(a, b);
    const double ba = ch02::dot_product(b, a);
    const double diff = std::abs(ab - ba);
    const bool ok = diff < tolerance;

    std::cout << label << ":\n";
    std::cout << "  a = " << a.transpose() << "\n";
    std::cout << "  b = " << b.transpose() << "\n";
    std::cout << "  a · b = " << ab << "\n";
    std::cout << "  b · a = " << ba << "\n";
    std::cout << "  |разница| = " << diff << "\n";
    std::cout << "  совпадает: " << (ok ? "да" : "НЕТ") << "\n\n";

    return ok;
}

}  // namespace

int main() {
    std::cout << "Проверка коммутативности: a·b == b·a\n\n";

    check_commutative("Конкретные векторы", Eigen::Vector3d(1.0, 2.0, 3.0),
                      Eigen::Vector3d(4.0, 5.0, 6.0));

    std::cout << "Случайные векторы:\n\n";

    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    for (int trial = 1; trial <= 3; ++trial) {
        Eigen::VectorXd x(5);
        Eigen::VectorXd y(5);
        std::generate(x.data(), x.data() + x.size(), [&]() { return dist(rng); });
        std::generate(y.data(), y.data() + y.size(), [&]() { return dist(rng); });

        check_commutative("Попытка " + std::to_string(trial), x, y);
    }

    std::cout << "Почему это работает (уравнение 2.9):\n";
    std::cout << "  a·b = Σ aᵢ·bᵢ\n";
    std::cout << "  b·a = Σ bᵢ·aᵢ\n";
    std::cout << "  Поскольку aᵢ·bᵢ = bᵢ·aᵢ для каждого i,\n";
    std::cout << "  суммы совпадают: a·b = b·a.\n";

    return 0;
}