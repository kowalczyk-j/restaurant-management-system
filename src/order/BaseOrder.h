#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../dish_menu/Dish.h"
#include <json/json.h>


class BaseOrder{
    protected:
    unsigned int order_id;              //unikatowy identyfikator zamówienia
    std::vector<Dish> ordered_dishes;   //zamówione dania

    public:
    //konstruktor
    BaseOrder(unsigned int id, std::vector<Dish> o_d):order_id(id), ordered_dishes(o_d){};
    unsigned int get_order_id() {return order_id;}

    //gettery
    std::vector<Dish> & get_ordered_dishes() {return ordered_dishes;}
    void add_dish(Dish & d){ordered_dishes.push_back(d);}

    //generator obiektu JSON
    virtual Json::Value parse_to_JSON(){
        Json::Value order;
        Json::Value dishes(Json::arrayValue);
        for(size_t i=0; i<ordered_dishes.size(); i++){
            dishes.append(ordered_dishes[i].parse_dish_to_json());
        }
        order["id"] = order_id;
        order["dishes"] = dishes;
        return order;
    };

    Money get_order_value() const{
        Money m;
        for (size_t i=0;  i<ordered_dishes.size(); i++){
            m += ordered_dishes[i].get_price();
        }
        return m;
    };
};