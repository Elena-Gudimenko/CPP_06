#include "Serializer.hpp"
#include <iostream>

int main()
{
    Data original;
    original.id = 25;
    original.name = "Elena";
    original.value = 3.14;

    Data* ptr = &original;

    // Pointer -> number
    uintptr_t raw = Serializer::serialize(ptr);
    // Number -> pointer
    Data* restored = Serializer::deserialize(raw);

    std::cout << "Original pointer:  " << ptr << std::endl;
    std::cout << "Serialized (dec):  " << raw << std::endl;
    std::cout << "Serialized (hex):  0x" << std::hex << raw << std::dec << std::endl;
    std::cout << "Restored pointer:  " << restored << std::endl;

    if (restored == ptr)
        std::cout << "OK: pointers are equal" << std::endl;
    else
        std::cout << "ERROR: pointers are different" << std::endl;

    // The restored pointer gives access to the same object
    std::cout << "restored->id:    " << restored->id << std::endl;
    std::cout << "restored->name:  " << restored->name << std::endl;
    std::cout << "restored->value: " << restored->value << std::endl;

    // Changing through the restored pointer changes the original
    restored->id = 100;
    std::cout << "After restored->id = 100, original.id = " << original.id << std::endl;

    return 0;

}