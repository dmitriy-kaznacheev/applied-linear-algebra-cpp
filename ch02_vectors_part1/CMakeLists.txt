# Глава 2: Векторы, часть 1.
# Библиотека главы — сюда попадают функции, используемые в примерах и тестах.

add_library(ch02 STATIC src/ch02.cpp)
target_link_libraries(ch02 PUBLIC Eigen3::Eigen)
target_include_directories(ch02 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# --- Примеры ---

add_executable(ex_2_1 src/ex_2_1.cpp)
target_link_libraries(ex_2_1 PRIVATE ch02 common)

add_executable(ex_2_2 src/ex_2_2.cpp)
target_link_libraries(ex_2_2 PRIVATE ch02)

add_executable(ex_2_3 src/ex_2_3.cpp)
target_link_libraries(ex_2_3 PRIVATE ch02 common)

add_executable(ex_2_4 src/ex_2_4.cpp)
target_link_libraries(ex_2_4 PRIVATE ch02 common)

add_executable(ex_2_5 src/ex_2_5.cpp)
target_link_libraries(ex_2_5 PRIVATE ch02 common)

add_executable(ex_2_6 src/ex_2_6.cpp)
target_link_libraries(ex_2_6 PRIVATE ch02 common)

add_executable(ex_2_7 src/ex_2_7.cpp)
target_link_libraries(ex_2_7 PRIVATE ch02 common)

# --- Упражнения ---

add_executable(prob_2_1 src/prob_2_1.cpp)
target_link_libraries(prob_2_1 PRIVATE ch02 common)

add_executable(prob_2_2 src/prob_2_2.cpp)
target_link_libraries(prob_2_2 PRIVATE ch02)

add_executable(prob_2_3 src/prob_2_3.cpp)
target_link_libraries(prob_2_3 PRIVATE ch02 common)

add_executable(prob_2_4 src/prob_2_4.cpp)
target_link_libraries(prob_2_4 PRIVATE ch02 common)

add_executable(prob_2_5 src/prob_2_5.cpp)
target_link_libraries(prob_2_5 PRIVATE ch02)

add_executable(prob_2_6 src/prob_2_6.cpp)
target_link_libraries(prob_2_6 PRIVATE ch02)

add_executable(prob_2_7 src/prob_2_7.cpp)
target_link_libraries(prob_2_7 PRIVATE ch02 common)

add_executable(prob_2_8 src/prob_2_8.cpp)
target_link_libraries(prob_2_8 PRIVATE ch02 common)

add_executable(prob_2_9 src/prob_2_9.cpp)
target_link_libraries(prob_2_9 PRIVATE ch02 common)

add_executable(prob_2_10 src/prob_2_10.cpp)
target_link_libraries(prob_2_10 PRIVATE ch02 common)