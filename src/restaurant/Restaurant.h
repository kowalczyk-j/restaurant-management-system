#pragma once
#include "../pantry/Pantry.h"
#include "../employees/Staff.h"
#include "../employees/Cook.h"
#include "../employees/Deliverer.h"
#include "../employees/Manager.h"
#include "../employees/Waiter.h"
#include "../dish_menu/Menu.h"
#include "../order/DeliveryOrder.h"
#include "../order/OnSiteOrder.h"

class Restaurant{
    unsigned int restaurant_id;
    std::string name;
    Addres address;
    Pantry pantry;
    Menu  menu;
    Staff<Cook> cooks;
    Staff<Deliverer> deliverers;
    Staff<Manager> managers;
    Staff<Waiter> waiters;
    std::vector<DeliveryOrder*> orders; // bvć może do zmiany  - obecnie wektor wskaźnikow na zamowienia

    public:
    Restaurant(unsigned int r_id, std::string n, Addres a, Pantry  p, Menu m, Staff<Cook> c,
               Staff<Deliverer> d, Staff<Manager> mng, Staff<Waiter> w, std::vector<DeliveryOrder*> o ):
               restaurant_id(r_id), name(n), address(a), pantry(p), menu(m), cooks(c), deliverers(d), managers(mng),
               waiters(w), orders(o) {};

    Addres & get_address(){return address;}
    Pantry & get_pantry(){return pantry;}
    Menu & get_menu(){return menu;}
    std::vector<DeliveryOrder*> & get_orders(){return orders;}
    Staff<Cook>& get_cooks() const {return cooks};
    Staff<Deliverer>& get_deliverers() const {return deliverers};
    Staff<Manager>& get_managers() const {return managers};
    Staff<Waiter>& get_waiters() const {return waiters};
    std::string get_name(){return name;}

    void add_delivery_order(unsigned int id, std::vector<Dish> vd, Addres a, unsigned d_id){
        DeliveryOrder * delivery_order = new DeliveryOrder(id, vd, a, d_id);
        orders.push_back(delivery_order);
    };
    void remove_delivery_order(unsigned int position){
        orders.erase(orders.begin()+position); // prawdopodobnie przydałby się jeszcze destruktor, ale musze nad tym jeszcze pomyslec
    }

};
