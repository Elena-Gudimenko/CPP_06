#include "ScalarConverter.hpp"
#include "DetectType.hpp"
#include "DisplayTypes.hpp"
#include <cstdlib>   // strtol, strtod
#include <cerrno>    // errno, ERANGE
#include <climits>   // INT_MIN, INT_MAX
#include <cfloat>    // FLT_MAX, DBL_MAX

// Canonical form: private, the class is not instantiable
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string& literal)
{
    double d = 0.0;        // carrier: any char, int or float fits into a double exactly
    bool   overflow = false;

    if (isChar(literal))
    {
        char c;
        if (literal.length() == 3)
            c = literal[1]; // 'a' -> middle symbol
        else
            c = literal[0]; // a -> the only symbol
        d = static_cast<double>(c);
    }
    else if (isInt(literal))
    {
        errno = 0;
        long l = std::strtol(literal.c_str(), NULL, 10);
        if (errno == ERANGE || l < INT_MIN || l > INT_MAX)
            overflow = true;
        else
            d = static_cast<double>(static_cast<int>(l));
    }
    else if (isFloat(literal))
    {
        // strtod stops at the trailing 'f': "4.2f" -> 4.2, "nanf" -> nan
        double tmp = std::strtod(literal.c_str(), NULL);
        // finite but too big for a float (inff and nanf are fine)
        if ((tmp > FLT_MAX && tmp <= DBL_MAX) || (tmp < -FLT_MAX && tmp >= -DBL_MAX))
            overflow = true;
        else
            d = static_cast<double>(static_cast<float>(tmp));
    }
    else if (isDouble(literal))
    {
        errno = 0;
        d = std::strtod(literal.c_str(), NULL);
        // ERANGE + inf result: a normal number did not fit ("inf" itself sets no error)
        if (errno == ERANGE && (d > DBL_MAX || d < -DBL_MAX))
            overflow = true;
    }
    else
    {
        printImpossible(); // not a valid literal
        return;
    }

    if (overflow)
        printImpossible();
    else
        printAll(d);
}