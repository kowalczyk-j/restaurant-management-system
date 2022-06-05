#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include <json/json.h>
#include <exception>

using namespace std;

enum units {ml, g, szt, none};

class Product{

    unsigned int product_id=0;
    string name;
    units unit;
    string allergen;
    int quantity;
    int available_quantity;

    public:
    //konstruktor
    Product(string n = "", units u = none, string a = "", int q=0):
    name(n), unit(u), allergen(a){
        if(q < 0){throw std::invalid_argument("Quantity cannot be negative!");}
        quantity = q;
        available_quantity = q;
    }

    //gettery
    string get_name() const{return name;}
    string get_unit() const{
        unordered_map<units, string> units_map = {{ml, "ml"},{szt, "szt"},{g, "g"}, {none, "none"}};
        return units_map[unit];
    }
    units get_enum_unit() const{return unit;}
    string get_allergen() const {return allergen;}
    unsigned int get_id() const{return product_id;}
    int get_quantity() const {return quantity;}
    int get_available_quantity() const {return available_quantity;}

    //settery
    void set_name(string n){name = n;}
    void set_allergen(string a){allergen = a;}
    void set_id(unsigned int id){product_id = id;}



    void set_quantity(int q){
        if(q < 0){throw std::invalid_argument("Quantity cannot be negative!");}
        quantity = q;
    }

    void operator+=(int quantity_to_add){
        if(quantity + quantity_to_add < 0){throw std::invalid_argument("Quantity cannot be negative!");}
        quantity += quantity_to_add;
    }


    void operator-=(int quantity_to_sub){
        *this += (-quantity_to_sub);
    }

    void reserve(int quantity){
        if(available_quantity - quantity < 0){throw std::invalid_argument("Quantity cannot be negative!");}
        available_quantity -= quantity;
    }

    void release(int quantity){
        if(available_quantity + quantity < 0){throw std::invalid_argument("Quantity cannot be negative!");}
        available_quantity += quantity;
    }

    /*
    Json::Value parse_to_json() const{
        Json::Value add;
        add["name"] = name;
        add["unit"] = this->get_enum_unit();
        add["allergen"] = allergen;
        return add;
    }

    static Product json_to_product(Json::Value obj){
        return  Product(obj["name"].asString(), (units)obj["unit"].asUInt(), obj["allergen"].asString());
    }*/

    void print_product(){
        cout << "Nazwa: " << name << endl;
     //   cout << "Ilość: " << quantity << " " << unit << endl;
        cout << "Alergen: " << allergen << endl;
        cout << "\n\n";
    }


};