#include <gtest/gtest.h>

#include "ch01.hpp"

TEST(Ch01_VectorNorm, StandardBasis) {
    Eigen::Vector3d v(3.0, 4.0, 0.0);
    EXPECT_DOUBLE_EQ(ch01::vector_norm(v), 5.0);
}

TEST(Ch01_VectorNorm, UnitAxis) {
    Eigen::Vector3d v(1.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(ch01::vector_norm(v), 1.0);
}

TEST(Ch01_VectorNorm, ZeroVector) {
    Eigen::Vector3d v(0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(ch01::vector_norm(v), 0.0);
}

TEST(Ch01_UnitVector, HasUnitNorm) {
    Eigen::Vector3d v(3.0, 4.0, 0.0);
    EXPECT_DOUBLE_EQ(ch01::unit_vector(v).norm(), 1.0);
}

TEST(Ch01_UnitVector, SameDirection) {
    Eigen::Vector3d v(3.0, 4.0, 0.0);
    Eigen::Vector3d u = ch01::unit_vector(v);

    EXPECT_DOUBLE_EQ(u(0), 0.6);
    EXPECT_DOUBLE_EQ(u(1), 0.8);
    EXPECT_DOUBLE_EQ(u(2), 0.0);
}