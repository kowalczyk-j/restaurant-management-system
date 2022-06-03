#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../dish_menu/Dish.h"
#include <json/json.h>
#include "../utils/Address.h"

class BaseOrder{
    protected:
    unsigned int order_id=0;              //unikatowy identyfikator zamówienia
    std::vector<unsigned int> ordered_dishes;   //zamówione dania
    unsigned int served_employee_id;
    unsigned int order_type;

    public:
    //konstruktor
    BaseOrder(std::vector<unsigned int> o_d, unsigned int e_id):ordered_dishes(o_d), served_employee_id(e_id){};
    virtual ~BaseOrder(){};
    unsigned int get_id() {return order_id;}
    unsigned int get_employee_id(){return served_employee_id;}
    unsigned int get_order_type(){return order_type;}
    //virtual Addres & get_delivery_addres(){}


    //gettery
    std::vector<unsigned int>  get_ordered_dishes() {return ordered_dishes;}
    void add_dish(unsigned int dish_id){ordered_dishes.push_back(dish_id);}
    void remove_dish(unsigned int position){ordered_dishes.erase(ordered_dishes.begin()+position);}

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
*/

};