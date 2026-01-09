//
// Created by anton on 2025-12-14.
//

#ifndef ALGOS_KURSACH_UTILS_H
#define ALGOS_KURSACH_UTILS_H
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

std::wstring trim(std::wstring s);
unsigned long long polynominal(std::wstring s, unsigned long long p, unsigned long long mod, size_t from, size_t to);
unsigned long long polynominal(std::wstring s, unsigned long long p, unsigned long long mod);
std::vector<std::wstring> split(std::wstring s, const std::wstring &delimiter);
tm *parseTime(const std::wstring &s);
tm *now();
std::wstring formatTime(const tm &t);
bool isGreaterOrEqual(const tm &t1, const tm &t2);
std::wstring addLeadingZeros(long long num, long long length);
std::string fromWideString(const std::wstring &s);
std::wstring toWideString(const std::string &s);

#endif //ALGOS_KURSACH_UTILS_H