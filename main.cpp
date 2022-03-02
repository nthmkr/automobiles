#include <iostream>
#include <TextNumbers.hpp>
#include <vector>

int main()
{
    setlocale(LC_CTYPE,"Russian");

    TextNumbers text_numbers;

    while(1) {
            std::cout << "Введите число:" << std::endl;

            std::string numbuf;
            std::cin >> numbuf;

            unsigned long input_long = strtoul(numbuf.c_str(), 0, 10);

            if (input_long >= UINT32_MAX) {
                std::cout << "Number too big!" << std::endl;
            } else {
                unsigned input = static_cast<unsigned>(input_long);
                std::cout << text_numbers.parsing(input) << std::endl;
            }
    }

    return 0;
}
