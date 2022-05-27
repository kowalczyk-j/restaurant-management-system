
#include <iomanip>
#include <iostream>
#include <unordered_map> //działa szybciej od mapy (nie trzeba sortować)
#include <fstream>
#include <set>
using namespace std;
class Pantry{
    struct product{
        std::string name;
        int quantity;
        std::string unit;
        set<string> allergen;
        public:
        product(std::string n = "", int q = 0, std::string u = "", set<string> a = {} ){
            if(q < 0){
                q = 0;
            }
            if(u != "ml" && u != "gram" && u != "szt" && u != ""){
                cout << "Nieprawidłowa jednostka(ml/gram/szt)" << endl;
                return;
            }
            name = n;
            quantity = q;
            unit = u;//jednostka miary(ml, gram, szt) -> enum, nie czaje co z tym enumem
            allergen = a;
        }

        std::string get_name(){
            return name;
        }
        int get_quantity(){
            return quantity;
        }
        std::string get_unit(){
            return unit;
        }
        set<string> get_allergen(){
            return allergen;
        }

        void set_name(std::string n){
            name = n;
        }
        void set_quantity(int q){
            if(q < 0){
                q = 0;
            }
            quantity = q;
        }
        void set_unit(std::string u){
            if(u != "ml" && u != "gram" && u != "szt"){
                cout << "Nieprawidłowa jednostka(ml/gram/szt)" << endl;
                return;
            }
            unit = u;
        }
        void set_allergen(set<string> a){
            allergen = a;
        }

        void print_product(){
            cout << "Nazwa: " << name << endl;
            cout << "Ilość: " << quantity << " " << unit << endl;
            cout << "Alergeny: ";
            for(auto i : allergen){ //jak pozbyć się przecinka na koniec ?
                cout << i << ", ";
            }
            cout << "\n\n";
        }

    };

    unordered_map<std::string, product> shell; // unordered_map<product, >
    public:

    void add_product(std::string name, int quantity, std::string unit, set<string> allergen){//żeby patrzyło też czy laergen jest
        if (shell.find(name) == shell.end()){
            shell[name] = product(name, quantity, unit, allergen);
        }
        else{
            if (shell[name].quantity + quantity < 0){
                shell[name].quantity = 0;
            }
            else{
                shell[name].quantity += quantity;
            }
    }
    }
    void remove_quantity(std::string name, int quantity, std::string unit, set<string> allergen){
        add_product(name, -quantity, unit, allergen);
    }

    void remove_product(std::string name){
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
            for(auto it2 = it->second.allergen.begin(); it2 != it->second.allergen.end(); it2++){
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
            file << it->first << "," << it->second.quantity << "," << it->second.unit;
            for(auto it2 = it->second.allergen.begin(); it2 != it->second.allergen.end(); it2++){
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
            string unit;
            set<string> allergen;
            std::string temp_s;
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, temp_s, ',');
            getline(ss, unit, ',');
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


