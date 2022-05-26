#include "../headers/webserv.hpp"


int main(int argc, char **argv)
{
    if (argc > 1)
    { 
        Http http = parsing(argv[1]);
 
    }
    return 0;
}