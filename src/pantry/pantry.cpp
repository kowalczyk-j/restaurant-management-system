#include <iostream>
#include <unordered_map> //działa szybciej od mapy (nie trzeba sortować)
#include <fstream>
using namespace std;
class Pantry{
    struct product{
        std::string name;
        int quantity;
        product(std::string n = "", int q = 0){ //pusty konstruktor, int -> unsigned int, nei może byc ujemne quantity
            name = n;
            quantity = q;
            //jednostka miary(ml, gram, szt) -> enum
            //alergeny, set stringów, siarczany i inne

        }

    };
    unordered_map<std::string, product> shell; // unordered_map<product, >
    public:

    void add_product(std::string name, int quantity){//można użyć do odejmowania qiantity
        if (shell.find(name) == shell.end()){
            shell[name] = product(name, quantity);
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
    void change_quantity(std::string name, int quantity){
        add_product(name, -quantity);
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
            cout << it->first << " " << it->second.quantity << " " << endl;
        }
    }

    void print_product(std::string name){
        cout <<"name :" << shell[name].name << "\n" << "quantity :" << shell[name].quantity << endl;
    }


    void write_to_file(){ // zrobic łądnie w tabelce
        ofstream file;
        file.open("pantry_base.txt"); //csv lepiej
        for(auto it = shell.begin(); it != shell.end(); it++){
            file << it->first << " " << it->second.quantity << endl;
        }
        file.close();
    }
};
//generuj raport
int main(){
    Pantry p;
    p.add_product("mleko", 10);
    p.add_product("jajka", 20);
    p.add_product("kakao", 10);
    p.add_product("mleko", 10);
    p.add_product("dżem", 10);
    p.print_products();
    p.add_product("dżem", -20);
    p.print_products();
    p.write_to_file();

    return 0;
}
