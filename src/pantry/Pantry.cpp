#include <iomanip>
#include <iostream>
#include <unordered_map> //działa szybciej od mapy (nie trzeba sortować)
#include <fstream>
#include <set>
#include <exception>
#include "Product.h"

using namespace std;
class Pantry{


    unordered_map<std::string, Product> shell; // unordered_map<product, >
    public:

    void add_quantity(string name, int quantity){
        if (shell.find(name) == shell.end()){throw invalid_argument("Produktu nie ma w spiżarni!");}
        shell[name] += quantity;
    }

    void remove_quantity(string name, int quantity){
        add_quantity(name, -quantity);
    }


    void add_product(std::string name, int quantity, units unit, set<string> allergen){//żeby patrzyło też czy laergen jest
        if (shell.find(name) == shell.end()){
            shell[name] = Product(name, quantity, unit, allergen);
        }
        else{
            add_quantity(name, quantity);
    }
    }

    void remove_product(std::string name){
        // tutaj nie wiem, czy nie będziemy potrzebować tego wyjątku (do GUI)
        try{
            shell.at(name);
        }
        catch(const std::out_of_range& oor){
            cout << "Nie ma takiego produktu" << endl;
            return;
        }
        shell.erase(name);

    }
    void print_products(){
        for(auto it = shell.begin(); it != shell.end(); it++){
            it->second.print_product();
        }
    }

    void print_allergens(){
        for(auto it = shell.begin(); it != shell.end(); it++){
            cout << it->first << " ";
            for(auto it2 = it->second.get_allergen().begin(); it2 != it->second.get_allergen().end(); it2++){
                cout << *it2 << " ";
            }
            cout << endl;
        }
    }

    void write_to_file(){
        ofstream file;
        file.open("pantry_base.csv", ios::out);
        if (file.is_open()){
        for(auto it = shell.begin(); it != shell.end(); it++){
            file << it->first << "," << it->second.get_quantity() << "," << it->second.get_unit();
            for(auto it2 = it->second.get_allergen().begin(); it2 != it->second.get_allergen().end(); it2++){
                file <<"," << *it2;
            }
            file << endl;
        }
        }
        file.close();
    }

    void read_from_file_csv(){
        ifstream file;
        file.open("pantry_base.csv", ios::in);
        if (file.is_open()){
        string line;
        while(getline(file, line)){
            string name;
            int quantity;
            units unit = ml;
            set<string> allergen;
            std::string temp_s;
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, temp_s, ',');
            //getline(ss, unit, ',');
            string allergen_string;
            while(getline(ss, allergen_string, ',')){
                allergen.insert(allergen_string);
            }
            quantity = stoi(temp_s);
            add_product(name, quantity, unit, allergen);
        }
        }
        file.close();
    }

    void generate_pretty_raport(){
        return;
    }
};


