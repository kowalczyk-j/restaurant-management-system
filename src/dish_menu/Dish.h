#pragma once
#include <iostream>
#include <map>
#include <set>
#include <json/json.h>
#include "../utils/Money.h"
#include "../pantry/Product.h"

enum dish_type {przystawka, danie_glowne, deser, napoje};

class Dish
{
    unsigned int id;
    std::string name;
    dish_type type;
    Money price;
    bool is_vegan;
    std::map<std::string, Product> ingredients;
    set<std::string> allergens;

public:
    unsigned int get_id() const { return id; }
    std::string get_name() const { return name; }
    dish_type get_dish_type() const { return type; }
    Money get_price() const { return price; }
    bool get_is_vegan() const { return is_vegan; }
    std::map<std::string, Product> get_ingredients() const { return ingredients; }
    set<string> get_allergens() const {return allergens;}

    void set_id(unsigned int i) { id=i; }
    void set_name(std::string n) { name=n; }
    void set_dish_type(dish_type t) { type=t; }
    void set_price(Money p) { price=p; }
    void set_is_vegan(bool veg) { is_vegan=veg; }
    void set_ingredients(std::map<std::string, Product> ingr) { ingredients=ingr; }
    void set_allergens(set<std::string> a) { allergens=a; }

    Dish(int i, std::string n, dish_type t, Money pr,
    bool veg, std::map<std::string, Product> ingr, set<std::string> allerg = {}) : 
    id(i), name(n), type(t), price(pr), is_vegan(veg), ingredients(ingr)
    {
        for (const auto& [key, value] : ingredients)
        {
            if (value.get_allergen() != "")
                allerg.insert(value.get_allergen());
        }
        allergens = allerg;
    }

    void print_ingredients() const
    {
        std::cout << "Lista składników - " << name << ": \n";
        for (const auto& [key, value] : ingredients) {
            std::cout << key << " - " << value.get_quantity() << ' ' << value.get_unit() << "; ";
        std::cout << "\n";
        }
    }
    void print_allergens() const
    {
        std::cout << "Alergeny: ";
        for (auto iter = allergens.begin(); iter != allergens.end(); iter++) {
            if (iter != allergens.begin()) std::cout << ", ";
            std::cout << *iter;
        }
        std::cout << "\n";
    }

    Json::Value parse_to_json(){
        Json::Value dish;
        dish["id"] = id;
        dish["name"] = name;
        dish["type"] = type;
        dish["price"]["zlotys"] = price.get_zlotys();
        dish["price"]["cents"] = price.get_cents();
        dish["is_vegan"] = is_vegan;
        // Json::Value ingr(Json::arrayValue);
        // for(const auto& [key, value] : ingredients){
        //     ingr.append(Json::Value(value.parse_to_json()));
        // }
        // dish["ingredients"] = ingr;
        return dish;
    };

    friend std::ostream& operator<<(std::ostream& os, Dish const& dish)
    {
        return os << dish.name << "\t" << dish.price << "\n";
    }
};