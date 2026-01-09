//
// Created by anton on 2026-01-11.
//

#include "boyer_moore.h"

#include <map>

boyer_moore::boyer_moore(const std::wstring &pattern) :
    pattern(pattern) {
    if (!pattern.empty()) {
        preprocessBadChar();
        preprocessGoodSuffix();
    }
}

void boyer_moore::preprocessBadChar() {
    // Используем map для хранения последних вхождений символов
    std::map<wchar_t, int> last_occurrence;

    // Заполняем таблицу сдвигов для плохого символа
    for (int i = 0; i < (int)pattern.length() - 1; ++i) {
        last_occurrence[pattern[i]] = i;
    }

    // Инициализируем таблицу сдвигов
    bad_char_shift.resize(pattern.length());

    for (int i = 0; i < (int)pattern.length(); ++i) {
        wchar_t c = pattern[i];
        if (last_occurrence.find(c) != last_occurrence.end()) {
            bad_char_shift[i] = i - last_occurrence[c];
        } else {
            bad_char_shift[i] = -1;
        }
    }
}

void boyer_moore::preprocessGoodSuffix() {
    int m = pattern.length();
    preprocessSuffix();

    good_suffix_shift.resize(m + 1);

    // Первый случай: суффикс встречается где-то еще в паттерне
    for (int i = 0; i < m; ++i) {
        good_suffix_shift[i] = m;
    }

    // Второй случай: префикс является суффиксом суффикса
    for (int i = m - 1; i >= 0; --i) {
        if (suffixes[i] == i + 1) {
            for (int j = 0; j < m - 1 - i; ++j) {
                if (good_suffix_shift[j] == m) {
                    good_suffix_shift[j] = m - 1 - i;
                }
            }
        }
    }

    // Третий случай: суффикс встречается в начале
    for (int i = 0; i <= m - 2; ++i) {
        good_suffix_shift[m - 1 - suffixes[i]] = m - 1 - i;
    }
}

void boyer_moore::preprocessSuffix() {
    int m = pattern.length();
    suffixes.resize(m);

    suffixes[m - 1] = m;
    int g = m - 1;
    int f = 0;

    for (int i = m - 2; i >= 0; --i) {
        if (i > g && suffixes[i + m - 1 - f] < i - g) {
            suffixes[i] = suffixes[i + m - 1 - f];
        } else {
            if (i < g) g = i;
            f = i;
            while (g >= 0 && pattern[g] == pattern[g + m - 1 - f]) {
                --g;
            }
            suffixes[i] = f - g;
        }
    }
}

int boyer_moore::findFirst(const std::wstring &text) const {
    if (pattern.empty()) return 0;
    if (text.empty() || pattern.length() > text.length()) return -1;

    int n = text.length();
    int m = pattern.length();

    int i = m - 1;
    int j = m - 1;

    while (i < n) {
        if (pattern[j] == text[i]) {
            if (j == 0) {
                return i; // Найдено вхождение
            }
            --i;
            --j;
        } else {
            // Эвристика плохого символа
            int bad_char_shift_value = 1;
            if (j > 0) {
                wchar_t bad_char = text[i];
                // Ищем последнее вхождение плохого символа в паттерне
                int last_occurrence = -1;
                for (int k = j - 1; k >= 0; --k) {
                    if (pattern[k] == bad_char) {
                        last_occurrence = k;
                        break;
                    }
                }
                bad_char_shift_value = std::max(1, j - last_occurrence);
            }

            // Эвристика хорошего суффикса
            int good_suffix_shift_value = good_suffix_shift[j];

            // Выбираем максимальный сдвиг
            i += std::max(bad_char_shift_value, good_suffix_shift_value);
            j = m - 1;
        }
    }

    return -1; // Не найдено
}

std::vector<int> boyer_moore::findAll(const std::wstring &text) const {
    std::vector<int> positions;
    if (pattern.empty() || text.empty() || pattern.length() > text.length()) {
        return positions;
    }

    int pos = 0;
    int found_pos;

    while (pos <= (int) text.length() - (int)pattern.length()) {
        found_pos = findFirst(text.substr(pos));
        if (found_pos != -1) {
            positions.push_back(pos + found_pos);
            pos += found_pos + 1; // Сдвигаем на 1 для поиска следующего вхождения
        } else {
            break;
        }
    }

    return positions;
}

bool boyer_moore::contains(const std::wstring &text) const {
    return findFirst(text) != -1;
}




