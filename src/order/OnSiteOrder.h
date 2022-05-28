#pragma once
#include <vector>
#include "AbstractOrder.h"
#include <json/json.h>

class OnSiteOrder : public AbstractOrder{
    unsigned int table_id;
    unsigned int waiter_id;

    public:
    OnSiteOrder(unsigned int id, std::vector<Dish> o_d, unsigned int tb_id, unsigned int w_id): AbstractOrder(id, o_d), table_id(tb_id), waiter_id(w_id){};
    unsigned int get_table_id(){return table_id;}
    unsigned int get_waiter_id(){return waiter_id;}
    virtual Json::Value parse_to_JSON() const{
        Json::Value order;
        Json::Value dishes(Json::arrayValue);
        for(size_t i=0; i<ordered_dishes.size(); i++){
            dishes.append(Json::Value(ordered_dishes[i].get_name()));
        }
        order["id"] = order_id;
        order["dishes"] = dishes;
        order["table_id"] = table_id;
        order["waiter_id"] = waiter_id;

        return order;
    }
    virtual void parse_from_JSON() const{

    }
};