#include "../../headers/parsing.hpp"

void check_file(std::ifstream &fin)
{
    if (!fin.is_open())
    {
        std::cout << "Can't open file\n";
        exit(1);
    }
    if (fin.peek() == EOF)
    {
         std::cout << "Empty file\n";
        exit(1);
    }
}

void syntax_error()
{
    std::cout << "Syntax Error!\n";
    exit(1);
}