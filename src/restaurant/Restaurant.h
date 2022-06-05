#pragma once
#include <set>
#include <json/json.h>
#include <fstream>
#include <ctime>
#include "../employees/Cook.h"
#include "../employees/Deliverer.h"
#include "../employees/Manager.h"
#include "../employees/Waiter.h"
#include "../order/DeliveryOrder.h"
#include "../order/OnSiteOrder.h"
#include "../Database.h"
#include "../pantry/Product.h"


enum restaurant_exception{DishCurrentlyInOrder, EmployeeCurrentlyWithOrder, ProductCurrentlyInDish, NotEnoughtProductInPantry, NotEnoughDishType};

class Restaurant{

    unsigned int restaurant_id;     //id restauracji
    std::string name;               //nazwa restauracji
    Addres address;                 //adres restuaracji
    Database<Product> pantry;
    Database<Dish> menu;
    Database<Employee> employee_database;
    Database<BaseOrder> active_orders;
    Database<BaseOrder> orders_history;

    public:

    //konstruktor
    Restaurant(unsigned int id, std::string n, Addres a):restaurant_id(id), name(n), address(a) {};

    //gettery
        //podstawowe dane
    unsigned int & get_id(){return restaurant_id;}
    std::string get_name(){return name;}
    Addres & get_address(){return address;}

        //pojedyncze elementy z baz danych, dostępne po id
    Product * get_product(unsigned int product_id){return pantry[product_id];}
    Dish * get_dish(unsigned int dish_id){return menu[dish_id];}
    Employee * get_employee(unsigned int employee_id){return employee_database[employee_id];}
    BaseOrder * get_active_order(unsigned int order_id){return active_orders[order_id];}
    BaseOrder * get_order_from_history(unsigned int order_id){return orders_history[order_id];}

        //wsztskie elemnty z baz danych
    std::vector<Product *> get_all_prodcucts(){return pantry.get_full_data();}
    std::vector<Dish *> get_all_dishes(){return menu.get_full_data();}
    std::vector<Employee *> get_all_employees(){return employee_database.get_full_data();}
    std::vector<BaseOrder *> get_all_active_orders(){return active_orders.get_full_data();}
    std::vector<BaseOrder *> get_all_orders_from_history(){return orders_history.get_full_data();}

        //wartości zbiorcze
    int get_active_orders_number(){return active_orders.size();}
    int get_emoployee_number(){return employee_database.size();}
    int get_dishes_number(){return menu.size();}
    int get_products_number(){return pantry.size();}


    //dodawanie elementów do baz danych
    unsigned int add_product(std::string const& name, units unit, std::string const& allergens, unsigned int quantity);
    unsigned int add_dish(unsigned int id, std::string const& name, dish_type type, Money const& price, bool is_vegan, std::vector<Ingredient> & ingredients);
    unsigned int add_cook(std::string const& name , std::string const& surname, Addres const& address, Money const& salary, bool is_chef);
    unsigned int add_deliverer(std::string const& name, std::string const& surname, Addres const& address, Money const& salary);
    unsigned int add_manager(std::string const& name, std::string const& surname, Addres const& address, Money const& salary);
    unsigned int add_waiter(std::string const& name, std::string const& surname, Addres const& address, Money const& salary);
    unsigned int add_delivery_order(std::vector<unsigned int> ordered_dishes, unsigned int deliverer_id, Addres const& address);
    unsigned int add_on_site_order(std::vector<unsigned int> ordered_dishes, unsigned int waiter_id, unsigned int table_id);

    //usuwanie elementów z baz danych
    void remove_product(unsigned int id);
    void remove_dish(unsigned int id);
    void remove_employee(unsigned int id);
    void remove_active_order(unsigned int id);

    //specjalna funckje do dodawania i usuwania dań w zamówieniu w celu zapewnienia wystarczającej ilości zapasów
    void add_dish_to_order(unsigned int order_id, int dish_id);
    void remove_dish_from_order(unsigned int order_id, int position);

    //funkcje specjalne
    Money get_active_order_value(unsigned int order_id);
    void mark_order_as_done(unsigned int order_id);
    void generate_lunch_menu();

    //obsługa wejścia z plikó w formacie JSON
    Json::Value parse_to_json();

};
