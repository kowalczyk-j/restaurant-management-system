#pragma once
#include "../pantry/Pantry.h"
#include "../employees/Manager.h"
#include "../employees/Cook.h"
#include "../employees/Deliverer.h"
#include "../employees/Waiter.h"
#include "../dish_menu/Menu.h"
#include "../order/DeliveryOrder.h"
#include "../order/OnSiteOrder.h"

class Restaurant{
    Addres address;
    Pantry pantry;
    Menu  menu;
    std::vector<Employee> employees;
    std::vector<AbstractOrder*> orders; // bvć może do zmiany  - obecnie wektor wskaźnikow na zamowienia

    public:
    Restaurant(Addres a, Pantry  p, Menu m ,std::vector<Employee>  e, std::vector<AbstractOrder*> o ):
    address(a), pantry(p), menu(m),employees(e), orders(o) {};

    Addres & get_address(){return address;}
    Pantry & get_pantry(){return pantry;}
    Menu & get_menu(){return menu;}
    std::vector<AbstractOrder*> & get_orders(){return orders;}
    std::vector<Employee> & get_employees(){return employees;}

};