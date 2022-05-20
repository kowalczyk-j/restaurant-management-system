#pragma once
#include <iostream>
#include <map>
class Dish
{
    int id;
    std::string name;
    std::string description;
    // std::string type; //{przystawka/ danie główne/ deser?}
    // alergeny
    double price;
    bool is_vegan;
    std::map<std::string, double> ingredients;

public:
    int get_id() const { return id; };
    std::string get_name() const { return name; };
    double get_price() const { return price; };
    void print_ingredients() const;
    Dish(int i, std::string n, std::string des, double pr,
         bool veg, std::map<std::string, double> ingr);
    friend std::ostream& operator<<(std::ostream& os, Dish const& dish);
};