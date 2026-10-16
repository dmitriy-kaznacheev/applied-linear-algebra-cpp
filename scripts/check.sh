#!/usr/bin/env bash
#
# Локальная проверка, дублирующая CI.
# Запускать из корня репозитория: ./scripts/check.sh
#
set -euo pipefail

# --- Цвета для вывода ---
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# --- Проверка, что мы в корне репозитория ---
if [[ ! -f "CMakeLists.txt" && ! -f ".gitmodules" ]]; then
    echo -e "${RED}Ошибка: скрипт нужно запускать из корня репозитория.${NC}"
    exit 1
fi

# --- Версия clang-format ---
CLANG_FORMAT="${CLANG_FORMAT:-clang-format-14}"
if ! command -v "$CLANG_FORMAT" &>/dev/null; then
    echo -e "${YELLOW}Предупреждение: $CLANG_FORMAT не найден. Пропускаю проверку форматирования.${NC}"
    echo -e "${YELLOW}Установите: sudo apt-get install clang-format-14${NC}"
else
    echo -e "${GREEN}[1/4] Проверка форматирования ($CLANG_FORMAT)...${NC}"
    find . \
        -path ./external -prune -o \
        -path ./build -prune -o \
        \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -print \
        | xargs "$CLANG_FORMAT" --dry-run --Werror
    echo -e "${GREEN}      ОК${NC}"
fi

# --- Сборка ---
echo -e "${GREEN}[2/4] Конфигурация CMake...${NC}"
cmake -B build -G Ninja \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE:-Debug}" \
    -DBUILD_TESTING=ON

echo -e "${GREEN}[3/4] Сборка...${NC}"
cmake --build build

# --- Тесты ---
echo -e "${GREEN}[4/4] Запуск тестов...${NC}"
ctest --test-dir build --output-on-failure

echo -e "${GREEN}Все проверки пройдены успешно!${NC}"
