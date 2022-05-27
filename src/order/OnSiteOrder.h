#include "AbstractOrder.h"

class OnSiteOrder : AbstractOrder{
    unsigned int table_id;
    unsigned int waiter_id;

    public:
    unsigned int get_table_id(){return table_id;}
    unsigned int get_waiter_id(){return waiter_id;}
};