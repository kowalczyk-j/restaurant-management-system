#pragma once
#include "Employee.h"

class Cook : public Employee
{
private:
    bool is_chef;
public:
    Cook(std::string fname, std::string lname,
         unsigned int e_id, unsigned int r_id, Money sal, bool chef) :
         Employee(fname, lname, e_id, r_id, sal), is_chef(chef) {};

    void set_chef() {is_chef = true;}

    Json::Value parse_to_json()
    {
        Json::Value cook = Employee::parse_to_json();
        cook["position"] = is_chef?"chef":"cook";
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
