#pragma once
#include "AbstractOrder.h"
#include "../utils/Address.h"
#include <json/json.h>

class DeliveryOrder : AbstractOrder{
    Addres delivery_address;
    unsigned int deliverer_id;

    public:
    DeliveryOrder(unsigned int id, std::vector<Dish> o_d, Addres a, unsigned int d_id): AbstractOrder(id, o_d), delivery_address(a), deliverer_id(d_id){};
    Addres get_delivery_address(){return delivery_address;}
    unsigned int get_deliverer_id(){return deliverer_id;}
};