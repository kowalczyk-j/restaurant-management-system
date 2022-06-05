#pragma once
#include "Employee.h"
#include <vector>

class Waiter : public Employee
{
private:
    double tips;
    std::vector<int> orders_to_serve;
public:
    Waiter(std::string fname, std::string lname, Addres a, Money sal) :
           Employee(fname, lname, a, sal) {
               position_name = "Kelner";
           };
    Waiter(Json::Value waiter_from_json) : Employee(waiter_from_json) {};

    void new_tip(double tip) {tips += tip;}
/*
    Json::Value parse_to_json()
    {
        Json::Value waiter = Employee::parse_to_json();
        waiter["position"] = "waiter";
        return waiter;
    }*/

    void print(std::ostream& os) const
    {
        this->Employee::print(os);
        os << "\nPosition: Waiter";
    }
};
