#pragma once

#include <Eigen/Dense>

namespace ch01 {

// евклидова норма (длина) вектора
double vector_norm(const Eigen::VectorXd &v);

// единичный вектор того же направления что и v
// для нулевого вектора UB (деление на ноль)
Eigen::VectorXd unit_vector(const Eigen::VectorXd &v);

}  // namespace ch01