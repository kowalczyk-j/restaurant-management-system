#pragma once
#include <set>
#include <json/json.h>
#include <fstream>
#include "../employees/Cook.h"
#include "../employees/Deliverer.h"
#include "../employees/Manager.h"
#include "../employees/Waiter.h"
#include "../order/DeliveryOrder.h"
#include "../order/OnSiteOrder.h"
#include "../Database.h"
#include "../pantry/Stock.h"


enum restaurant_exception{DishCurrentlyInOrder, EmployeeCurrentlyWithOrder, ProductCurrentlyInDish};

class Restaurant{

    unsigned int restaurant_id;     //id restauracji
    std::string name;               //nazwa restauracji
    Addres address;                 //adres restuaracji
    Database<Stock> pantry;
    Database<Dish> menu;
    Database<Employee> employee_database;
    Database<BaseOrder> active_orders;
    Database<BaseOrder> orders_history;

    public:

    //konstruktor
    Restaurant(unsigned int id, std::string n, Addres a):restaurant_id(id), name(n), address(a) {};

    //gettery
    unsigned int & get_id(){return restaurant_id;}
    std::string get_name(){return name;}
    Addres & get_address(){return address;}

    Stock * get_prodcuct(unsigned int product_id){return pantry[product_id];}
    Dish * get_dish(unsigned int dish_id){return menu[dish_id];}
    Employee * get_employee(unsigned int employee_id){return employee_database[employee_id];}
    BaseOrder * get_active_order(unsigned int order_id){return active_orders[order_id];}
    BaseOrder * get_order_from_history(unsigned int order_id){return orders_history[order_id];}

    std::vector<Stock *> get_all_prodcucts(){return pantry.get_full_data();}
    std::vector<Dish *> get_all_dishes(){return menu.get_full_data();}
    std::vector<Employee *> get_all_employees(){return employee_database.get_full_data();}
    std::vector<BaseOrder *> get_all_active_orders(){return active_orders.get_full_data();}
    std::vector<BaseOrder *> get_all_orders_from_history(){return orders_history.get_full_data();}

    int get_active_orders_number(){return active_orders.size();}
    int get_emoployee_number(){return employee_database.size();}

    /*
    ewentaulnie funkcja zwracająca kucharzy, managerow...
    */

    //dodawanie elementów do baz danych
    void add_products(std::string name, units unit, std::string allergens, unsigned int quantity){
        Stock * p = new Stock(name, unit, allergens, quantity);
        pantry.add_data(p);
    }

    void add_dish(std::string name, dish_type type, Money & price, bool is_vegan, std::vector<Ingredient> & ingredients){
        Dish * d = new Dish(name, type, price, is_vegan, ingredients);
        menu.add_data(d);
    }

    void add_cook(std::string name, std::string surname, Addres & address, Money & salary, bool is_chef){
        Cook * c = new Cook(name, surname, address, salary, is_chef);
        employee_database.add_data(c);
    }

    void add_deliverer(std::string name, std::string surname, Addres & address, Money & salary){
        Deliverer * d = new Deliverer(name, surname, address, salary);
        employee_database.add_data(d);
    }

    void add_manager(std::string name, std::string surname, Addres & address, Money & salary){
        Manager * m = new Manager(name, surname, address, salary);
        employee_database.add_data(m);
    }

    void add_waiter(std::string name, std::string surname, Addres & address, Money & salary){
        Waiter * w = new Waiter(name, surname, address, salary);
        employee_database.add_data(w);
    }

    void add_delivery_order(std::vector<unsigned int> & ordered_dishes, unsigned int deliverer_id, Addres & address){
        DeliveryOrder * dor = new DeliveryOrder(ordered_dishes, deliverer_id, address);
        active_orders.add_data(dor);
    }

    void add_on_site_order(std::vector<unsigned int> & ordered_dishes, unsigned int waiter_id, unsigned int table_id){
        OnSiteOrder * dor = new OnSiteOrder(ordered_dishes,  waiter_id, table_id);
        active_orders.add_data(dor);
    }

    /*
    void mark_order_as_done(unsigned int ){

    }
    */


    //usuwanie elementów z baz danych
    void remove_product(unsigned int id){
        std::vector<Dish *> dishes= this->get_all_dishes();
        for(auto dish:dishes){
            for(auto ing:dish->get_ingredients()){
                if(ing.stock_id == id) throw ProductCurrentlyInDish;
            }
        }
        pantry.remove_and_delete_data(id);
    }

    void remove_dish(unsigned int id){
        std::vector<BaseOrder *> orders = this->get_all_active_orders();
        for (auto order:orders){
            for(auto dish:order->get_ordered_dishes()){
                if(dish == id) throw DishCurrentlyInOrder;
            }
        }
        orders = this->get_all_orders_from_history();
        for (auto order:orders){
            for(auto dish:order->get_ordered_dishes()){
                if(dish == id) throw DishCurrentlyInOrder;
            }
        }
        menu.remove_and_delete_data(id);
    }

    void remove_employee(unsigned int id){
        employee_database.remove_and_delete_data(id);
        std::vector<BaseOrder *> orders = this->get_all_active_orders();
        for (auto order:orders){
            if(order->get_employee_id() == id) throw EmployeeCurrentlyWithOrder;
        }
        // tutaj i w przykałdzie wyżej trzeba się zastanowić, czy to naprawdę jest potrzebne
        orders = this->get_all_orders_from_history();
        for (auto order:orders){
            if(order->get_employee_id() == id) throw EmployeeCurrentlyWithOrder;
        }
    }

    void remove_active_order(unsigned int id){active_orders.remove_and_delete_data(id);}



    //funkcje specjalne
    /*
    void generate_lunch_menu()
    {
        ofstream file;
        file.open ("lunch.txt");
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        file << "Lunch menu - " << (now->tm_year + 1900) << '.'
        << (now->tm_mon + 1) << '.' <<  now->tm_mday << "\n";
        vector<size_t> types;
        for (size_t i = 1; i < dishes.size(); i++)
        {
            if(dishes[i].get_enum_dish_type() != dishes[i-1].get_enum_dish_type())
                types.push_back(i);
        }
        types.push_back(dishes.size());
        srand (time(NULL));
        file << "Przystawka:\n" << dishes[rand() % types[0]].get_name();
        file << "\nDanie główne:\n" << dishes[rand() % (types[1]-types[0])+types[0]].get_name();
        file << "\nDeser:\n" << dishes[rand() % (types[2]-types[1])+types[1]].get_name();
        file.close();
    }*/

    //obsługa wejścia z plikó w formacie JSON
    //Json::Value parse_to_json();
    //static Restaurant parse_from_json(Json::Value restaurant);

};
