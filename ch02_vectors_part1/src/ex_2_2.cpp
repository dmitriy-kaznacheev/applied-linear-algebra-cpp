// Глава 2, пример 2: Операции над векторами.
// Раздел книги: "Operations on Vectors".
//
// Демонстрирует:
//   - сложение и вычитание векторов
//   - умножение вектора на скаляр
//   - транспонирование (вектор-столбец ↔ вектор-строка)
//   - поэлементные операции (Eigen::Array)

#include <Eigen/Dense>
#include <iostream>

int main() {
    Eigen::Vector3d a(1.0, 2.0, 3.0);
    Eigen::Vector3d b(4.0, 5.0, 6.0);

    std::cout << "a          = " << a.transpose() << "\n";
    std::cout << "b          = " << b.transpose() << "\n";

    std::cout << "\nсложение и вычитаение векторов:\n";
    std::cout << "a + b      = " << (a + b).transpose() << "\n";
    std::cout << "a - b      = " << (a - b).transpose() << "\n";

    std::cout << "\nумножение вектора на скаляр:\n";
    std::cout << "2 * a      = " << (2.0 * a).transpose() << "\n";
    std::cout << "a / 2      = " << (a / 2.0).transpose() << "\n";

    std::cout << "\nтранспонирование:\n";
    std::cout << "a:           " << a.rows() << "x" << a.cols() << "\n";
    std::cout << "a^T:         " << a.transpose().rows() << "x" << a.transpose().cols() << "\n";

    std::cout << "\nпоэлементные операции:\n";
    {
        // для поэлементных операций нужен переход на Array
        Eigen::Array3d a_arr = a.array();
        Eigen::Array3d b_arr = b.array();

        std::cout << "a * b      = " << (a_arr * b_arr).transpose() << "\n";
        std::cout << "a^2        = " << (a_arr * a_arr).transpose() << "\n";
        std::cout << "a + 2      = " << (a_arr + 2.0).transpose() << "\n";
    }

    return 0;
}