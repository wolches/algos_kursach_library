//
// Created by anton on 2025-12-14.
//
#include "reader.h"

reader::reader() {
}

reader::reader(
    reader_id readerId, full_name fullName, short_value_object yearOfBirth,
    std::wstring address, std::wstring counterparty
) : yearOfBirth(0) {
    this->readerId = readerId;
    this->fullName = fullName;
    this->yearOfBirth = yearOfBirth;
    this->address = address;
    this->counterparty = counterparty;
}


std::wstring reader::getReaderId() const {
    return this->readerId.getValue();
}

std::wstring reader::getFullName() const {
    return this->fullName.getValue();
}

std::wstring reader::getAddress() const {
    return this->address;
}

short reader::getYearOfBirth() const {
    return this->yearOfBirth.getValue();
}

std::wstring reader::getCounterParty() const {
    return this->counterparty;
}

short reader::getId() const {
    return readerId.getId();
}

wchar_t reader::getAccess() const {
    return readerId.getAccess();
}

std::wstring reader::getFirstName() const {
    return this->fullName.getFirstName();
}

std::wstring reader::getLastName() const {
    return this->fullName.getLastName();
}

std::wstring reader::getMiddleName() const {
    return this->fullName.getMiddleName();
}

/**
 * По условиям задачи, id это порядковый номер регистрации читателя
 */
bool reader::operator==(const reader &other) const {
    return this->getId() == other.getId();
}



