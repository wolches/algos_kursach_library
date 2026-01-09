//
// Created by anton on 2025-12-14.
//

#ifndef ALGOS_KURSACH_PASSPORT_H
#define ALGOS_KURSACH_PASSPORT_H
#include <string>

inline const std::wstring reader_id_regex = L"[АЧВ]\\d{4}-\\d{2}";
inline const std::wstring reader_id_format = L"{}{}-{}";

class reader_id {
private:
    wchar_t access;
    short id;
    short year;
public:
    reader_id();
    reader_id(std::wstring value);
    std::wstring getValue() const;
    wchar_t getAccess() const;
    short getId() const;
    short getYear() const;
};


#endif //ALGOS_KURSACH_PASSPORT_H