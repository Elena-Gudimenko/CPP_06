#include "DisplayTypes.hpp"
#include <iostream>
#include <iomanip>   // std::setprecision
#include <climits>   // CHAR_MIN, CHAR_MAX, INT_MIN, INT_MAX
#include <cfloat>    // FLT_MAX, DBL_MAX
#include <cmath>     // std::floor

void printImpossible()
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
}

// d != d is true only for nan
static void printChar(double d)
{
    std::cout << "char: ";
    if (d != d || d < CHAR_MIN || d > CHAR_MAX)
        std::cout << "impossible" << std::endl;
    else if (d < 32 || d > 126) // printable ASCII range is 32..126
        std::cout << "Non displayable" << std::endl;
    else
        std::cout << "'" << static_cast<char>(d) << "'" << std::endl;
}

static void printInt(double d)
{
    std::cout << "int: ";
    if (d != d || d < INT_MIN || d > INT_MAX) // also catches inf
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int>(d) << std::endl;
}

// Prints nan / +inf / -inf, or the number with ".0" if it is whole
static void printNumber(double value, const char* suffix)
{
    if (value != value)
        std::cout << "nan";
    else if (value > DBL_MAX)
        std::cout << "+inf";
    else if (value < -DBL_MAX)
        std::cout << "-inf";
    else if (value == std::floor(value))
        std::cout << std::fixed << std::setprecision(1) << value;
    else
        std::cout << value;
    std::cout << suffix << std::endl;
    std::cout.unsetf(std::ios::fixed); // std::fixed is sticky: restore default
    std::cout << std::setprecision(6);
}

static void printFloat(double d)
{
    std::cout << "float: ";
    // finite, but too big for a float (nan and inf are valid floats)
    if ((d > FLT_MAX && d <= DBL_MAX) || (d < -FLT_MAX && d >= -DBL_MAX))
        std::cout << "impossible" << std::endl;
    else
        printNumber(static_cast<float>(d), "f");
}

static void printDouble(double d)
{
    std::cout << "double: ";
    printNumber(d, "");
}

void printAll(double d)
{
    printChar(d);
    printInt(d);
    printFloat(d);
    printDouble(d);
}