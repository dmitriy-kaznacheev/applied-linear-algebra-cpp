// Упражнение 2.10: Поиск ошибки в проекции.
// Раздел книги: "Orthogonal Vector Decomposition".
//
// Задача: в коде проекции специально внедрить ошибку — в знаменателе
// проекционного скаляра поставить t·t вместо r·r. Проверить, что
// результат уходит в сторону от правильного. Подумать: как проверить,
// правильный результат или нет?

#include <cmath>
#include <iostream>

#include "ch02.hpp"
#include "vector_info.hpp"

int main() {
    Eigen::Vector2d t(2.0, 3.0);
    Eigen::Vector2d r(1.0, 0.0);

    info::vector_compact(t, "t");
    info::vector_compact(r, "r");
    std::cout << "\n";

    // --- Правильная проекция ---

    Eigen::Vector2d correct = ch02::project_onto(t, r);
    Eigen::Vector2d correct_orth = ch02::orthogonal_component(t, r);

    std::cout << "Правильная проекция:\n";
    info::vector_compact(correct, "project_onto");
    info::vector_compact(correct_orth, "orthogonal");
    std::cout << "  проекция · ортогональная = " << ch02::dot_product(correct, correct_orth)
              << " (должно быть 0)\n\n";

    // --- Ошибочная проекция ---

    Eigen::Vector2d wrong = ch02::project_onto_wrong(t, r);
    Eigen::Vector2d wrong_orth = t - wrong;

    std::cout << "Ошибочная проекция (знаменатель t·t вместо r·r):\n";
    info::vector_compact(wrong, "project_onto_wrong");
    info::vector_compact(wrong_orth, "orthogonal");
    std::cout << "  проекция · ортогональная = " << ch02::dot_product(wrong, wrong_orth)
              << " (должно быть 0, если правильно)\n\n";

    // --- Как обнаружить ошибку ---

    std::cout << "Как обнаружить ошибку:\n\n";

    // проверка 1: сумма компонент (всегда сходится, ошибку не ловит)
    std::cout << "1) Сумма компонент:\n";
    std::cout << "   правильная == t? " << ((correct + correct_orth).isApprox(t) ? "да" : "НЕТ")
              << "\n";
    std::cout << "   ошибочная  == t? " << ((wrong + wrong_orth).isApprox(t) ? "да" : "НЕТ")
              << "\n";
    std::cout << "   (эта проверка НЕ ловит ошибку: t - wrong + wrong = t всегда)\n\n";

    // проверка 2: ортогональность проекции и ортогональной части
    std::cout << "2) Ортогональность проекции и ортогональной части:\n";
    std::cout << "   правильная: " << ch02::dot_product(correct, correct_orth)
              << " (≈0 — хорошо)\n";
    std::cout << "   ошибочная:  " << ch02::dot_product(wrong, wrong_orth)
              << " (≠0 — ошибка обнаружена!)\n\n";

    // проверка 3: ортогональная часть должна быть перпендикулярна r
    std::cout << "3) Ортогональная часть ⟂ r:\n";
    std::cout << "   правильная: " << ch02::dot_product(correct_orth, r) << " (≈0 — хорошо)\n";
    std::cout << "   ошибочная:  " << ch02::dot_product(wrong_orth, r)
              << " (≠0 — ошибка обнаружена!)\n\n";

    // проверка 4: проекция должна лежать на прямой r
    std::cout << "4) Проекция должна лежать на прямой r = (1, 0) и иметь длину 2:\n";
    std::cout << "   правильная: x = " << correct(0) << " (должно быть 2 — хорошо)\n";
    std::cout << "   ошибочная:  x = " << wrong(0) << " (≠ 2 — ошибка обнаружена!)\n\n";

    std::cout << "Вывод: ошибку в знаменателе можно обнаружить через проверку ортогональности.\n";

    return 0;
}