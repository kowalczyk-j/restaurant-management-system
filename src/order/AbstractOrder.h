#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../dish_menu/Dish.h"


class AbstractOrder{
    protected:
    unsigned int order_id;
    std::vector<Dish> ordered_dishes;

    public:
    AbstractOrder(unsigned int id, std::vector<Dish> o_d):order_id(id), ordered_dishes(o_d){};
    unsigned int get_order_id() const {return order_id;}
    std::vector<Dish> const& get_ordered_dishes() const {return ordered_dishes;}
    virtual void read_from_file()const = 0;
    virtual void write_to_file() const = 0;
    Money get_order_value() const;
};