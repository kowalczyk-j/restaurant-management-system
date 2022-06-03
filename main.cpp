//#include "src/restaurant/RestaurantNet.h"
#include "src/Database.h"
#include <json/json.h>
#include <fstream>
#include "src/pantry/Product.h"
#include "src/employees/Employee.h"
#include "src/employees/Manager.h"
#include "src/employees/Deliverer.h"
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


}