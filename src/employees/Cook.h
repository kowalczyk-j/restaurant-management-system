#pragma once
#include "Employee.h"

class Cook : public Employee
{
private:
    bool is_chef;
public:
    Cook(std::string fname, std::string lname, Addres a, Money sal, bool chef) :
         Employee(fname, lname,  a, sal), is_chef(chef) {
             position_name = "Kucharz";
         };
    Cook(Json::Value cook_from_json) : Employee(cook_from_json), is_chef(cook_from_json["ischef"].asBool()) {};
    ~Cook(){};

    bool get_ischef() {return is_chef;}
    void set_chef() {is_chef = true;}
    void remove_chef(){is_chef = false;}

    /*
    Json::Value parse_to_json()
    {
        Json::Value cook = Employee::parse_to_json();
        cook["position"] = "cook";
        cook["ischef"] = is_chef;
        return cook;
    }*/

    void print(std::ostream& os) const
    {
        this->Employee::print(os);
        os << "\nPosition: ";
        is_chef?(os << "Chef"):(os << "Cook");
    }
};
