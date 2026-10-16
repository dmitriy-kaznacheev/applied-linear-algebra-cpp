# Прикладная линейная алгебра для исследователей данных — на C++

Учебный репозиторий: проработка книги **«Прикладная линейная алгебра для исследователей данных»** Майка Коэна (Mike X Cohen) с реализацией всех примеров и упражнений на **C++**.

## Цель

Пройти книгу от начала до конца, реализуя каждый пример на C++ вместо Python/NumPy. Это даёт:

- глубокое понимание линейной алгебры на уровне типов, памяти и алгоритмов;
- практику промышленной C++-разработки с современными инструментами;
- сравнение поведения Eigen с NumPy (численная проверка корректности).

## Технологический стек

| Компонент | Выбор |
|---|---|
| Язык | C++17 |
| Линейная алгебра | [Eigen](https://gitlab.com/libeigen/eigen) (подмодуль) |
| Визуализация | [gnuplot-iostream](https://github.com/dstahlke/gnuplot-iostream) (подмодуль) + gnuplot |
| Тесты | Google Test (через CMake FetchContent) |
| Сборка | CMake ≥ 3.16 + Ninja |
| CI | GitHub Actions (gcc/clang × Debug/Release) |

На Ubuntu/Debian:

```bash
sudo apt-get install -y build-essential cmake ninja-build \
    libboost-iostreams-dev libboost-system-dev libboost-filesystem-dev \
    gnuplot-nox
```

## Структура репозитория

Каждая глава книги — отдельная директория с примерами и упражнениями.

| # | директория | Глава книги |
|---|---|---|
| 01 | `ch01_introduction` | Введение |
| 02 | `ch02_vectors_part1` | Векторы, часть 1 |
| 03 | `ch03_vectors_part2` | Векторы, часть 2 |
| 04 | `ch04_vector_applications` | Применение векторов |
| 05 | `ch05_matrices_part1` | Матрицы, часть 1 |
| 06 | `ch06_matrices_part2` | Матрицы, часть 2 |
| 07 | `ch07_matrix_applications` | Применение матриц |
| 08 | `ch08_matrix_inverse` | Обратная матрица |
| 09 | `ch09_orthogonal_matrices_qr` | Ортогональные матрицы и QR-разложение |
| 10 | `ch10_row_reduction_lu` | Приведение строк и LU-разложение |
| 11 | `ch11_general_linear_models_least_squares` | Общие линейные модели и метод наименьших квадратов |
| 12 | `ch12_least_squares_applications` | Применение метода наименьших квадратов |
| 13 | `ch13_eigendecomposition` | Спектральное разложение |
| 14 | `ch14_singular_value_decomposition` | Сингулярное разложение |
| 15 | `ch15_eig_svd_applications` | Применение спектрального и сингулярного разложений |
| 16 | `ch16_python_tutorial` | Руководство по Python (справочно) |

## Сборка и запуск

```bash
git clone --recursive git@github.com:ВАШ_ЛОГИН/applied-linear-algebra-cpp.git
cd applied-linear-algebra-cpp

cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

## CI/CD

GitHub Actions workflow (`.github/workflows/ci.yml`) выполняет:

1. Проверку форматирования через `clang-format-14`.
2. Сборку и тесты в матрице **gcc/clang × Debug/Release**.
3. Подмодули подтягиваются автоматически (`submodules: recursive`).

## Прогресс

- [x] Глава 01 — Введение *(каркас + проверка Eigen)*
- [ ] Глава 02 — Векторы, часть 1
- [ ] Глава 03 — Векторы, часть 2
- [ ] Глава 04 — Применение векторов
- [ ] Глава 05 — Матрицы, часть 1
- [ ] Глава 06 — Матрицы, часть 2
- [ ] Глава 07 — Применение матриц
- [ ] Глава 08 — Обратная матрица
- [ ] Глава 09 — Ортогональные матрицы и QR-разложение
- [ ] Глава 10 — Приведение строк и LU-разложение
- [ ] Глава 11 — Общие линейные модели и метод наименьших квадратов
- [ ] Глава 12 — Применение метода наименьших квадратов
- [ ] Глава 13 — Спектральное разложение
- [ ] Глава 14 — Сингулярное разложение
- [ ] Глава 15 — Применение спектрального и сингулярного разложений

## Источник

Mike X Cohen. *Practical Linear Algebra for Data Science: From Core Concepts to Applications Using Python*. O'Reilly Media, 2022.

Оригинальные примеры автора на Python доступны в репозитории книги: [github.com/mikexcohen/LinAlg4DataScience](https://github.com/mikexcohen/LinAlg4DataScience).

## Как пользоваться репозиторием

1. Каждая глава — отдельная директория `chNN_название` с независимыми примерами.
2. Один пример = один `.cpp` файл = один исполняемый файл (собирается отдельной целью CMake).
3. Запуск конкретного примера:

   ```bash
   ./build/ch02_vectors_part1/ex_2_1
   ```

4. **Визуализация.** Примеры, строящие графики, используют `gnuplot-iostream`. По умолчанию данные отправляются в gnuplot через пайп, и открывается окно с графиком.

   **Если gnuplot не установлен** — пример завершится с ошибкой. Установите:

   ```bash
   # Ubuntu/Debian — с GUI (X11)
   sudo apt-get install gnuplot

   # Ubuntu/Debian — без GUI, только терминал (для CI)
   sudo apt-get install gnuplot-nox

   # macOS
   brew install gnuplot
   ```

   **Три режима работы с графиками** (переключаются через `common/plot_helpers.hpp`):

   | Режим | Когда использовать | Что делает |
   |---|---|---|
   | `Pipe` (по умолчанию) | Локальная работа, интерактив | Открывает окно gnuplot, данные идут через stdin |
   | `File` | Отладка, CI, медленные вычисления | Сохраняет `.dat` и `.gnuplot`, запускает gnuplot из файла |
   | `Silent` | Автотесты | Только пишет данные в `.dat`, gnuplot не вызывается |

   **Типичный сценарий работы:**

   ```cpp
   #include "plot_helpers.hpp"
   #include <Eigen/Dense>

   int main() {
       Eigen::VectorXd x = Eigen::VectorXd::LinSpaced(100, 0, 2 * M_PI);
       Eigen::VectorXd y = x.array().sin();

       plot::line(x, y, "sin(x)", "x", "y");
       return 0;
   }
   ```

5. Для отладки визуализации можно переключиться на запись данных в файл (см. `common/plot_helpers.hpp`).

## Вклад и обратная связь

Репозиторий учебный и личный, но Issues и Pull Request'ы приветствуются:

- нашёл ошибку в реализации примера — открой Issue с указанием главы и номера;
- видишь более идиоматичное решение на Eigen — Pull Request с пояснением;
- заметил расхождение с результатами из книги — приложи скриншот или вывод Python-версии.

## Лицензия

Код в этом репозитории распространяется под **MIT License** (см. файл [LICENSE](LICENSE)). Сама книга, её текст, оригинальные примеры и иллюстрации принадлежат автору (Mike X Cohen) и издателю (O'Reilly Media). Этот репозиторий — независимая учебная работа и не аффилирован с автором или издателем.