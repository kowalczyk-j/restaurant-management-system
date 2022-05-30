#include "Dish.h"

Dish::Dish(std::string n, dish_type t, Money pr,
bool veg, std::vector<Product> ingr, set<std::string> allerg) :
name(n), type(t), price(pr), is_vegan(veg), ingredients(ingr)
{
    for (const auto& value : ingredients)
    {
        if (value.get_allergen() != "")
            allerg.insert(value.get_allergen());
    }
    allergens = allerg;
}

void Dish::print_ingredients() const
{
     std::cout << "Lista składników - " << name << ": \n";
     for (const auto& value : ingredients) {
         std::cout << value.get_name() << " - " << value.get_quantity() << ' ' << value.get_unit() << "; ";
     std::cout << "\n";
     }
}

void Dish::print_allergens() const
{
    std::cout << "Alergeny: ";
    for (auto iter = allergens.begin(); iter != allergens.end(); iter++) {
        if (iter != allergens.begin()) std::cout << ", ";
        std::cout << *iter;
    }
    std::cout << "\n";
}

Json::Value Dish::parse_dish_to_json(){
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

Dish Dish::parse_dish_from_json(Json::Value dish)
{
    std::vector<Product> ingr;
    for(auto it = dish["products"].begin(); it != dish["products"].end(); it++){
        ingr.push_back(Product::json_to_product(*it));
    }
    return Dish(dish["name"].asString(), (dish_type) dish["type"].asInt(), Money(dish["price"].asUInt()), dish["is_vegan"].asBool(), ingr);
}
