#include "Pantry.h"
#include <vector>

using namespace std;


    vector<string> Pantry::get_all_products(){
        vector<string> products;
        for(auto it = shell.begin(); it != shell.end(); it++){
            products.push_back(it->first);
        }
        return products;
    }

    void Pantry::add_quantity(string name, int quantity){
        if (shell.find(name) == shell.end()){throw invalid_argument("Produktu nie ma w spiżarni!");}
        shell[name] += quantity;
    }

    void Pantry::remove_quantity(string name, int quantity){
        add_quantity(name, -quantity);
    }


    void Pantry::add_product(std::string name, int quantity, units unit, string allergen){//żeby patrzyło też czy laergen jest
        if (shell.find(name) == shell.end()){
            shell[name] = Product(name, quantity, unit, allergen);
        }
        else{
            add_quantity(name, quantity);
    }
    }
    void Pantry::add_product(const Product& product){
        add_product(product.get_name(), product.get_quantity(), product.get_enum_unit() , product.get_allergen());
    }

    void Pantry::remove_product(std::string name){
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
    void Pantry::print_products(){
        for(auto it = shell.begin(); it != shell.end(); it++){
            it->second.print_product();
        }
    }

    void Pantry::print_allergens(){
        for(auto it = shell.begin(); it != shell.end(); it++){
            cout << it->first << " ";
            for(auto it2 = it->second.get_allergen().begin(); it2 != it->second.get_allergen().end(); it2++){
                cout << *it2 << " ";
            }
            cout << endl;
        }
    }

    Json::Value Pantry::write_to_file_json(){
        Json::Value root;
        for(auto it = shell.begin(); it != shell.end(); it++){
            root.append(it->second.parse_to_json());
        }
        return root;
    }

    Pantry Pantry::read_from_file_json(Json::Value pan){
        Pantry p;
        for(auto it = pan.begin(); it != pan.end(); it++){
            Product new_product = Product::json_to_product(*it);
            p.add_product(new_product);
        }
        return p;
    }

    /*
    void Pantry::write_to_file_csv(){
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

    void Pantry::read_from_file_csv(){
        ifstream file;
        file.open("pantry_base.csv", ios::in);
        if (file.is_open()){
        string line;
        while(getline(file, line)){
            string name;
            int quantity;
            units unit = ml;
            string allergen;
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
    */
    void Pantry::generate_pretty_raport(){
        return;
    }



