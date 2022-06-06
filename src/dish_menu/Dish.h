#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <json/json.h>
#include "../utils/Money.h"
#include "../pantry/Product.h"
#include "../Database.h"

enum dish_exceptions {NegativeIndex, IndexOutOfBounds};

enum dish_type {zupa, przystawka, danie_glowne, deser, napoje};

struct Ingredient{
    unsigned int stock_id;
    int quantity;

    Ingredient(unsigned int s_id, int q):stock_id(s_id), quantity(q){};
};

class Dish
{
    unsigned int dish_id;
    std::string name;
    dish_type type;
    Money price;
    bool is_vegan;
    std::vector<Ingredient> ingredients;
    std::set<std::string> allergens;

public:
    Dish(unsigned int id=1, std::string n="", dish_type t=danie_glowne, Money pr= Money(),
    bool veg=0, std::vector<Ingredient> ingr={}, std::set<std::string> allerg={},
    Database<Product> * products=nullptr);

    unsigned int get_id() const {return dish_id;}
    std::string const& get_name() const { return name; }
    std::string const& get_dish_type() const {
        std::unordered_map<dish_type, std::string> dish_type_map = {{zupa, "Zupa"},{przystawka, "Przystawka"},{danie_glowne, "Danie Główne"}, {deser, "Deser"},{napoje, "Napoje"}};
        return dish_type_map[type];
    }
    dish_type const& get_enum_dish_type() const { return type;}
    Money const& get_price() const { return price; }
    bool get_is_vegan() const { return is_vegan; }
    std::vector<Ingredient> const& get_ingredients() const {return ingredients; }
    std::string get_string_allergens() const;

    void set_id(unsigned int id){dish_id=id;}
    void set_name(std::string n) { name=n; }
    void set_dish_type(dish_type t) { type=t; }
    void set_price(Money p) { price=p; }
    void set_is_vegan(bool veg) { is_vegan=veg; }
    void set_ingredients(std::vector<Ingredient> ingr) {ingredients=ingr;}

    void add_ingredient(Ingredient ingr){ingredients.push_back(ingr);}
    void remove_ingredient(int position){
        if(position < 0) throw NegativeIndex;
        if(position >= (int)ingredients.size()) throw IndexOutOfBounds;
        ingredients.erase(ingredients.begin() + position);
    }

    void print_ingredients() const;
    void print_allergens() const;

    Json::Value parse_to_json();
    static Dish * parse_from_json(Json::Value dish);

    friend std::ostream& operator<<(std::ostream& os, Dish * dish){return os << dish->name << "\t" << dish->price << "\n";}
};