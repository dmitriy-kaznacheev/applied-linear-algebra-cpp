#pragma once

#include <Eigen/Dense>

namespace ch02 {

// норма и единичный вектор (с проверкой на ноль)
double vector_norm(const Eigen::VectorXd &v);
Eigen::VectorXd unit_vector(const Eigen::VectorXd &v);

// скалярное произведение и угол
double dot_product(const Eigen::VectorXd &a, const Eigen::VectorXd &b);
double angle_between(const Eigen::VectorXd &a, const Eigen::VectorXd &b);

// проекция и ортогональная составляющая
Eigen::VectorXd project_onto(const Eigen::VectorXd &v, const Eigen::VectorXd &onto);
Eigen::VectorXd orthogonal_component(const Eigen::VectorXd &v, const Eigen::VectorXd &onto);

// произведение Адамара (поэлементное)
Eigen::VectorXd hadamard_product(const Eigen::VectorXd &a, const Eigen::VectorXd &b);

// внешнее произведение a ⊗ b
Eigen::MatrixXd outer_product(const Eigen::VectorXd &a, const Eigen::VectorXd &b);

// векторное произведение (определено только для 3D-векторов)
Eigen::Vector3d cross_product(const Eigen::Vector3d &a, const Eigen::Vector3d &b);

// смешанное (тройное) произведение: a · (b × c)
// геометрический смысл: объём параллелепипеда, построенного на a, b, c
double triple_product(const Eigen::Vector3d &a, const Eigen::Vector3d &b, const Eigen::Vector3d &c);

// упражнение 2.2: норма через явную формулу sqrt(Σvᵢ²)
double vector_norm_manual(const Eigen::VectorXd &v);

// упражнение 2.4: вектор того же направления, но заданного модуля
// для нулевого вектора возвращает нулевой вектор
Eigen::VectorXd set_magnitude(const Eigen::VectorXd &v, double magnitude);

// упражнение 2.5: транспонирование через цикл (без transpose())
// возвращает матрицу 1×N (вектор-строку)
Eigen::MatrixXd transpose_manual(const Eigen::VectorXd &v);

// упражнение 2.10: ошибочная проекция — знаменатель v·v вместо onto·onto.
// используется только для упражнения: результат неверный
Eigen::VectorXd project_onto_wrong(const Eigen::VectorXd &v, const Eigen::VectorXd &onto);

}  // namespace ch02