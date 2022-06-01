#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../dish_menu/Dish.h"
#include <json/json.h>


class BaseOrder{
    protected:
    unsigned int order_id=0;              //unikatowy identyfikator zamówienia
    std::vector<unsigned int> ordered_dishes;   //zamówione dania
    unsigned int served_employee_id;

    public:
    //konstruktor
    BaseOrder(std::vector<unsigned int> & o_d, unsigned int e_id):ordered_dishes(o_d), served_employee_id(e_id){};
    virtual ~BaseOrder(){};
    unsigned int get_id() {return order_id;}
    unsigned int get_employee_id(){return served_employee_id;}

    //gettery
    std::vector<unsigned int>  get_ordered_dishes() {return ordered_dishes;}
    //void add_dish(Dish & d){ordered_dishes.push_back(d);}

    void set_id(unsigned int id){order_id = id;}

/*
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
    };*/
};