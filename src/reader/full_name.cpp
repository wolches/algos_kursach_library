//
// Created by anton on 2025-12-14.
//

#include "full_name.h"
#include "../utils/utils.h"
#include <format>
#include <regex>

#include "../app/ui/io.h"

full_name::full_name(std::wstring fullName) {
    fullName = trim(fullName);
    bool match = std::regex_search(fullName, std::wregex(full_name_regex));
    if (match) {
        auto nameParts = split(fullName, L" ");
        // F I O
        this->lastName = nameParts[0];
        this->firstName = nameParts[1];
        this->middleName = (nameParts.size() == 3 ? nameParts[2] : L"");
        validateLength();
    } else {
        printString(full_name_regex);
        printString(fullName);
        throw std::invalid_argument("Invalid name");
    }
}

full_name::full_name() {
    lastName = firstName = middleName = L"";
}

full_name::full_name(
    const std::wstring &firstName,
    const std::wstring &lastName,
    const std::wstring &middleName
) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->middleName = middleName;
    validateLength();
}

std::wstring full_name::getValue() const {
    // F I O
    std::wstring res = std::vformat(
        full_name_format,
        std::make_wformat_args(this->lastName, this->firstName, this->middleName)
    );
    return trim(res);
}

void full_name::validateLength() {
    if (firstName.size() > 20) throw std::invalid_argument("First name is too long");
    if (middleName.size() > 20) throw std::invalid_argument("Middle name is too long");
    if (lastName.size() > 20) throw std::invalid_argument("Last name is too long");
}

std::wstring full_name::getFirstName() const {
    return this->firstName;
}

std::wstring full_name::getLastName() const {
    return this->lastName;
}

std::wstring full_name::getMiddleName() const {
    return this->middleName;
}




