#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <json/json.h>
#include "../utils/Money.h"
#include "../pantry/Product.h"

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
    void add_ingiridnet(Product ingr){ingredients.push_back(ingr);}
    void remove_ingridient(int position){ingredients.erase(ingredients.begin() + position);}
    void set_allergens(set<std::string> a) { allergens=a; }

    Dish(std::string n, dish_type t, Money pr,
    bool veg, std::vector<Product> ingr= {}, set<std::string> allerg = {}) :
    name(n), type(t), price(pr), is_vegan(veg), ingredients(ingr)
    {
        for (const auto& value : ingredients)
        {
            if (value.get_allergen() != "")
                allerg.insert(value.get_allergen());
        }
        allergens = allerg;
    }

    void print_ingredients() const
    {
        std::cout << "Lista składników - " << name << ": \n";
        for (const auto& value : ingredients) {
            std::cout << value.get_name() << " - " << value.get_quantity() << ' ' << value.get_unit() << "; ";
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

    Json::Value parse_dish_to_json(){
        Json::Value dish;
        Json::Value products (Json::arrayValue);
        dish["name"] = name;
        dish["type"] = type;
        dish["price"] = price.get_in_cents();
        dish["is_vegan"] = is_vegan;
        //dish["allergens"] = allergens;
        for(const auto& value : ingredients){
            products.append(value.parse_to_json());
        }
        dish["products"]=products;
        return dish;
    }

    static Dish parse_dish_from_json(Json::Value dish){
        std::vector<Product> ingr;
        for(auto it = dish["products"].begin(); it != dish["products"].end(); it++){
            ingr.push_back(Product::json_to_product(*it));
        }
        return Dish(dish["name"].asString(), (dish_type) dish["type"].asInt(), Money(dish["price"].asInt()), dish["is_vegan"].asBool(), ingr);
    }

    friend std::ostream& operator<<(std::ostream& os, Dish const& dish)
    {
        return os << dish.name << "\t" << dish.price << "\n";
    }
};