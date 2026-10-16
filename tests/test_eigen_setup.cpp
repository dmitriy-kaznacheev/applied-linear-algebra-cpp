#include <gtest/gtest.h>

#include <Eigen/Dense>

TEST(EigenSetup, VectorNorm) {
    Eigen::Vector2d v(3.0, 4.0);
    EXPECT_DOUBLE_EQ(v.norm(), 5.0);
}

TEST(EigenSetup, DotProduct) {
    Eigen::Vector2d a(1.0, 2.0);
    Eigen::Vector2d b(3.0, 4.0);
    EXPECT_DOUBLE_EQ(a.dot(b), 11.0);
}

TEST(EigenSetup, MatrixMultiplication) {
    Eigen::Matrix2d A;
    A << 1.0, 2.0, 3.0, 4.0;

    Eigen::Vector2d v(1.0, 1.0);
    Eigen::Vector2d result = A * v;

    EXPECT_DOUBLE_EQ(result(0), 3.0);
    EXPECT_DOUBLE_EQ(result(1), 7.0);
}