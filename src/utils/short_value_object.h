//
// Created by anton on 2025-12-14.
//

#ifndef ALGOS_KURSACH_SHORT_VALUE_OBJECT_H
#define ALGOS_KURSACH_SHORT_VALUE_OBJECT_H
#include <string>


class short_value_object {
private:
    short value;
public:
    short_value_object();
    short_value_object(std::wstring stringValue, short lowerBorder, short upperBorder, std::wstring name);
    short_value_object(short value); // Direct constructor without validation
    short getValue() const;
};


#endif //ALGOS_KURSACH_SHORT_VALUE_OBJECT_H