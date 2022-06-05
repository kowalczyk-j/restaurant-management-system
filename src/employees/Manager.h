#pragma once
#include "Employee.h"

class Manager : public Employee
{
public:
    Manager(std::string fname, std::string lname,  Addres a, Money sal) :
            Employee(fname, lname, a, sal) {
                position_name = "Manager";
            };
    Manager(Json::Value manager_from_json) : Employee(manager_from_json) {};
/*
    Json::Value parse_to_json()
    {
        Json::Value manager = Employee::parse_to_json();
        manager["position"] = "manager";
        return manager;
    }*/

    void print(std::ostream& os) const
    {
        this->Employee::print(os);
        os << "\nPosition: Manager";
    }
};
