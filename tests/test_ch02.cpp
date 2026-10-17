#include <gtest/gtest.h>

#include <cmath>

#include "ch02.hpp"

// --- Норма ---

TEST(Ch02_VectorNorm, StandardBasis) {
    Eigen::Vector3d v(3.0, 4.0, 0.0);
    EXPECT_DOUBLE_EQ(ch02::vector_norm(v), 5.0);
}

TEST(Ch02_VectorNorm, ZeroVector) {
    Eigen::Vector3d v(0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(ch02::vector_norm(v), 0.0);
}

// --- Единичный вектор ---

TEST(Ch02_UnitVector, HasUnitNorm) {
    Eigen::Vector3d v(3.0, 4.0, 0.0);
    EXPECT_DOUBLE_EQ(ch02::unit_vector(v).norm(), 1.0);
}

TEST(Ch02_UnitVector, SameDirection) {
    Eigen::Vector3d v(3.0, 4.0, 0.0);
    Eigen::Vector3d u = ch02::unit_vector(v);

    EXPECT_DOUBLE_EQ(u(0), 0.6);
    EXPECT_DOUBLE_EQ(u(1), 0.8);
    EXPECT_DOUBLE_EQ(u(2), 0.0);
}

TEST(Ch02_UnitVector, ZeroVectorReturnsZero) {
    Eigen::Vector3d v(0.0, 0.0, 0.0);
    Eigen::Vector3d u = ch02::unit_vector(v);

    EXPECT_DOUBLE_EQ(u.norm(), 0.0);
}

// --- Скалярное произведение ---

TEST(Ch02_DotProduct, Basic) {
    Eigen::Vector3d a(1.0, 2.0, 3.0);
    Eigen::Vector3d b(4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(ch02::dot_product(a, b), 32.0);
}

TEST(Ch02_DotProduct, OrthogonalVectors) {
    Eigen::Vector3d a(1.0, 0.0, 0.0);
    Eigen::Vector3d b(0.0, 1.0, 0.0);
    EXPECT_DOUBLE_EQ(ch02::dot_product(a, b), 0.0);
}

TEST(Ch02_DotProduct, SizeMismatchThrows) {
    Eigen::VectorXd a(3);
    a << 1.0, 2.0, 3.0;
    Eigen::VectorXd b(2);
    b << 1.0, 2.0;

    EXPECT_THROW(ch02::dot_product(a, b), std::invalid_argument);
}

// --- Угол между векторами ---

TEST(Ch02_AngleBetween, SameDirection) {
    Eigen::Vector3d a(1.0, 0.0, 0.0);
    Eigen::Vector3d b(2.0, 0.0, 0.0);
    EXPECT_NEAR(ch02::angle_between(a, b), 0.0, 1e-12);
}

TEST(Ch02_AngleBetween, Orthogonal) {
    Eigen::Vector3d a(1.0, 0.0, 0.0);
    Eigen::Vector3d b(0.0, 1.0, 0.0);
    EXPECT_NEAR(ch02::angle_between(a, b), M_PI / 2.0, 1e-12);
}

TEST(Ch02_AngleBetween, Opposite) {
    Eigen::Vector3d a(1.0, 0.0, 0.0);
    Eigen::Vector3d b(-1.0, 0.0, 0.0);
    EXPECT_NEAR(ch02::angle_between(a, b), M_PI, 1e-12);
}

TEST(Ch02_AngleBetween, ZeroVectorThrows) {
    Eigen::Vector3d a(0.0, 0.0, 0.0);
    Eigen::Vector3d b(1.0, 0.0, 0.0);

    EXPECT_THROW(ch02::angle_between(a, b), std::invalid_argument);
}

// --- Проекция и ортогональное разложение ---

TEST(Ch02_ProjectOnto, Basic) {
    Eigen::Vector2d v(2.0, 3.0);
    Eigen::Vector2d onto(1.0, 0.0);

    Eigen::Vector2d p = ch02::project_onto(v, onto);

    EXPECT_DOUBLE_EQ(p(0), 2.0);
    EXPECT_DOUBLE_EQ(p(1), 0.0);
}

TEST(Ch02_ProjectOnto, ZeroOntoThrows) {
    Eigen::Vector2d v(2.0, 3.0);
    Eigen::Vector2d onto(0.0, 0.0);

    EXPECT_THROW(ch02::project_onto(v, onto), std::invalid_argument);
}

TEST(Ch02_OrthogonalComponent, OrthogonalToOnto) {
    Eigen::Vector2d v(2.0, 3.0);
    Eigen::Vector2d onto(1.0, 0.0);

    Eigen::Vector2d orth = ch02::orthogonal_component(v, onto);

    // ортогональная составляющая должна быть перпендикулярна onto
    EXPECT_DOUBLE_EQ(orth.dot(onto), 0.0);
    EXPECT_DOUBLE_EQ(orth(0), 0.0);
    EXPECT_DOUBLE_EQ(orth(1), 3.0);
}

// --- Произведение Адамара ---

TEST(Ch02_Hadamard, Basic) {
    Eigen::Vector3d a(1.0, 2.0, 3.0);
    Eigen::Vector3d b(4.0, 5.0, 6.0);
    Eigen::Vector3d r = ch02::hadamard_product(a, b);

    EXPECT_DOUBLE_EQ(r(0), 4.0);
    EXPECT_DOUBLE_EQ(r(1), 10.0);
    EXPECT_DOUBLE_EQ(r(2), 18.0);
}

TEST(Ch02_Hadamard, SizeMismatchThrows) {
    Eigen::VectorXd a(3);
    a << 1.0, 2.0, 3.0;
    Eigen::VectorXd b(2);
    b << 1.0, 2.0;

    EXPECT_THROW(ch02::hadamard_product(a, b), std::invalid_argument);
}

// --- Внешнее произведение ---

TEST(Ch02_Outer, Shape) {
    Eigen::Vector3d a(1.0, 2.0, 3.0);
    Eigen::Vector2d b(4.0, 5.0);

    Eigen::MatrixXd r = ch02::outer_product(a, b);

    EXPECT_EQ(r.rows(), 3);
    EXPECT_EQ(r.cols(), 2);
}

TEST(Ch02_Outer, Basic) {
    Eigen::Vector2d a(1.0, 2.0);
    Eigen::Vector2d b(3.0, 4.0);

    Eigen::MatrixXd r = ch02::outer_product(a, b);

    EXPECT_DOUBLE_EQ(r(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(r(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(r(1, 0), 6.0);
    EXPECT_DOUBLE_EQ(r(1, 1), 8.0);
}

// --- Векторное произведение ---

TEST(Ch02_Cross, StandardBasis) {
    Eigen::Vector3d x(1.0, 0.0, 0.0);
    Eigen::Vector3d y(0.0, 1.0, 0.0);

    Eigen::Vector3d r = ch02::cross_product(x, y);

    EXPECT_DOUBLE_EQ(r(0), 0.0);
    EXPECT_DOUBLE_EQ(r(1), 0.0);
    EXPECT_DOUBLE_EQ(r(2), 1.0);
}

TEST(Ch02_Cross, OrthogonalToInputs) {
    Eigen::Vector3d a(1.0, 2.0, 3.0);
    Eigen::Vector3d b(4.0, 5.0, 6.0);

    Eigen::Vector3d r = ch02::cross_product(a, b);

    EXPECT_NEAR(r.dot(a), 0.0, 1e-12);
    EXPECT_NEAR(r.dot(b), 0.0, 1e-12);
}

TEST(Ch02_Cross, AntiCommutative) {
    Eigen::Vector3d a(1.0, 2.0, 3.0);
    Eigen::Vector3d b(4.0, 5.0, 6.0);

    Eigen::Vector3d ab = ch02::cross_product(a, b);
    Eigen::Vector3d ba = ch02::cross_product(b, a);

    EXPECT_DOUBLE_EQ(ab(0), -ba(0));
    EXPECT_DOUBLE_EQ(ab(1), -ba(1));
    EXPECT_DOUBLE_EQ(ab(2), -ba(2));
}

// --- Смешанное (тройное) произведение ---

TEST(Ch02_TripleProduct, StandardBasis) {
    Eigen::Vector3d x(1.0, 0.0, 0.0);
    Eigen::Vector3d y(0.0, 1.0, 0.0);
    Eigen::Vector3d z(0.0, 0.0, 1.0);

    // объём единичного куба = 1.
    EXPECT_DOUBLE_EQ(ch02::triple_product(x, y, z), 1.0);
}

TEST(Ch02_TripleProduct, CyclicPermutation) {
    Eigen::Vector3d a(1.0, 2.0, 3.0);
    Eigen::Vector3d b(4.0, 5.0, 6.0);
    Eigen::Vector3d c(1.0, 0.0, -1.0);

    double abc = ch02::triple_product(a, b, c);
    double bca = ch02::triple_product(b, c, a);
    double cab = ch02::triple_product(c, a, b);

    EXPECT_DOUBLE_EQ(abc, bca);
    EXPECT_DOUBLE_EQ(abc, cab);
}

TEST(Ch02_TripleProduct, CoplanarVectorsGiveZero) {
    Eigen::Vector3d a(1.0, 0.0, 0.0);
    Eigen::Vector3d b(0.0, 1.0, 0.0);
    Eigen::Vector3d c(1.0, 1.0, 0.0);  // лежит в плоскости xy

    EXPECT_DOUBLE_EQ(ch02::triple_product(a, b, c), 0.0);
}

TEST(Ch02_TripleProduct, CollinearVectorsGiveZero) {
    Eigen::Vector3d a(1.0, 2.0, 3.0);
    Eigen::Vector3d b(4.0, 5.0, 6.0);
    Eigen::Vector3d d = 2.0 * a;  // коллинеарен a

    EXPECT_DOUBLE_EQ(ch02::triple_product(a, b, d), 0.0);
}

// --- Упражнение 2.2: ручная норма ---

TEST(Ch02_VectorNormManual, StandardBasis) {
    Eigen::Vector3d v(3.0, 4.0, 0.0);
    EXPECT_DOUBLE_EQ(ch02::vector_norm_manual(v), 5.0);
}

TEST(Ch02_VectorNormManual, MatchesEigen) {
    Eigen::VectorXd v(5);
    v << 1.0, -2.0, 3.0, -4.0, 5.0;

    EXPECT_NEAR(ch02::vector_norm_manual(v), ch02::vector_norm(v), 1e-12);
}

TEST(Ch02_VectorNormManual, ZeroVector) {
    Eigen::Vector3d v = Eigen::Vector3d::Zero();
    EXPECT_DOUBLE_EQ(ch02::vector_norm_manual(v), 0.0);
}

TEST(Ch02_VectorNormManual, UnitVector) {
    Eigen::Vector3d v(1.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(ch02::vector_norm_manual(v), 1.0);
}

TEST(Ch02_UnitVector, ZeroVectorHasNoNaN) {
    Eigen::Vector3d v = Eigen::Vector3d::Zero();
    Eigen::Vector3d u = ch02::unit_vector(v);

    EXPECT_FALSE(u.hasNaN());
    EXPECT_DOUBLE_EQ(u.norm(), 0.0);
}

// --- Упражнение 2.4: вектор заданного модуля ---

TEST(Ch02_SetMagnitude, RequestedMagnitude) {
    Eigen::Vector3d v(3.0, 4.0, 0.0);
    Eigen::Vector3d r = ch02::set_magnitude(v, 2.5);

    EXPECT_DOUBLE_EQ(ch02::vector_norm(r), 2.5);
}

TEST(Ch02_SetMagnitude, SameDirection) {
    Eigen::Vector3d v(3.0, 4.0, 0.0);
    Eigen::Vector3d r = ch02::set_magnitude(v, 7.0);

    EXPECT_TRUE(ch02::unit_vector(r).isApprox(ch02::unit_vector(v)));
}

TEST(Ch02_SetMagnitude, ZeroVectorReturnsZero) {
    Eigen::Vector3d v = Eigen::Vector3d::Zero();
    Eigen::Vector3d r = ch02::set_magnitude(v, 5.0);

    EXPECT_DOUBLE_EQ(r.norm(), 0.0);
    EXPECT_FALSE(r.hasNaN());
}

TEST(Ch02_SetMagnitude, NegativeMagnitude) {
    // отрицательный модуль переворачивает направление:
    // set_magnitude(v, -m) = (-m/|v|) * v = -set_magnitude(v, m)
    Eigen::Vector3d v(3.0, 4.0, 0.0);
    Eigen::Vector3d r = ch02::set_magnitude(v, -2.0);

    EXPECT_DOUBLE_EQ(ch02::vector_norm(r), 2.0);
    EXPECT_TRUE(r.isApprox(-ch02::set_magnitude(v, 2.0)));
}

// --- Упражнение 2.5: ручное транспонирование ---

TEST(Ch02_TransposeManual, Shape) {
    Eigen::VectorXd v(4);
    v << 1.0, 2.0, 3.0, 4.0;

    Eigen::MatrixXd r = ch02::transpose_manual(v);

    EXPECT_EQ(r.rows(), 1);
    EXPECT_EQ(r.cols(), 4);
}

TEST(Ch02_TransposeManual, MatchesBuiltin) {
    Eigen::VectorXd v(5);
    v << 1.0, -2.0, 3.0, -4.0, 5.0;

    Eigen::MatrixXd manual = ch02::transpose_manual(v);
    Eigen::MatrixXd builtin = v.transpose();

    EXPECT_TRUE(manual.isApprox(builtin));
}

TEST(Ch02_TransposeManual, ElementsMatch) {
    Eigen::VectorXd v(3);
    v << 7.0, 8.0, 9.0;

    Eigen::MatrixXd r = ch02::transpose_manual(v);

    EXPECT_DOUBLE_EQ(r(0, 0), 7.0);
    EXPECT_DOUBLE_EQ(r(0, 1), 8.0);
    EXPECT_DOUBLE_EQ(r(0, 2), 9.0);
}

TEST(Ch02_TransposeManual, EmptyVector) {
    Eigen::VectorXd v(0);
    Eigen::MatrixXd r = ch02::transpose_manual(v);

    EXPECT_EQ(r.rows(), 1);
    EXPECT_EQ(r.cols(), 0);
}

// --- Упражнение 2.6: ||v||² == v·v ---

TEST(Ch02_NormSquared, MatchesDotSelf) {
    Eigen::Vector3d v(3.0, 4.0, 0.0);

    double norm_sq = ch02::vector_norm(v) * ch02::vector_norm(v);
    double dot_self = ch02::dot_product(v, v);

    EXPECT_DOUBLE_EQ(norm_sq, dot_self);
}

TEST(Ch02_NormSquared, RandomVectors) {
    Eigen::VectorXd v(10);
    v << 1.5, -2.5, 3.0, -4.0, 5.5, -6.0, 7.0, -8.5, 9.0, -10.0;

    double norm_sq = ch02::vector_norm(v) * ch02::vector_norm(v);
    double dot_self = ch02::dot_product(v, v);

    EXPECT_NEAR(norm_sq, dot_self, 1e-10);
}

TEST(Ch02_NormSquared, ZeroVector) {
    Eigen::Vector3d v = Eigen::Vector3d::Zero();

    EXPECT_DOUBLE_EQ(ch02::vector_norm(v) * ch02::vector_norm(v), 0.0);
    EXPECT_DOUBLE_EQ(ch02::dot_product(v, v), 0.0);
}

// --- Упражнение 2.7: коммутативность dot product ---

TEST(Ch02_DotProductCommutative, Basic) {
    Eigen::Vector3d a(1.0, 2.0, 3.0);
    Eigen::Vector3d b(4.0, 5.0, 6.0);

    EXPECT_DOUBLE_EQ(ch02::dot_product(a, b), ch02::dot_product(b, a));
}

TEST(Ch02_DotProductCommutative, RandomVectors) {
    Eigen::VectorXd x(6);
    x << 1.5, -2.5, 3.0, -4.0, 5.5, -6.0;
    Eigen::VectorXd y(6);
    y << -1.0, 2.0, -3.0, 4.0, -5.0, 6.0;

    EXPECT_NEAR(ch02::dot_product(x, y), ch02::dot_product(y, x), 1e-12);
}

TEST(Ch02_DotProductCommutative, OrthogonalVectors) {
    Eigen::Vector3d a(1.0, 0.0, 0.0);
    Eigen::Vector3d b(0.0, 1.0, 0.0);

    EXPECT_DOUBLE_EQ(ch02::dot_product(a, b), 0.0);
    EXPECT_DOUBLE_EQ(ch02::dot_product(b, a), 0.0);
}

TEST(Ch02_DotProductCommutative, SelfDot) {
    Eigen::Vector3d a(3.0, 4.0, 0.0);

    EXPECT_DOUBLE_EQ(ch02::dot_product(a, a), ch02::dot_product(a, a));
}

// --- Упражнение 2.9: ортогональное разложение ---

TEST(Ch02_OrthogonalDecomposition, SumEqualsOriginal) {
    Eigen::Vector3d t(2.0, -1.0, 3.0);
    Eigen::Vector3d r(1.0, 2.0, 0.0);

    Eigen::Vector3d par = ch02::project_onto(t, r);
    Eigen::Vector3d perp = ch02::orthogonal_component(t, r);

    EXPECT_TRUE((par + perp).isApprox(t));
}

TEST(Ch02_OrthogonalDecomposition, ComponentsOrthogonal) {
    Eigen::Vector3d t(2.0, -1.0, 3.0);
    Eigen::Vector3d r(1.0, 2.0, 0.0);

    Eigen::Vector3d par = ch02::project_onto(t, r);
    Eigen::Vector3d perp = ch02::orthogonal_component(t, r);

    EXPECT_NEAR(par.dot(perp), 0.0, 1e-12);
}

TEST(Ch02_OrthogonalDecomposition, PerpOrthogonalToOnto) {
    Eigen::Vector3d t(2.0, -1.0, 3.0);
    Eigen::Vector3d r(1.0, 2.0, 0.0);

    Eigen::Vector3d perp = ch02::orthogonal_component(t, r);

    EXPECT_NEAR(perp.dot(r), 0.0, 1e-12);
}

// --- Упражнение 2.10: ошибочная проекция ---

TEST(Ch02_ProjectOntoWrong, DiffersFromCorrect) {
    Eigen::Vector2d t(2.0, 3.0);
    Eigen::Vector2d r(1.0, 0.0);

    Eigen::Vector2d correct = ch02::project_onto(t, r);
    Eigen::Vector2d wrong = ch02::project_onto_wrong(t, r);

    EXPECT_FALSE(correct.isApprox(wrong));
}

TEST(Ch02_ProjectOntoWrong, NotOrthogonal) {
    Eigen::Vector2d t(2.0, 3.0);
    Eigen::Vector2d r(1.0, 0.0);

    Eigen::Vector2d wrong = ch02::project_onto_wrong(t, r);
    Eigen::Vector2d wrong_orth = t - wrong;

    // для правильной проекции dot(proj, orth) == 0
    // для ошибочной — не равно нулю
    EXPECT_GT(std::abs(ch02::dot_product(wrong, wrong_orth)), 1e-6);
}

TEST(Ch02_ProjectOntoWrong, OrthogonalNotPerpendicularToOnto) {
    Eigen::Vector2d t(2.0, 3.0);
    Eigen::Vector2d r(1.0, 0.0);

    Eigen::Vector2d wrong_orth = t - ch02::project_onto_wrong(t, r);

    // для правильной проекции orth ⟂ onto
    // для ошибочной — нет
    EXPECT_GT(std::abs(ch02::dot_product(wrong_orth, r)), 1e-6);
}

TEST(Ch02_ProjectOntoWrong, CorrectProjectionIsOrthogonal) {
    // контрольный тест: правильная проекция действительно ортогональна
    Eigen::Vector2d t(2.0, 3.0);
    Eigen::Vector2d r(1.0, 0.0);

    Eigen::Vector2d correct = ch02::project_onto(t, r);
    Eigen::Vector2d correct_orth = t - correct;

    EXPECT_NEAR(ch02::dot_product(correct, correct_orth), 0.0, 1e-12);
    EXPECT_NEAR(ch02::dot_product(correct_orth, r), 0.0, 1e-12);
}
