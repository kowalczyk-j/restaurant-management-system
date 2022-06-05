#pragma once
#include "BaseOrder.h"


class DeliveryOrder : public BaseOrder{
    Addres delivery_address;        //adres dostawy

    public:
    DeliveryOrder(std::vector<unsigned int> & o_d, unsigned int e_id, Addres a): BaseOrder(o_d, e_id), delivery_address(a){order_type=0;};
    Addres & get_delivery_address(){return delivery_address;}

    //operacje na obiektach JSON
    Json::Value parse_to_json(){
        Json::Value Delivery = BaseOrder::parse_to_json();
        Delivery["delivery_address"] = delivery_address.parse_to_json();
        return Delivery;
    }

    /*
    static DeliveryOrder parse_from_JSON(Json::Value dor) {
        vector<Dish> ordered_dishes;
        for(auto it = dor["dishes"].begin(); it != dor["dishes"].end(); it++){
            Dish d_order = Dish::parse_dish_from_json(*it);
            ordered_dishes.push_back(d_order);
        }
        return DeliveryOrder(dor["id"].asInt(), ordered_dishes, Addres::parse_from_json(dor["delivery_address"]), dor["deliverer_id"].asInt());
    }*/
};