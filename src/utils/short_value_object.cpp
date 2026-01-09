//
// Created by anton on 2025-12-14.
//

#include "short_value_object.h"

#include <format>
#include "utils.h"

short_value_object::short_value_object() {
    value = 0;
}

short_value_object::short_value_object(std::wstring stringValue, short lowerBorder, short upperBorder, std::wstring name) {
    stringValue = trim(stringValue);
    int number = std::stoi(stringValue);
    if (number < lowerBorder || number > upperBorder) {
        throw std::invalid_argument(
            fromWideString(
                std::vformat(
                    L"{} must be between {} and {}",
                    std::make_wformat_args(name, lowerBorder, upperBorder)
                )));
    }
    this->value = number;
}

short_value_object::short_value_object(short value) {
    this->value = value;
}

short short_value_object::getValue() const {
    return this->value;
}
