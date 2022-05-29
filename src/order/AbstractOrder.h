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
    std::vector<Dish> & get_ordered_dishes() {return ordered_dishes;}
    virtual Json::Value parse_to_JSON(){
        Json::Value order;
        Json::Value dishes(Json::arrayValue);
        for(size_t i=0; i<ordered_dishes.size(); i++){
            dishes.append(Json::Value(ordered_dishes[i].get_name()));
        }
        order["id"] = order_id;
        order["dishes"] = dishes;
        return order;
    };
    virtual void parse_from_JSON(){};
    Money get_order_value() const{
        Money m;
        for (size_t i=0;  i<ordered_dishes.size(); i++){
            m += ordered_dishes[i].get_price();
        }
        return m;
    };
};