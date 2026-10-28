#ifndef DETECTTYPE_HPP
#define DETECTTYPE_HPP

#include <string>

bool isChar(const std::string& s);
bool isInt(const std::string& s);
bool isFloat(const std::string& s);
bool isDouble(const std::string& s);

void printImpossible();
void printAll(double d);

#endif