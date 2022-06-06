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

};