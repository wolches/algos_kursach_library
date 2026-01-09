//
// Created by anton on 2025-12-14.
//

#include "reader_id.h"

#include <format>
#include "../utils/utils.h"
#include <regex>

reader_id::reader_id() {
    access = L'Н';
    id = -1;
    year = -1;
}

reader_id::reader_id(std::wstring value) {
    value = trim(value);
    if (std::regex_match(value, std::wregex(reader_id_regex))) {
        this->access = value[0];
        this->id = std::stoi(value.substr(1, 5));
        this->year = std::stoi(value.substr(6, 8));
    } else {
        throw std::invalid_argument("Reader id format is invalid");
    }
}

std::wstring reader_id::getValue() const {
    std::wstring a(1, this->access);
    auto id = addLeadingZeros(this->id, 4);
    auto yy = addLeadingZeros(this->year, 2);
    return std::vformat(reader_id_format, std::make_wformat_args(a, id, yy));
}

wchar_t reader_id::getAccess() const {
    return access;
}

short reader_id::getId() const {
    return id;
}

short reader_id::getYear() const {
    return year;
}

