#pragma once
#include "AbstractOrder.h"
#include "../utils/Address.h"


class DeliveryOrder : public AbstractOrder{
    Addres delivery_address;
    unsigned int deliverer_id;

    public:
    DeliveryOrder(unsigned int id, std::vector<Dish> o_d, Addres a, unsigned int d_id): AbstractOrder(id, o_d), delivery_address(a), deliverer_id(d_id){};
    Addres get_delivery_address() const{return delivery_address;}
    unsigned int get_deliverer_id() const{return deliverer_id;}
    virtual Json::Value parse_to_JSON() const{
        Json::Value order;
        Json::Value dishes(Json::arrayValue);
        for(size_t i=0; i<ordered_dishes.size(); i++){
            dishes.append(Json::Value(ordered_dishes[i].get_name()));
        }
        order["id"] = order_id;
        order["dishes"] = dishes;
        order["delivery_address"] = get_delivery_address().parse_to_json();
        order["deliverer_id"] = deliverer_id;

        return order;
    }
    virtual void parse_from_JSON() const{

    }
};