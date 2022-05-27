#pragma once
#include <iostream>
#include <map>
#include "../utils/Money.h"

enum dish_type
{
    przystawka,
    danie_glowne,
    deser,
    napoje
};

class Dish
{
    int id;
    std::string name;
    dish_type type;
    // alergeny
    Money price;
    bool is_vegan;
    std::map<std::string, int> ingredients;
    // czas przygotowania dania

public:
    int get_id() const { return id; };
    std::string get_name() const { return name; };
    dish_type get_dish_type() const { return type; };
    Money get_price() const { return price;};
    void print_ingredients() const;
    Dish(int i, std::string n, dish_type t, Money pr,
         bool veg, std::map<std::string, int> ingr);
    friend std::ostream& operator<<(std::ostream& os, Dish const& dish);
};