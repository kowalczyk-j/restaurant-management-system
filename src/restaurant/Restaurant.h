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

enum exceptions {DuplicatedEmployeeID, DuplicatedOrderID};

class Restaurant{
    unsigned int restaurant_id;
    std::string name;
    Addres address;
    Pantry pantry;
    Menu  menu;
    std::set<int> employee_ids;
    std::set<int> orders_id;
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
               waiters(w), delivery_orders(dor), onsite_orders(oo){
                   for(size_t i=0; i<delivery_orders.size(); i++){
                        if (orders_id.find(delivery_orders[i].get_order_id()) != orders_id.end()) {
                            throw DuplicatedOrderID;
                        }
                        orders_id.insert(delivery_orders[i].get_order_id());
                   }
                   for(size_t i=0; i<onsite_orders.size(); i++){
                        if (orders_id.find(onsite_orders[i].get_order_id()) != orders_id.end()) {
                            throw DuplicatedOrderID;
                        }
                        orders_id.insert(onsite_orders[i].get_order_id());
                   }
                    for(size_t i=0; i<cooks.size(); i++){add_and_check_employee_id(cooks[i].get_employee_id());}
                    for(size_t i=0; i<deliverers.size(); i++){add_and_check_employee_id(deliverers[i].get_employee_id());}
                    for(size_t i=0; i<managers.size(); i++){add_and_check_employee_id(managers[i].get_employee_id());}
                    for(size_t i=0; i<waiters.size(); i++){add_and_check_employee_id(waiters[i].get_employee_id());}
               };

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
    int get_orders_number(){return orders_id.size();}
    int get_emoployee_number(){return employee_ids.size();}

    void add_delivery_order(unsigned int id, std::vector<Dish> vd, Addres a, unsigned d_id){
        if (orders_id.find(id) != orders_id.end()) {
            throw DuplicatedOrderID;
        }
        orders_id.insert(id);
        DeliveryOrder delivery_order = DeliveryOrder(id, vd, a, d_id);
        delivery_orders.push_back(delivery_order);
    };
    void remove_delivery_order(unsigned int position){
        orders_id.erase(orders_id.find(delivery_orders[position].get_order_id()));
        delivery_orders.erase(delivery_orders.begin()+position);
    }
    void add_on_site_order(unsigned int id, std::vector<Dish> vd, unsigned t_id, unsigned int w_id){
        if (orders_id.find(id) != orders_id.end()) {
            throw DuplicatedOrderID;
        }
        orders_id.insert(id);
        OnSiteOrder delivery_order = OnSiteOrder(id, vd, t_id, w_id);
        onsite_orders.push_back(delivery_order);
    };
    void remove_on_site_order(unsigned int position){
        orders_id.erase(orders_id.find(onsite_orders[position].get_order_id()));
        onsite_orders.erase(onsite_orders.begin()+position);
    }

    void add_and_check_employee_id(int id){
        if (employee_ids.find(id) != employee_ids.end()) {
            throw DuplicatedEmployeeID;
        }
        employee_ids.insert(id);
    }
    void remove_emoloyee_id(int id){
        employee_ids.erase(employee_ids.find(id));
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

    static Restaurant create_from_json(Json::Value restaurant){
        std::cout<<"lalal";
        std::string name = restaurant["name"].asString();
        int id = restaurant["id"].asUInt();
        Addres a = Addres::read_from_json(restaurant["address"]);
        Pantry p = Pantry::read_from_file_json(restaurant["pantry"]);
        Menu m = Menu::parse_from_json(restaurant["menu"]);
        std::vector<DeliveryOrder> dorv;
        for(auto it = restaurant["orders"]["delivery"].begin(); it != restaurant["orders"]["delivery"].end(); it++){
            DeliveryOrder dor = DeliveryOrder::parse_from_JSON(*it);
            dorv.push_back(dor);
        }
        std::vector<OnSiteOrder> osorv;
        for(auto it = restaurant["orders"]["on_site"].begin(); it != restaurant["orders"]["on_site"].end(); it++){
            OnSiteOrder oso = OnSiteOrder::parse_from_JSON(*it);
            osorv.push_back(oso);
        }
        Staff<Cook> cookers = Staff<Cook>(restaurant["employees"]["cooks"]);
        Staff<Deliverer> deliverers = Staff<Deliverer>(restaurant["employees"]["deliverers"]);
        Staff<Manager> managers = Staff<Manager>(restaurant["employees"]["managers"]);
        Staff<Waiter> waiters = Staff<Waiter>(restaurant["employees"]["waiters"]);

        return Restaurant(id, name, a, p, m, cookers, deliverers, managers, waiters, dorv, osorv);
    }

};
