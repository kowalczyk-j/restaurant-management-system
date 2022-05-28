#include "Dish.h"
#include <iostream>
#include <map>
#include <set>

void Dish::print_ingredients() const
{
    std::cout << "Lista składników - " << name << ": \n";
    for (const auto& [key, value] : ingredients) {
        std::cout << key << " - " << value.get_quantity() << ' ' << value.get_unit() << "; ";
    std::cout << "\n";
    }
}

std::ostream& operator<<(std::ostream& os, Dish const& dish)
{
    return os << dish.name << "\t" << dish.price << "\n";
}