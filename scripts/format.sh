#!/usr/bin/env bash
#
# Автоформатирование всех .cpp/.h/.hpp в репозитории.
# Запускать из корня: ./scripts/format.sh
#
set -euo pipefail

CLANG_FORMAT="${CLANG_FORMAT:-clang-format-14}"

if ! command -v "$CLANG_FORMAT" &>/dev/null; then
    echo "Ошибка: $CLANG_FORMAT не найден."
    echo "Установите: sudo apt-get install clang-format-14"
    echo "Или задайте другую версию: CLANG_FORMAT=clang-format-15 ./scripts/format.sh"
    exit 1
fi

echo "Форматирование через $CLANG_FORMAT..."

find . \
    -path ./external -prune -o \
    -path ./build -prune -o \
    -path ./.git -prune -o \
    -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -print0 \
    | xargs -0 "$CLANG_FORMAT" -i

echo "Готово."
