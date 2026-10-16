cmake_minimum_required(VERSION 3.16)
project(AppliedLinearAlgebraCpp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Boost
find_package(Boost REQUIRED COMPONENTS iostreams system filesystem)
include_directories(${Boost_INCLUDE_DIRS})

# Eigen
add_subdirectory(external/eigen)

# gnuplot-iostream (header-only)
include_directories(external/gnuplot-iostream)

# common
add_subdirectory(common)

# Главы
add_subdirectory(ch01_introduction)

# Тесты
option(BUILD_TESTING "Build tests" ON)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()