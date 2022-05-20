#include <iostream>
#include <vector>
#include "Menu.h"

std::ostream& operator<<(std::ostream& os, Menu const& menu)
{
    os << "---Menu---\n";
    for(int i = 0; i < menu.size(); i++)
    {
        os << menu.get_dishes()[i];
    }
    return os;
}