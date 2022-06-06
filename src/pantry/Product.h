#pragma once
#include <iostream>
#include <json/json.h>
#include <unordered_map>
#include <exception>

using namespace std;

enum units {ml, g, szt, none};

// nie wiem, czy to jesto dobre (na pewno jest tanie :)
static unordered_map<units, string> units_map = {{ml, "ml"},{szt, "szt"},{g, "g"}, {none, "none"}};

class Product{

    unsigned int product_id=0;      //id produktu
    string name;                    //nazwa produktu
    units unit;                     //jednostka
    string allergen;                //alergeny
    int quantity;                   //ilość na magazynie
    int available_quantity;         //dostępna ilość uwzględniająca przyjęte zamówienia

    public:

    //konstruktor
    Product(string n = "", units u = none, string a = "", int q=0, int aq=-1):
    name(n), unit(u), allergen(a){
        if(aq == -1){available_quantity=q;}
        else if(aq < 0){throw std::invalid_argument("Quantity cannot be negative!");}
        if(q < 0){throw std::invalid_argument("Quantity cannot be negative!");}
        quantity = q;
    }

    //gettery
    string const& get_name() const& {return name;}
    string const& get_unit() & {return units_map[unit];}
    units get_enum_unit() const{return unit;}
    string const& get_allergen() const& {return allergen;}
    unsigned int get_id() const{return product_id;}
    int get_quantity() const {return quantity;}
    int get_available_quantity() const {return available_quantity;}

    //settery
    void set_name(string n){name = n;}
    void set_allergen(string a){allergen = a;}
    void set_id(unsigned int id){product_id = id;}


    //manipulatory ilością produktu

    void operator+=(int quantity_to_add){
        // dodaje pewną ilość produktu na stan zwiększająć jednocześnie ilość dostępngo produktu
        if(quantity + quantity_to_add < 0){throw std::invalid_argument("Quantity cannot be negative!");}
        quantity += quantity_to_add;
        available_quantity += quantity_to_add;
    }

    void operator-=(int quantity_to_sub){
        // zabiera produkt redukując jednocześnie ilość dostępngo produktu
        // w przyszłości należałoby lepiej sprawdzać, czy po zabraniu ilość porduktu nie jest zbyt mała do realizajci zamówień
        *this += (-quantity_to_sub);
    }

    void reserve(int quantity){
        // rezerwuje produkt (zmniejsza ilość dostępnego produktu) na poczet zamówienia
        if(available_quantity - quantity < 0){throw std::invalid_argument("Quantity cannot be negative!");}
        available_quantity -= quantity;
    }

    void release(int quantity){
        // zwalnia produkt (zwiększa ilość dostępnego produktu) po usunięciu z zamówienia
        if(available_quantity + quantity < 0){throw std::invalid_argument("Quantity cannot be negative!");}
        available_quantity += quantity;
    }

    void use_product(int quantity_to_take){
        // odejmuje wykorzystaną ilość produktu po faktycnzym zrealizowaniu zamówienia
        quantity -= quantity_to_take;
    }

    void print_product(){
        cout << "Nazwa: " << name << endl;
        cout << "Ilość: " << quantity << " " << units_map[unit] << endl;
        cout << "Alergen: " << allergen << endl;
        cout << "\n\n";
    }



    //konwertery do formtu JSON
    Json::Value parse_to_json() const{
        Json::Value product;
        product["id"] = product_id;
        product["name"] = name;
        product["unit"] = this->get_enum_unit();
        product["allergen"] = allergen;
        product["quantity"] = quantity;
        product ["available_quantity"] = available_quantity;
        return product;
    }


};