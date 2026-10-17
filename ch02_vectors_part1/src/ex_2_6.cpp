// Глава 2, пример 6: Другие виды умножения векторов.
// Раздел книги: "Other Vector Multiplications".
//
// Демонстрирует:
//   - произведение Адамара (поэлементное умножение)
//   - внешнее произведение (outer product)
//   - векторное произведение (cross product, только 3D)

#include <iostream>

#include "ch02.hpp"
#include "vector_info.hpp"

int main() {
    Eigen::Vector3d a(1.0, 2.0, 3.0);
    Eigen::Vector3d b(4.0, 5.0, 6.0);

    info::vector_compact(a, "a");
    info::vector_compact(b, "b");

    {
        std::cout << "\n--- Произведение Адамара (поэлементное) ---\n";
        Eigen::Vector3d hadamard = ch02::hadamard_product(a, b);
        info::vector_compact(hadamard, "a ∘ b");
    }

    {
        std::cout << "\n--- Внешнее произведение ---\n";
        Eigen::Matrix3d outer = ch02::outer_product(a, b);
        std::cout << "a ⊗ b =\n" << outer << "\n";
    }

    {
        std::cout << "\n--- Векторное произведение (только 3D) ---\n";
        Eigen::Vector3d cross = ch02::cross_product(a, b);
        info::vector_compact(cross, "a × b");

        // свойства векторного произведения: (a×b ⟂ a) и (a×b ⟂ b)
        std::cout << "\nпроверка ортогональности: (a×b ⟂ a) и (a×b ⟂ b)\n";
        std::cout << "  (a × b) · a = " << ch02::dot_product(cross, a) << "\n";
        std::cout << "  (a × b) · b = " << ch02::dot_product(cross, b) << "\n";
    }

    {
        std::cout << "\n--- Смешанное (тройное) произведение: a · (b × c) ---\n";
        std::cout << "\nгеометрический смысл: объём параллелепипеда на рёбрах a, b, c\n";

        Eigen::Vector3d c(1.0, 0.0, -1.0);
        info::vector_compact(c, "c");

        std::cout << "\nсвойства: циклическая перестановка не меняет результа\n";
        std::cout << "a · (b × c) = " << ch02::triple_product(a, b, c) << "\n";
        std::cout << "b · (c × a) = " << ch02::triple_product(b, c, a) << "\n";
        std::cout << "c · (a × b) = " << ch02::triple_product(c, a, b) << "\n";

        std::cout << "\nесли векторы компланарны (лежат в одной плоскости), объём = 0\n";
        Eigen::Vector3d d(2.0, 4.0, 6.0);  // d = 2*a, коллинеарен a
        info::vector_compact(d, "d");
        std::cout << "a · (b × d) = " << ch02::triple_product(a, b, d)
                  << "   (d = 2*a, коллинеарен a)\n";
    }

    return 0;
}