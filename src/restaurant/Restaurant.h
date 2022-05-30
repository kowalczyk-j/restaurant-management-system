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
    unsigned int restaurant_id;     //id restauracji
    std::string name;               //nazwa restauracji
    Addres address;                 //adres restuaracji
    Pantry pantry;                  //spiżarania restauracji
    Menu  menu;                     //menu restauracji
    std::set<int> employee_ids;     //zbiór id pracowników restauracji - w celu zapewnienia unikatowości
    std::set<int> orders_id;        //zbiór id zamówień - w celu zapewnienia unikatowości
    Staff<Cook> cooks;              //kucharze zatrudnieni w restauracji
    Staff<Deliverer> deliverers;    //dostawcy zatrudnieni w restauracji
    Staff<Manager> managers;        //managerowie zatrudnieni w restauracji
    Staff<Waiter> waiters;          //kelnerzy zatrudnieni w restauracji
    std::vector<DeliveryOrder> delivery_orders;     //zamówienia z dostawą
    std::vector<OnSiteOrder> onsite_orders;         //zamówienia na miejscu

    public:

    //konstruktor
    Restaurant(unsigned int r_id, std::string n, Addres a, Pantry  p, Menu m, Staff<Cook> c,
               Staff<Deliverer> d, Staff<Manager> mng, Staff<Waiter> w, std::vector<DeliveryOrder> dor,  std::vector<OnSiteOrder> oo );

    //gettery
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

    //operacje na seatch id pracowników i zamówień w celu zapewnienia unikatowości
    void add_delivery_order(unsigned int id, std::vector<Dish> vd, Addres a, unsigned d_id);
    void remove_delivery_order(unsigned int position);
    void add_on_site_order(unsigned int id, std::vector<Dish> vd, unsigned t_id, unsigned int w_id);
    void remove_on_site_order(unsigned int position);
    void add_and_check_employee_id(int id);
    void remove_emoloyee_id(int id);

    //obsługa wejścia z plikó w formacie JSON
    Json::Value parse_to_json();
    static Restaurant parse_from_json(Json::Value restaurant);

};
