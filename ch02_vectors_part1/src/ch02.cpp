#include "ch02.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace ch02 {

double vector_norm(const Eigen::VectorXd &v) {
    return v.norm();
}

Eigen::VectorXd unit_vector(const Eigen::VectorXd &v) {
    const double n = v.norm();

    // для нулевого вектора norm() возвращает ровно 0.0 (IEEE 754: sqrt(0) = 0),
    // поэтому сравнение с 0.0 корректно — это не приблизительное значение
    if (n == 0.0) {
        return Eigen::VectorXd::Zero(v.size());
    }

    return v / n;
}

double dot_product(const Eigen::VectorXd &a, const Eigen::VectorXd &b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("dot_product: размеры векторов не совпадают");
    }
    return a.dot(b);
}

double angle_between(const Eigen::VectorXd &a, const Eigen::VectorXd &b) {
    const double na = a.norm();
    const double nb = b.norm();
    if (na == 0.0 || nb == 0.0) {
        throw std::invalid_argument("angle_between: нулевой вектор не имеет направления");
    }

    // cos(θ) = a·b / (|a|·|b|)
    // из-за погрешностей округления значение может выйти за [-1, 1]
    double cos_theta = a.dot(b) / (na * nb);
    cos_theta = std::clamp(cos_theta, -1.0, 1.0);

    return std::acos(cos_theta);
}

Eigen::VectorXd project_onto(const Eigen::VectorXd &v, const Eigen::VectorXd &onto) {
    const double denom = onto.squaredNorm();
    if (denom == 0.0) {
        throw std::invalid_argument("project_onto: нельзя проецировать на нулевой вектор");
    }
    return (v.dot(onto) / denom) * onto;
}

Eigen::VectorXd orthogonal_component(const Eigen::VectorXd &v, const Eigen::VectorXd &onto) {
    return v - project_onto(v, onto);
}

Eigen::VectorXd hadamard_product(const Eigen::VectorXd &a, const Eigen::VectorXd &b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("hadamard_product: размеры векторов не совпадают");
    }
    return (a.array() * b.array()).matrix();
}

Eigen::MatrixXd outer_product(const Eigen::VectorXd &a, const Eigen::VectorXd &b) {
    return a * b.transpose();
}

Eigen::Vector3d cross_product(const Eigen::Vector3d &a, const Eigen::Vector3d &b) {
    return a.cross(b);
}

double triple_product(const Eigen::Vector3d &a, const Eigen::Vector3d &b,
                      const Eigen::Vector3d &c) {
    return a.dot(b.cross(c));
}

// --- Функции для упражнений ---

double vector_norm_manual(const Eigen::VectorXd &v) {
    double sum = 0.0;
    for (Eigen::Index i = 0; i != v.size(); ++i) {
        sum += v(i) * v(i);
    }
    return std::sqrt(sum);
}

Eigen::VectorXd set_magnitude(const Eigen::VectorXd &v, double magnitude) {
    const double n = v.norm();
    if (n == 0.0) {
        return Eigen::VectorXd::Zero(v.size());
    }
    return (magnitude / n) * v;
}

Eigen::MatrixXd transpose_manual(const Eigen::VectorXd &v) {
    Eigen::MatrixXd result(1, v.size());
    for (Eigen::Index i = 0; i != v.size(); ++i) {
        result(0, i) = v(i);
    }
    return result;
}

Eigen::VectorXd project_onto_wrong(const Eigen::VectorXd &v, const Eigen::VectorXd &onto) {
    // ОШИБКА: знаменатель должен быть onto.squaredNorm(), а не v.squaredNorm()
    // функция реализована только для упражнения 2.10
    const double denom = v.squaredNorm();
    if (denom == 0.0) {
        throw std::invalid_argument("project_onto_wrong: нулевой вектор");
    }
    return (v.dot(onto) / denom) * onto;
}

}  // namespace ch02