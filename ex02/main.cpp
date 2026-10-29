#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>   // std::rand, std::srand
#include <ctime>     // std::time

// Randomly creates A, B or C and returns it as a Base pointer
Base* generate(void)
{
    int r = std::rand() % 3;

    if (r == 0)
    {
        std::cout << "Generated: A" << std::endl;
        return new A;
    }
    else if (r == 1)
    {
        std::cout << "Generated: B" << std::endl;
        return new B;
    }
    std::cout << "Generated: C" << std::endl;
    return new C;
}

// dynamic_cast on a pointer returns NULL if the object is not of that type
void identify(Base* p)
{
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown" << std::endl;
}

void identify(Base& p)
{
    try
    {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    }
    catch (...) {}

    try
    {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    }
    catch (...) {}

    try
    {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    }
    catch (...) {}

    std::cout << "Unknown" << std::endl;
}


int main()
{
    // Seed the random generator once, so each run gives different results
    std::srand(std::time(NULL));

    for (int i = 0; i < 5; i++)
    {
        Base* p = generate();

        std::cout << "identify(Base*): ";
        identify(p);
        std::cout << "identify(Base&): ";
        identify(*p);
        std::cout << std::endl;

        delete p; // virtual destructor: the real A / B / C is destroyed
    }
    return 0;
}
