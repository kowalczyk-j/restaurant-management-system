#pragma once
#include <iomanip>
#include <iostream>
#include <unordered_map> //działa szybciej od mapy (nie trzeba sortować)
#include <fstream>
#include <exception>

using namespace std;

enum units {ml, g, szt, none};

class Product{

    std::string name;
    int quantity;
    units unit;
    string allergen;

    public:
    Product(std::string n = "", int q = 0, units u = none, string a = "" ):
    name(n), unit(u), allergen(a){
        if(q < 0){throw invalid_argument("Quantity cannot be negative!");}
        quantity = q;
    }
    string get_name() const{return name;}
    int get_quantity() const{return quantity;}
    string get_unit() const{
        unordered_map<units, string> units_map = {{ml, "ml"},{szt, "szt"},{g, "g"}, {none, "none"}};
        return units_map[unit];
    }
    string get_allergen() const {return allergen;}

    void set_name(string n){name = n;}
    void set_quantity(int q){
        if(q < 0){throw invalid_argument("Quantity cannot be negative!");}
        quantity = q;
    }
    void set_allergen(string a){allergen = a;}

    void operator+=(int quantity_to_add){
        if(quantity + quantity_to_add < 0){throw invalid_argument("Quantity cannot be negative!");}
        quantity += quantity_to_add;
    }

    void operator-=(int quantity_to_sub){
        *this += (-quantity_to_sub);
    }

    void print_product(){
        cout << "Nazwa: " << name << endl;
        cout << "Ilość: " << quantity << " " << unit << endl;
        cout << "Alergen: " << allergen << endl;
        cout << "\n\n";
    }
};