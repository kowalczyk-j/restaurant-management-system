#pragma once
#include <iostream>
#include <vector>
#include "Dish.h"

class Menu
{
    int id; // do usunięcia
    std::vector<Dish> dishes;

public:
    int get_id() const { return id; };
    std::vector<Dish> get_dishes() const { return dishes; };
    int size() const { return dishes.size(); };
    Menu(int i, std::vector<Dish> di) : id(i), dishes(di)
    {}
    void add_dish(Dish const& dish)
    {
        dishes.push_back(dish);
    }
    void remove_dish(int dish_idx);
    friend std::ostream &operator<<(std::ostream &os, Menu const &menu);
};