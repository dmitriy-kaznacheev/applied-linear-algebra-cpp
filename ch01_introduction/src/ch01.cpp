#include "ch01.hpp"

namespace ch01 {

double vector_norm(const Eigen::VectorXd &v) {
    return v.norm();
}

Eigen::VectorXd unit_vector(const Eigen::VectorXd &v) {
    return v / v.norm();
}

}  // namespace ch01