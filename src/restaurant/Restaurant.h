#pragma once
#include <set>
#include <json/json.h>
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
    std::set<int> employee_ids;
    Staff<Cook> cooks;
    Staff<Deliverer> deliverers;
    Staff<Manager> managers;
    Staff<Waiter> waiters;
    std::vector<DeliveryOrder> delivery_orders;
    std::vector<OnSiteOrder> onsite_orders;

    public:
    Restaurant(unsigned int r_id, std::string n, Addres a, Pantry  p, Menu m, Staff<Cook> c,
               Staff<Deliverer> d, Staff<Manager> mng, Staff<Waiter> w, std::vector<DeliveryOrder> dor,  std::vector<OnSiteOrder> oo ):
               restaurant_id(r_id), name(n), address(a), pantry(p), menu(m), cooks(c), deliverers(d), managers(mng),
               waiters(w), delivery_orders(dor), onsite_orders(oo) {};

    Addres & get_address(){return address;}
    Pantry & get_pantry(){return pantry;}
    Menu & get_menu(){return menu;}
    std::vector<DeliveryOrder> & get_delivery_orders(){return delivery_orders;}
    std::vector<OnSiteOrder> & get_onsite_orders(){return onsite_orders;}
    Staff<Cook>& get_cooks() {return cooks;}
    Staff<Deliverer>& get_deliverers() {return deliverers;}
    Staff<Manager>& get_managers() {return managers;}
    Staff<Waiter>& get_waiters() {return waiters;}
    std::string get_name(){return name;}
    std::set<int>& get_employees_id_set(){return employee_ids;}

    void add_delivery_order(unsigned int id, std::vector<Dish> vd, Addres a, unsigned d_id){
        DeliveryOrder delivery_order = DeliveryOrder(id, vd, a, d_id);
        delivery_orders.push_back(delivery_order);
    };
    void remove_delivery_order(unsigned int position){
        delivery_orders.erase(delivery_orders.begin()+position);
    }

    Json::Value parse_to_json(){
        Json::Value restaurant;
        restaurant["id"] = restaurant_id;
        restaurant["address"] = address.parse_to_json();
        restaurant["name"] = name;
        restaurant["pantry"] = pantry.write_to_file_json();
        restaurant["menu"] = menu.parse_menu_to_json();

        Json::Value del = Json::arrayValue;
        for(size_t i=0; i<delivery_orders.size(); i++){
            del.append(delivery_orders[i].parse_to_JSON());
        }
        restaurant["orders"]["delivery"] = del;

        Json::Value ons = Json::arrayValue;
        for(size_t i=0; i<onsite_orders.size(); i++){
            ons.append(onsite_orders[i].parse_to_JSON());
        }
        restaurant["orders"]["on_site"] = ons;
        restaurant["employees"]["cooks"] = cooks.parse_to_json();
        restaurant["employees"]["deliverers"] = deliverers.parse_to_json();
        restaurant["employees"]["managers"] = managers.parse_to_json();
        restaurant["employees"]["waiters"] = waiters.parse_to_json();

        return restaurant;
    }

};
