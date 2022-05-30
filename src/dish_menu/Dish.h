#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <json/json.h>
#include "../utils/Money.h"
#include "../pantry/Product.h"

enum dish_exceptions {NegativeIndex, IndexOutOfBounds};

enum dish_type {zupa, przystawka, danie_glowne, deser, napoje};

class Dish
{
    std::string name;
    dish_type type;
    Money price;
    bool is_vegan;
    std::vector<Product> ingredients;
    set<std::string> allergens;

public:
    Dish(std::string n, dish_type t, Money pr,
    bool veg, std::vector<Product> ingr={}, set<std::string> allerg={});

    std::string get_name() const { return name; }
    std::string get_dish_type(){
        unordered_map<dish_type, string> dish_type_map = {{zupa, "Zupa"},{przystawka, "Przystawka"},{danie_glowne, "Danie Główne"}, {deser, "Deser"},{napoje, "Napoje"}};
        return dish_type_map[type];
    }
    dish_type get_enum_dish_type() const { return type;}
    Money get_price() const { return price; }
    bool get_is_vegan() const { return is_vegan; }
    std::vector<Product> & get_ingredients() {return ingredients; }
    set<string> get_allergens() const {return allergens;}

    void set_name(std::string n) { name=n; }
    void set_dish_type(dish_type t) { type=t; }
    void set_price(Money p) { price=p; }
    void set_is_vegan(bool veg) { is_vegan=veg; }
    void set_ingredients(std::vector <Product> ingr) {ingredients=ingr;}
    void set_allergens(set<std::string> a) { allergens=a; }

    void add_ingiridnet(Product ingr){ingredients.push_back(ingr);}
    void remove_ingridient(int position);

    void print_ingredients() const;
    void print_allergens() const;

    Json::Value parse_dish_to_json();
    static Dish parse_dish_from_json(Json::Value dish);

    friend std::ostream& operator<<(std::ostream& os, Dish const& dish){return os << dish.name << "\t" << dish.price << "\n";}
};