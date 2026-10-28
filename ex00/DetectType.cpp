#include "DetectType.hpp"
#include <cctype>   // std::isdigit

// needDot == false: [sign] digits
// needDot == true:  [sign] digits '.' digits (exactly one dot)
static bool isNumber(const std::string& s, bool needDot)
{
    size_t i = 0;
    if (s[0] == '+' || s[0] == '-')
        i = 1; // skip the sign
    bool   hasDigit = false;
    bool   hasDot = false;

    for (; i < s.length(); i++)
    {
        if (std::isdigit(static_cast<unsigned char>(s[i])))
            hasDigit = true;
        else if (s[i] == '.' && needDot && !hasDot)
            hasDot = true;
        else
            return false;
    }
    return hasDigit && hasDot == needDot;
}

// 'a' or 'a' in quotes; a single digit is an int, not a char
bool isChar(const std::string& s)
{
    if (s.length() == 1)
        return !std::isdigit(static_cast<unsigned char>(s[0]));
    return s.length() == 3 && s[0] == '\'' && s[2] == '\'';
}

// [sign] digits
bool isInt(const std::string& s)
{
    return !s.empty() && isNumber(s, false);
}

// [sign] digits '.' digits 'f', or a float pseudo-literal
bool isFloat(const std::string& s)
{
    if (s == "nanf" || s == "inff" || s == "+inff" || s == "-inff")
        return true;
    return s.length() > 1 && s[s.length() - 1] == 'f'
        && isNumber(s.substr(0, s.length() - 1), true);
}

// [sign] digits '.' digits, or a double pseudo-literal
bool isDouble(const std::string& s)
{
    if (s == "nan" || s == "inf" || s == "+inf" || s == "-inf")
        return true;
    return !s.empty() && isNumber(s, true);
}