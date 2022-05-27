#include <iostream>
#include <vector>
#include "../pantry/Pantry.h"
#include "../employees/Manager.h"
#include "../employees/Cook.h"
#include "../employees/Deliverer.h"
#include "../employees/Waiter.h"
#include "../dish menu/Menu.h"
#include "../order/DeliveryOrder.h"
#include "../order/OnSiteOrder.h"

class Restaurant{
    Pantry pantry;
    Menu  menu;
    std::vector<AbstractOrder> orders;
    std::vector<Employee> employees;

};