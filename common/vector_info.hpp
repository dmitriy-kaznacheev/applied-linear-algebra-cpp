#pragma once

#include <Eigen/Dense>
#include <iostream>
#include <string>

namespace info {

// выводит вектор, его размер и норму.
inline void vector(const Eigen::VectorXd &v, const std::string &label) {
    std::cout << label << ":  " << v.transpose() << "\n";
    std::cout << "Размер:  " << v.size() << "\n";
    std::cout << "Норма:   " << v.norm() << "\n";
    std::cout << "\n";
}

// выводит вектор и его норму в компактном виде: "v = ... |v| = ...".
inline void vector_compact(const Eigen::VectorXd &v, const std::string &label) {
    std::cout << label << " = " << v.transpose() << "   |" << label << "| = " << v.norm() << "\n";
}

// выводит два вектора и результаты базовых операций.
inline void two_vectors(const Eigen::VectorXd &a, const Eigen::VectorXd &b,
                        const std::string &label_a = "a", const std::string &label_b = "b") {
    std::cout << label_a << " = " << a.transpose() << "\n";
    std::cout << label_b << " = " << b.transpose() << "\n";
    std::cout << label_a << " + " << label_b << " = " << (a + b).transpose() << "\n";
    std::cout << label_a << " - " << label_b << " = " << (a - b).transpose() << "\n";
    std::cout << label_a << " · " << label_b << " = " << a.dot(b) << "\n";
}

}  // namespace info