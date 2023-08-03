#include "defines.h"
#include <iostream>
#include "error_list.h"

int main()
{
    u32 my_number = 0;
    std::cout << "Hello, Nameless Engine!\nMy number = " << my_number << "\n";
    std::cout << error_names[ERR_END] << "\n";
    return 0;
}