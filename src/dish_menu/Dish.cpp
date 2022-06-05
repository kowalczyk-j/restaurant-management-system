#include "Dish.h"

Dish::Dish(unsigned int id, std::string n, dish_type t, Money pr,
bool veg, std::vector<Ingredient> ingr, set<std::string> allergs,
Database<Product> *products) :
dish_id(id), name(n), type(t), price(pr), is_vegan(veg), ingredients(ingr)
{
    if(products != nullptr){
        for (size_t i=0; i< ingr.size(); i++){
            auto allerg = products->operator[](ingr[i].stock_id)->get_allergen();
            if (allerg != "")
                allergs.insert(allerg);
        }
    }
    allergens = allergs;
}

std::string Dish::get_string_allergens() const
{
    std::string outcome = "";
    for (const auto& allergen : allergens)
    {
        outcome = outcome + allergen + '\n';
    }
    return outcome;
}

void Dish::print_ingredients() const
{
     std::cout << "Lista składników - " << name << ": \n";
     for (const auto& value : ingredients) {
         std::cout << "Id składniku: " << value.stock_id << " Ilość: " << value.quantity << "; ";
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


Json::Value Dish::parse_to_json(){
    Json::Value dish;
    Json::Value products (Json::arrayValue);
    Json::Value allergs (Json::arrayValue);
    dish["id"] = dish_id;
    dish["name"] = name;
    dish["type"] = type;
    dish["price"] = price.get_in_cents();
    dish["is_vegan"] = is_vegan;
    for(const auto& value : allergens){
        allergs.append(value);
    }
    for(const auto& value : ingredients){
        Json::Value ingredient;
        ingredient["stock_id"] = value.stock_id;
        ingredient["quantity"] = value.quantity;
        products.append(ingredient);
    }
    dish["allergens"] = allergs;
    dish["products"]=products;
    return dish;
}

Dish Dish::parse_from_json(Json::Value dish)
{
    std::vector<Ingredient> ingr;
    std::set<string> allerg;
    for(auto it = dish["products"].begin(); it != dish["products"].end(); it++){
        auto obj = *it;
        ingr.push_back(Ingredient(obj["stock_id"].asUInt(), obj["quantity"].asInt()));
    }
    for(auto it = dish["allergens"].begin(); it != dish["allergens"].end(); it++){
        allerg.insert(it->asString());
    }
    return Dish(dish["id"].asUInt(), dish["name"].asString(), (dish_type) dish["type"].asInt(), Money(dish["price"].asInt()), dish["is_vegan"].asBool(), ingr, allerg);
}