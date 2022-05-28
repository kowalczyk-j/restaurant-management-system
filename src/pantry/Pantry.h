#pragma once
#include<vector>
#include "Product.h"

using namespace std;
class Pantry{


    unordered_map<std::string, Product> shell; // unordered_map<product, >
    public:

    vector<string> get_all_products();
    void add_quantity(string name, int quantity);
    void remove_quantity(string name, int quantity);

    void add_product(std::string name, int quantity, units unit, string allergen);

    void remove_product(std::string name);
    void print_products();
    void print_allergens();

    void write_to_file();

    void read_from_file_csv();


    void generate_pretty_raport();
};


