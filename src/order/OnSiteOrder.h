#pragma once
#include "BaseOrder.h"

class OnSiteOrder : public BaseOrder{
    unsigned int table_id;  //id stolika

    public:
    OnSiteOrder(std::vector<unsigned int> o_d, unsigned int e_id, unsigned int tb_id): BaseOrder(o_d, e_id), table_id(tb_id){order_type=1;};
    unsigned int get_table_id(){return table_id;}

    //operacje na obiektach JSON

    virtual Json::Value parse_to_JSON() {
        Json::Value OnSite = BaseOrder::parse_to_json();
        OnSite["table_id"] = table_id;
        return OnSite;
    }
};