// Глава 2, пример 5: Угол между векторами.
// Раздел книги: "Geometry of the Dot Product".
//
// Демонстрирует:
//   - cos(θ) = a·b / (|a|·|b|)
//   - угол между сонаправленными векторами = 0
//   - угол между ортогональными = π/2
//   - угол между противоположными = π
//   - угол между произвольными векторами

#include <cmath>
#include <iostream>

#include "ch02.hpp"
#include "vector_info.hpp"

namespace {

void print_angle(const std::string &label, const Eigen::VectorXd &a, const Eigen::VectorXd &b) {
    auto to_deg = [](double rad) { return rad * 180.0 / M_PI; };

    {
        double theta_rad = ch02::angle_between(a, b);
        std::cout << label << ":\n";
        info::vector_compact(a, "a");
        info::vector_compact(b, "b");
        std::cout << "θ = " << to_deg(theta_rad) << "° (" << theta_rad << " рад)\n";
    }

    // проверка по формуле: cos(θ) = a·b / (|a|·|b|)
    {
        double cos_theta = ch02::dot_product(a, b) / (ch02::vector_norm(a) * ch02::vector_norm(b));
        double theta_rad = std::acos(cos_theta);
        std::cout << "проверка по формуле:\n";
        std::cout << "  cos(θ) = " << cos_theta << "\n";
        std::cout << "  θ      = " << to_deg(theta_rad) << "° (" << theta_rad << " рад)\n";
        std::cout << "\n";
    }
}

}  // namespace

int main() {
    print_angle("Сонаправленные", Eigen::Vector3d(1.0, 0.0, 0.0), Eigen::Vector3d(2.0, 0.0, 0.0));
    print_angle("Ортогональные", Eigen::Vector3d(1.0, 0.0, 0.0), Eigen::Vector3d(0.0, 1.0, 0.0));
    print_angle("Противоположные", Eigen::Vector3d(1.0, 0.0, 0.0), Eigen::Vector3d(-1.0, 0.0, 0.0));
    print_angle("Произвольные", Eigen::Vector3d(1.0, 2.0, 3.0), Eigen::Vector3d(4.0, 5.0, 6.0));

    return 0;
}