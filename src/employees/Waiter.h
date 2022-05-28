#pragma once
#include "Employee.h"
#include <vector>

class Waiter : public Employee
{
private:
    double tips;
    std::vector<int> orders_to_serve;
public:
    Waiter( unsigned int e_id, std::string fname, std::string lname, Addres a, Money sal) :
           Employee(e_id, fname, lname, a, sal) {};

    void new_tip(double tip) {tips += tip;}

    Json::Value parse_to_json()
    {
        Json::Value waiter = Employee::parse_to_json();
        waiter["position"] = "waiter";
        return waiter;
    }

    friend std::ostream& operator<<(std::ostream& os, Waiter waiter)
    {
        waiter.print(os);
        os << "\nPosition: Waiter";
        return os;
    }
};
