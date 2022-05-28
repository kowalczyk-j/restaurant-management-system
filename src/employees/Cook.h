#pragma once
#include "Employee.h"

class Cook : public Employee
{
private:
    bool is_chef;
public:
    Cook(unsigned int e_id, std::string fname, std::string lname, Addres a, Money sal, bool chef) :
         Employee(e_id, fname, lname,  a, sal), is_chef(chef) {};

    void set_chef() {is_chef = true;}
    void remove_chef(){is_chef = false;}

    Json::Value parse_to_json()
    {
        Json::Value cook = Employee::parse_to_json();
        cook["position"] = "cook";
        cook["ischef"] = is_chef;
        return cook;
    }

    friend std::ostream& operator<<(std::ostream& os, Cook cook)
    {
        cook.print(os);
        os << "\nPosition: ";
        cook.is_chef?(os << "Chef"):(os << "Cook");
        return os;
    }
};
