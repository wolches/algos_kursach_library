//
// Created by anton on 2025-12-14.
//
#include "utils.h"

#include <codecvt>
#include <regex>

const wchar_t* ws = L" \t\n\r\f\v";

std::wstring trim(std::wstring s) {
    s.erase(0, s.find_first_not_of(ws));
    s.erase(s.find_last_not_of(ws) + 1);
    return s;
}

unsigned long long polynominal(std::wstring s, unsigned long long p, unsigned long long mod, size_t from, size_t to) {
    if (from == to || s.size() == 0) return 0;
    unsigned long long h = s[from];
    for (int i = from + 1; i < to; i++) {
        h = ((h * p) + (s[i] + 1)) % mod;
    }
    return h;
}

unsigned long long polynominal(std::wstring s, unsigned long long p, unsigned long long mod) {
    return polynominal(s, p, mod, 0, s.size());
}

std::vector<std::wstring> split(std::wstring s, const std::wstring &delimiter) {
    std::vector<std::wstring> tokens;
    std::size_t start = 0, end = 0;
    while ((end = s.find(delimiter, start)) != std::wstring::npos) {
        std::wstring token = s.substr(start, end - start);
        if (!token.empty()) {
            tokens.push_back(token);
        }
        start = end + delimiter.length();
    }
    std::wstring token = s.substr(start);
    tokens.push_back(token);
    return tokens;
}


// ISO date (yyyy-MM-dd)
const std::wstring iso_date_regex = L"^d{4}-d{2}-d{2}$";

tm *parseTime(const std::wstring &strValue) {
    if (std::regex_match(strValue, std::wregex(iso_date_regex))) {
        auto ymd = split(strValue, L"-");
        tm *res = new tm;
        res->tm_year = std::stoi(ymd[0]) - 1970;
        res->tm_mon = std::stoi(ymd[1]) - 1;
        res->tm_mday = std::stoi(ymd[2]);
        res->tm_hour = 0;
        res->tm_min = 0;
        res->tm_sec = 0;
        return res;
    }
    throw std::invalid_argument("Invalid date format");
}

tm *now() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    tm *date = std::localtime(&time);
    tm *result = new tm;
    result->tm_year = date->tm_year;
    result->tm_mon = date->tm_mon;
    result->tm_mday = date->tm_mday;
    result->tm_hour = 0;
    result->tm_min = 0;
    result->tm_sec = 0;
    return result;
}

std::wstring formatTime(const tm &t) {
    return std::format(L"{}-{}-{}", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);
}

bool isGreaterOrEqual(const tm &t1, const tm &t2) {
    return t1.tm_year > t2.tm_year
    || (t1.tm_year == t2.tm_year && (
        t1.tm_mon > t2.tm_mon
        || (t1.tm_mon == t2.tm_mon &&
            t1.tm_mday >= t2.tm_mday)));
}

std::wstring addLeadingZeros(const long long num, const long long length) {
    return std::format(L"{:0{}}", num, length);
}

std::string fromWideString(const std::wstring &s) {
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(s);
}

std::wstring toWideString(const std::string &s) {
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(s);
}
