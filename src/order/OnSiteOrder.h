#pragma once
#include <vector>
#include "AbstractOrder.h"
#include <json/json.h>

class OnSiteOrder : AbstractOrder{
    unsigned int table_id;
    unsigned int waiter_id;

    public:
    OnSiteOrder(unsigned int id, std::vector<Dish> o_d, unsigned int tb_id, unsigned int w_id): AbstractOrder(id, o_d), table_id(tb_id), waiter_id(w_id){};
    unsigned int get_table_id(){return table_id;}
    unsigned int get_waiter_id(){return waiter_id;}
};