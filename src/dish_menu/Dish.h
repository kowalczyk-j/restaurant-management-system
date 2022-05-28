#pragma once
#include <iostream>
#include <map>
#include <set>
#include <bits/stdc++.h>
#include "../utils/Money.h"
#include "../pantry/Product.h"


enum dish_type {przystawka, danie_glowne, deser, napoje};

class Dish
{
    int id;
    std::string name;
    dish_type type;
    Money price;
    bool is_vegan;
    std::map<std::string, Product> ingredients;
    set<std::string> allergens;

public:
    int get_id() const { return id; }
    std::string get_name() const { return name; }
    dish_type get_dish_type() const { return type; }
    Money get_price() const { return price;}
    set<string> get_allergens() const {return allergens;}
    void print_ingredients() const
    {
        std::cout << "Lista składników - " << name << ": \n";
        for (const auto& [key, value] : ingredients) {
            std::cout << key << " - " << value.get_quantity() << ' ' << value.get_unit() << "; ";
        std::cout << "\n";
        }
    }
    void print_allergens() const
    {
        std::cout << "Alergeny: ";
        for(auto i : allergens){ //jak pozbyć się przecinka na koniec ?
            std::cout << i << ", ";
        }
    }
    Dish(int i, std::string n, dish_type t, Money pr,
    bool veg, std::map<std::string, Product> ingr, set<std::string> allerg = {}) : 
    id(i), name(n), type(t), price(pr), is_vegan(veg), ingredients(ingr)
    {
        for (const auto& [key, value] : ingredients)
        {
            if (value.get_allergen() != "")
                allerg.insert(value.get_allergen());
        }
        allergens = allerg;
    }
    friend std::ostream& operator<<(std::ostream& os, Dish const& dish)
    {
        return os << dish.name << "\t" << dish.price << "\n";
    }
};