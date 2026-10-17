// Глава 2, пример 7: Ортогональное разложение вектора.
// Раздел книги: "Orthogonal Vector Decomposition".
//
// Демонстрирует:
//   - проекцию вектора v на направление onto
//   - ортогональную составляющую (v минус проекция)
//   - что проекция и ортогональная составляющая перпендикулярны
//   - что их сумма равна исходному вектору

#include <iostream>

#include "ch02.hpp"
#include "vector_info.hpp"

namespace {

void print_info(const Eigen::VectorXd &v, const Eigen::VectorXd &onto, const Eigen::VectorXd &proj,
                const Eigen::VectorXd &orth) {
    info::vector_compact(v, "v");
    info::vector_compact(onto, "onto");

    std::cout << "\nразложение: \n";
    info::vector_compact(proj, "proj");
    info::vector_compact(orth, "orth");

    std::cout << "\nпроверки:\n";
    std::cout << "proj · orth = " << ch02::dot_product(proj, orth) << "   (должны быть ⟂)\n";

    std::cout << "\nv = proj + orth:\n";
    info::vector_compact((proj + orth), "proj + orth");
}

}  // namespace

int main() {
    {
        std::cout << "\n--- Разложение вдоль одной из осей ---\n\n";

        Eigen::Vector2d v(2.0, 3.0);
        Eigen::Vector2d onto(1.0, 0.0);

        Eigen::Vector2d proj = ch02::project_onto(v, onto);
        Eigen::Vector2d orth = ch02::orthogonal_component(v, onto);

        print_info(v, onto, proj, orth);
    }

    {
        std::cout << "\n--- Произвольное направление (не по оси) ---\n\n";
        Eigen::Vector2d v(3.0, 4.0);
        Eigen::Vector2d onto(1.0, 1.0);

        Eigen::Vector2d proj = ch02::project_onto(v, onto);
        Eigen::Vector2d orth = ch02::orthogonal_component(v, onto);

        print_info(v, onto, proj, orth);
    }

    return 0;
}