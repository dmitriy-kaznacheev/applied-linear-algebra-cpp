include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# --- Инфраструктурный тест: Eigen подключён ---
add_executable(test_eigen_setup test_eigen_setup.cpp)
target_link_libraries(test_eigen_setup PRIVATE Eigen3::Eigen GTest::gtest_main)
gtest_discover_tests(test_eigen_setup)

# --- Тесты главы 1 ---
add_executable(test_ch01 test_ch01.cpp)
target_link_libraries(test_ch01 PRIVATE ch01 GTest::gtest_main)
gtest_discover_tests(test_ch01)