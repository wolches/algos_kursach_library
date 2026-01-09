//
// Created by anton on 2025-12-14.
//

#ifndef ALGOS_KURSACH_FULLNAME_H
#define ALGOS_KURSACH_FULLNAME_H
#include <string>

inline const std::wstring full_name_regex = L"[А-ЯЁ][а-яё]+ [А-ЯЁ][а-яё]+( [А-ЯЁ][а-яё]+)?";
inline const std::wstring full_name_format = L"{} {} {}";

class full_name {
private:
    std::wstring firstName;
    std::wstring lastName;
    std::wstring middleName;
    void validateLength();
public:
    full_name();
    full_name(const std::wstring &firstName, const std::wstring &lastName, const std::wstring &middleName);
    full_name(std::wstring fullName);
    std::wstring getValue() const;
    std::wstring getFirstName() const;
    std::wstring getLastName() const;
    std::wstring getMiddleName() const;
};


#endif //ALGOS_KURSACH_FULLNAME_H