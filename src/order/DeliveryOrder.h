#include "AbstractOrder.h"
#include "../utils/Address.h"

class DeliveryOrder : AbstractOrder{
    Addres delivery_address;
    unsigned int deliverer_id;

    public:
    Addres get_delivery_address(){return delivery_address;}
    unsigned int get_deliverer_id(){return deliverer_id;}
};