# Прикладная линейная алгебра для исследователей данных — на C++

Учебный репозиторий: проработка книги **«Прикладная линейная алгебра для исследователей данных»** Майка Коэна (Mike X Cohen) с реализацией всех примеров и упражнений на **C++**.

## Цель

- глубокое понимание линейной алгебры на уровне типов, памяти и алгоритмов;
- практику промышленной C++-разработки с современными инструментами;
- сравнение поведения Eigen с NumPy (численная проверка корректности).

## Технологический стек

| Компонент | Выбор |
|---|---|
| Язык | C++17 |
| Линейная алгебра | [Eigen](https://gitlab.com/libeigen/eigen) (подмодуль) |
| Визуализация | [gnuplot-iostream](https://github.com/dstahlke/gnuplot-iostream) (подмодуль) + gnuplot с терминалом `qt` |
| Тесты | Google Test (через CMake FetchContent) |
| Сборка | CMake ≥ 3.16 + Ninja |
| CI | GitHub Actions (gcc/clang × Debug/Release) |

На Ubuntu/Debian:

```bash
# Для сборки и тестов
sudo apt-get install -y build-essential cmake ninja-build \
    libboost-iostreams-dev libboost-system-dev libboost-filesystem-dev

# Для интерактивных графиков (локально)
sudo apt-get install -y gnuplot

# Проверка, что qt-терминал доступен:
gnuplot -e "set terminal" | grep qt
```

## Структура репозитория

Каждая глава книги — отдельная директория с примерами и упражнениями.

| # | директория | Глава книги |
|---|---|---|
| 01 | `ch01_introduction` | Введение |
| 02 | [`ch02_vectors_part1`](ch02_vectors_part1/README.md) | Векторы, часть 1 |
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

Для запуска примеров с графиками нужен gnuplot с терминалом `qt`:

```bash
gnuplot -e "set terminal" | grep qt
```

## CI/CD

GitHub Actions workflow (`.github/workflows/ci.yml`) выполняет:

1. Проверку форматирования через `clang-format-14`.
2. Сборку и тесты в матрице **gcc/clang × Debug/Release**.
3. Подмодули подтягиваются автоматически (`submodules: recursive`).

## Прогресс

- [x] Глава 01 — Введение *(каркас + проверка Eigen)*
- [x] [Глава 02](ch02_vectors_part1/README.md) — Векторы, часть 1
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

4. **Визуализация.** Примеры и упражнения с графиками используют `gnuplot-iostream` и открывают интерактивное окно `qt` во время выполнения. Окно остается открытым до закрытия вручную.

   **Требования:** gnuplot с терминалом `qt` (или `wxt`, `x11`). Проверить:

   ```bash
   gnuplot -e "set terminal" | grep -E "qt|wxt|x11"
   ```

   Если ни один терминал не найден — установите gnuplot с GUI:

   ```bash
   # Ubuntu/Debian
   sudo apt-get install gnuplot
   ```

   **В CI** примеры с графиками не запускаются — только собираются, потому что в GitHub Actions нет дисплея.

   **Типичный сценарий работы:**

   ```cpp
   #include "plot_helpers.hpp"

   int main() {
       Eigen::Vector2d v(3.0, 2.0);

       Gnuplot gp = plot::make_interactive();
       plot::setup_interactive(gp, "Вектор (3, 2)");
       gp << "set xrange [-1:5]\nset yrange [-1:5]\n";
       plot::draw_vector(gp, v, "v = (3, 2)");

       return 0;
   }
   ```

## Вклад и обратная связь

Репозиторий учебный, Issues и Pull Request'ы приветствуются:

- нашел ошибку в реализации примера — открой Issue с указанием главы и номера;
- видишь более идиоматичное решение на Eigen — Pull Request с пояснением;
- заметил расхождение с результатами из книги — приложи скриншот или вывод Python-версии.

## Лицензия

Код в этом репозитории распространяется под [**MIT License**](LICENSE). Сама книга, ее текст, оригинальные примеры и иллюстрации принадлежат автору (Mike X Cohen) и издателю (O'Reilly Media). Этот репозиторий — независимая учебная работа и не аффилирован с автором или издателем.