add_library(ch01 STATIC src/ch01.cpp)
target_link_libraries(ch01 PUBLIC Eigen3::Eigen)
target_include_directories(ch01 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(ex_1_1 src/ex_1_1.cpp)
target_link_libraries(ex_1_1 PRIVATE ch01)