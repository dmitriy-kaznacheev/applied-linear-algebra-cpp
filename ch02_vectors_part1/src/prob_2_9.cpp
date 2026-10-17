// Упражнение 2.9: Ортогональное разложение векторов.
// Раздел книги: "Orthogonal Vector Decomposition".

#include <iostream>

#include "ch02.hpp"
#include "plot_helpers.hpp"
#include "vector_info.hpp"

int main() {
    Eigen::Vector2d r(-1.2, 0.7);
    Eigen::Vector2d t(-0.8, 0.2);

    info::vector_compact(r, "r");
    info::vector_compact(t, "t");

    Eigen::Vector2d t_parallel = ch02::project_onto(t, r);
    Eigen::Vector2d t_perp = ch02::orthogonal_component(t, r);

    info::vector_compact(t_parallel, "t_parallel");
    info::vector_compact(t_perp, "t_perp");

    // вывод на консоль
    {
        std::cout << "\n";
        std::cout << "Свойства разложения:\n";
        std::cout << "  t_parallel + t_perp = t? "
                  << ((t_parallel + t_perp).isApprox(t) ? "да" : "НЕТ") << "\n";

        std::cout << "  t_parallel ∥ r?          "
                  << (t_parallel.isApprox(t_parallel.dot(r) / r.squaredNorm() * r) ? "да" : "НЕТ")
                  << "\n";

        std::cout << "  t_parallel ⟂ t_perp?     "
                  << (std::abs(ch02::dot_product(t_parallel, t_perp)) < 1e-10 ? "да" : "НЕТ")
                  << "\n\n";
    }

    // отрисовка
    plot::show_orthogonal_decomposition(t, r, "Ортогональное разложение", {-1.5, 0.2}, {-0.4, 0.9});

    return 0;
}