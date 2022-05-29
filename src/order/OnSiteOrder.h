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
    virtual Json::Value parse_to_JSON() {
        Json::Value OnSite = AbstractOrder::parse_to_JSON();
        OnSite["table_id"] = table_id;
        OnSite["waiter_id"] = waiter_id;
        return OnSite;
    }
    static OnSiteOrder parse_from_JSON(Json::Value oso) {
        vector<Dish> ordered_dishes;
        for(auto it = oso["dishes"].begin(); it != oso["dishes"].end(); it++){
            Dish d_order = Dish::parse_dish_from_json(*it);
            ordered_dishes.push_back(d_order);
        }
        return OnSiteOrder(oso["id"].asUInt(), ordered_dishes, oso["table_id"].asUInt(), oso["waiter_id"].asUInt());
    }
};