#pragma once
#include "BaseOrder.h"
#include "../utils/Address.h"


class DeliveryOrder : public BaseOrder{
    Addres delivery_address;        //adres dostawy
    unsigned int deliverer_id;      //id dostawcy

    public:
    DeliveryOrder(std::vector<unsigned int> & o_d, unsigned int e_id, Addres a): BaseOrder(o_d, e_id), delivery_address(a){order_type=0;};
    virtual ~DeliveryOrder(){};
    Addres & get_delivery_address(){return delivery_address;}
    unsigned int get_deliverer_id() const{return deliverer_id;}

    //operacje na obiektach JSON
    /*
    virtual Json::Value parse_to_JSON(){
        Json::Value Delivery = BaseOrder::parse_to_JSON();
        Delivery["delivery_address"] = get_delivery_address().parse_to_json();
        Delivery["deliverer_id"] = deliverer_id;
        return Delivery;
    }
    static DeliveryOrder parse_from_JSON(Json::Value dor) {
        vector<Dish> ordered_dishes;
        for(auto it = dor["dishes"].begin(); it != dor["dishes"].end(); it++){
            Dish d_order = Dish::parse_dish_from_json(*it);
            ordered_dishes.push_back(d_order);
        }
        return DeliveryOrder(dor["id"].asInt(), ordered_dishes, Addres::parse_from_json(dor["delivery_address"]), dor["deliverer_id"].asInt());
    }
    */
};