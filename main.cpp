#include <iostream>
#include "optional.h"
#include <string>

int main()
{
    optional<int> a = 7;
    optional<int> b;
    a = a;

    if (a)
        std::cout << 1;
    else std::cout << 2;
    std::cout << *a;

    return 0;
}