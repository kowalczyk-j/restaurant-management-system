#pragma once
#include<vector>
#include "Product.h"

using namespace std;
class Pantry{

    unordered_map<std::string, Product> shell;

    public:
    Pantry(){};
    vector<string> get_all_products();
    Product & get_product(std::string name){return shell[name];}
    void add_quantity(string name, int quantity);
    void remove_quantity(string name, int quantity);

    void add_product(std::string name, int quantity, units unit, string allergen);
    void add_product(const Product& product);

    void remove_product(std::string name);
    void print_products();
    void print_allergens();

    Json::Value write_to_file_json();
    static Pantry read_from_file_json(Json::Value pan);

    void write_to_file_csv();
    void read_from_file_csv();


    void generate_pretty_raport();
};


