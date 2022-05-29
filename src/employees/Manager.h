#pragma once
#include "Employee.h"

class Manager : public Employee
{
public:
    Manager(unsigned int e_id, std::string fname, std::string lname,  Addres a, Money sal) :
            Employee(e_id, fname, lname, a, sal) {};
    Manager(Json::Value manager_from_json) : Employee(manager_from_json) {};

    Json::Value parse_to_json()
    {
        Json::Value manager = Employee::parse_to_json();
        manager["position"] = "manager";
        return manager;
    }

    friend std::ostream& operator<<(std::ostream& os, Manager manager)
    {
        manager.print(os);
        os << "\nPosition: Manager";
        return os;
    }
};
