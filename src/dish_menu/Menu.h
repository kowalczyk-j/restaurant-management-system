#pragma once
#include <iostream>
#include <vector>
#include "Dish.h"
#include <json/json.h>

class Menu
{
    std::vector<Dish> dishes;

public:
    Menu(){};
    Menu(std::vector<Dish> dishes);
    std::vector<Dish> & get_dishes()  {return dishes;}
    void set_dishes(std::vector<Dish> d) { dishes = d; }
    size_t size() const { return dishes.size(); }
    void add_dish(Dish const& dish);
    void remove_dish(unsigned int dish_idx);

    void generate_lunch_menu();

    Json::Value parse_menu_to_json();
    static Menu parse_from_json(Json::Value m);

    friend std::ostream &operator<<(std::ostream &os, Menu &menu);
};
