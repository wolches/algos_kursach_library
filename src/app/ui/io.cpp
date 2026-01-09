//
// Created by anton on 2026-01-10.
//

#include "io.h"

#include <codecvt>
#include <locale>
#include <windows.h>
#include "../../utils/utils.h"

std::wstring readString(const std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > &advice) {
    std::wstring target;
    std::wcout << advice << std::endl << L">> ";
    std::getline(std::wcin, target);
    std::wcin.seekg(0, std::ios::end);
    std::wcin.clear();
    return target; //convert(target);
}

// Т.к. совместное использование cin и wcin приводит к тому что байты в потоке
// считываются как нецифровые символы, проще все делать через stoi
int readInt(const std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > &advice) {
    auto read = readString(advice);
    return std::stoi(read);
}

void printString(const std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > &value) {
    std::wcout << value << std::endl;
}

void printInt(const int &value) {
    std::wcout << value << std::endl;
}