#pragma once
#include <iostream>
#include <vector>
#include <json/json.h>
#include "../dish_menu/Dish.h"
#include "../utils/Address.h"

class BaseOrder{
    protected:
    unsigned int order_id=0;              //unikatowy identyfikator zamówienia
    std::vector<unsigned int> ordered_dishes;   //zamówione dania
    unsigned int served_employee_id;            //id pracownika obśługującego zamówienie
    unsigned int order_type;                    // typ dania - 0 z dowozem/1 na miejscu

    public:

    //konstruktor
    BaseOrder(std::vector<unsigned int> o_d, unsigned int e_id):ordered_dishes(o_d), served_employee_id(e_id){};

    //destruktor
    virtual ~BaseOrder(){};

    //gettery
    unsigned int get_id() const{return order_id;}
    unsigned int get_employee_id()const{return served_employee_id;}
    unsigned int get_order_type()const{return order_type;}
    virtual Addres & get_delivery_address(){Addres a = Addres(); Addres &ar = a; return ar;}
    std::vector<unsigned int> const& get_ordered_dishes() const{return ordered_dishes;}


    //settery i modyfikatory
    void set_id(unsigned int id){order_id = id;}
    void add_dish(unsigned int dish_id){ordered_dishes.push_back(dish_id);}
    void remove_dish(unsigned int position){ordered_dishes.erase(ordered_dishes.begin()+position);}

    //generator obiektu JSON
    virtual Json::Value parse_to_json(){
        Json::Value order;
        Json::Value dishes(Json::arrayValue);
        for(size_t i=0; i<ordered_dishes.size(); i++){
            dishes.append(ordered_dishes[i]);
        }
        order["dishes"] = dishes;
        order["employee_id"] = served_employee_id;
        order["type"] = order_type;
        order["id"] = order_id;
        return order;
    };


};