#include <iostream>

#include "Interface.h"

int main(int argc, char *argv[])
{

    Interface i{};
    i.menu_principal(cout, cin);

    return 0;
}
