#include <iostream>
#include <unordered_map> //działa szybciej od mapy (nie trzeba sortować)
#include <fstream>
using namespace std;
class Pantry{
    struct product{
        std::string name;
        int quantity;
        product(std::string n = "", int q = 0);

    };
    unordered_map<std::string, product> shell; // unordered_map<product, >
    public:

    void add_product(std::string name, int quantity);
    void change_quantity(std::string name, int quantity);
    void remove_product(std::string name);
    void print_products();

    void print_product(std::string name);

    void write_to_file();
};