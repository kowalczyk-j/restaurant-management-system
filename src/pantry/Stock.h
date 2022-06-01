#pragma once
#include <iomanip>
#include <iostream>
#include <unordered_map> //działa szybciej od mapy (nie trzeba sortować)
#include <fstream>
#include <json/json.h>
#include <exception>
#include"Product.h"



class Stock: public Product{

    int quantity;

    public:
    Stock(std::string n = "", units u = none, std::string a = "", int q=0): Product(n, u, a){
        if(q < 0){throw std::invalid_argument("Quantity cannot be negative!");}
        quantity = q;
    }

    int get_quantity() const{return quantity;}

    void set_quantity(int q){
        if(q < 0){throw std::invalid_argument("Quantity cannot be negative!");}
        quantity = q;
    }

    void operator+=(int quantity_to_add){
        if(quantity + quantity_to_add < 0){throw std::invalid_argument("Quantity cannot be negative!");}
        quantity += quantity_to_add;
    }

    void operator+=(Ingredient & ing){
        if(quantity + ing.quantity < 0){throw std::invalid_argument("Quantity cannot be negative!");}
        quantity += ing.quantity;
    }

    void operator-=(int quantity_to_sub){
        *this += (-quantity_to_sub);
    }

    void operator-=(Ingredient & ing){
        *this += (-ing.quantity);
    }
};