#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../dish_menu/Dish.h"
#include <json/json.h>


class AbstractOrder{
    protected:
    unsigned int order_id;
    std::vector<Dish> ordered_dishes;

    public:
    AbstractOrder(unsigned int id, std::vector<Dish> o_d):order_id(id), ordered_dishes(o_d){};
    unsigned int get_order_id() {return order_id;}
    std::vector<Dish> const& get_ordered_dishes() const {return ordered_dishes;}
    virtual Json::Value parse_to_JSON()const = 0;
    virtual void parse_from_JSON() const = 0;
    Money get_order_value() const{
        Money m;
        for (size_t i=0;  i<ordered_dishes.size(); i++){
            m += ordered_dishes[i].get_price();
        }
        return m;
    };
};