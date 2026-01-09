//
// Created by anton on 2026-01-11.
//

#ifndef ALGOS_KURSACH_BOYER_MOORE_H
#define ALGOS_KURSACH_BOYER_MOORE_H
#include <string>
#include <vector>


class boyer_moore {
private:
    std::wstring pattern;
    std::vector<int> bad_char_shift;
    std::vector<int> good_suffix_shift;
    std::vector<int> suffixes;
    void preprocessBadChar();
    void preprocessGoodSuffix();
    void preprocessSuffix();
public:
    boyer_moore(const std::wstring &pattern);
    std::vector<int> findAll(const std::wstring &text) const;
    int findFirst(const std::wstring &text) const;
    bool contains(const std::wstring &text) const;
};


#endif //ALGOS_KURSACH_BOYER_MOORE_H