//
// Created by anton on 2025-12-14.
//
#ifndef ALGOS_KURSACH_GUEST_H
#define ALGOS_KURSACH_GUEST_H
#include <string>

#include "full_name.h"
#include "reader_id.h"
#include "../utils/short_value_object.h"

class reader {
private:
    reader_id readerId;
    full_name fullName;
    short_value_object yearOfBirth;
    std::wstring address;
    std::wstring counterparty;
public:
    reader();
    reader(
        reader_id readerId,
        full_name fullName,
        short_value_object yearOfBirth,
        std::wstring address,
        std::wstring counterparty
    );
    short getId() const;
    wchar_t getAccess() const;
    std::wstring getReaderId() const;
    std::wstring getFirstName() const;
    std::wstring getLastName() const;
    std::wstring getMiddleName() const;
    std::wstring getFullName() const;
    short getYearOfBirth() const;
    std::wstring getAddress() const;
    std::wstring getCounterParty() const;
    bool operator==(const reader &) const;
};


#endif //ALGOS_KURSACH_GUEST_H