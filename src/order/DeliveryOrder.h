#pragma once
#include "AbstractOrder.h"
#include "../utils/Address.h"


class DeliveryOrder : public AbstractOrder{
    Addres delivery_address;
    unsigned int deliverer_id;

    public:
    DeliveryOrder(unsigned int id, std::vector<Dish> o_d, Addres a, unsigned int d_id): AbstractOrder(id, o_d), delivery_address(a), deliverer_id(d_id){};
    Addres & get_delivery_address(){return delivery_address;}
    unsigned int get_deliverer_id() const{return deliverer_id;}
    virtual Json::Value parse_to_JSON(){
        Json::Value Delivery = AbstractOrder::parse_to_JSON();
        Delivery["delivery_address"] = get_delivery_address().parse_to_json();
        Delivery["deliverer_id"] = deliverer_id;
        return Delivery;
    }
    virtual void parse_from_JSON() {

    }
};