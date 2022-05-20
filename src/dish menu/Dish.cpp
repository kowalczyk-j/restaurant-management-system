#include "Dish.h"
#include <iostream>
#include <map>

Dish::Dish(int i, std::string n, std::string des, double pr,
    bool veg, std::map<std::string, double> ingr)
    {
        id = i;
        name = n;
        description = des;
        price = pr;
        is_vegan = veg;
        ingredients = ingr;
    }

void Dish::print_ingredients() const
{
    std::cout << "Lista składników - " << get_name() << ": \n";
    for (const auto& [key, value] : ingredients) {
        std::cout << key << " - " << value << "; ";
    std::cout << "\n";
    }
}

std::ostream& operator<<(std::ostream& os, Dish const& dish)
{
    return os << dish.name << "\t" << dish.price << " zł\n";
}