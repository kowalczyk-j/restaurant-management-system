#include <json/json.h>
#include <fstream>
#include "src/restaurant/Restaurant.h"

using namespace std;

int main(){
    Database<Employee> employee_databse;
    Manager * man = new Manager("ded", "eeff", Addres(), Money());
    Deliverer * del = new Deliverer("sew", "ewfewf", Addres(), Money());
    employee_databse.add_data(man);
    employee_databse.add_data(del);
    Employee * man2 = employee_databse[1001];
    man2->set_name("Karol");
    for(Employee * employee:employee_databse.get_full_data()){employee->print(std::cout);}

    Restaurant r1(0, "Rożana", Addres());
    Addres a = Addres();
    Money m = Money();
    std::string name = "Kajetan";
    r1.add_manager(name, "Rożej", a, m);
    name = "JAKUB";
    for(Employee * employee:r1.get_all_employees()){employee->print(std::cout);}

    Ingredient i1(1001, 100), i2(1002, 200);
    Database<Product> pantry;
    Product * p1 = new Product("produkt1", ml, "mleko", 3000);
    Product * p2 = new Product("produkt2", szt, "jaja", 30);
    pantry.add_data(p1);
    pantry.add_data(p2);
    Dish * d1 = new Dish(1001, "kotlet1", danie_glowne, Money(15,50), 0,{i1, i2},{"siarka"}, &pantry);
    Dish * d2 = new Dish(1002, "przystawka", przystawka, Money(15,50), 0,{i1, i2},{"siarka"}, &pantry);
    Dish * d3 = new Dish(1003, "zupa", zupa, Money(15,50), 0,{i1, i2},{"siarka"}, &pantry);
   Dish * d4 = new Dish(1004, "deser", deser, Money(15,50), 0,{i1, i2},{"siarka"}, &pantry);
    Database<Dish> menu;
    menu.add_data(d1);
    menu.add_data(d2);
    menu.add_data(d3);
    menu.add_data(d4);
    cout << endl << d1->get_string_allergens();
    for(Product * product:pantry.get_full_data()){product->print_product();}
    Json::Value json = d1->parse_to_json();
    std::ofstream file;
    file.open("file.json");
    Json::StyledWriter styledWriter;
    file << styledWriter.write(json);
    file.close();

    std::ifstream ofile("file.json");
    Json::Reader reader;
    Json::Value dish;
    reader.parse(ofile, dish);
    cout << Dish::parse_from_json(dish);
    Dish::parse_from_json(dish)->print_ingredients();
    pantry[1001]->print_product();
    r1.generate_lunch_menu();
}