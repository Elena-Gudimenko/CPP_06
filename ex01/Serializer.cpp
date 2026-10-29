#include "Serializer.hpp"

Serializer::Serializer() {}
Serializer::Serializer(const Serializer& other) { (void)other; }
Serializer& Serializer::operator=(const Serializer& other) { (void)other; return *this; }
Serializer::~Serializer() {}

// Pointer -> integer: the same bits, now seen as a number
uintptr_t Serializer::serialize(Data* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

// Integer -> pointer: the same bits, seen as an address again
Data* Serializer::deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data*>(raw);
}