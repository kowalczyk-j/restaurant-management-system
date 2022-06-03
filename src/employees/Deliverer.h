#pragma once
#include <vector>
#include "Employee.h"

class Deliverer : public Employee
{
private:
    Money tips;
    std::vector<int> orders_to_serve;

public:
    Deliverer(std::string fname, std::string lname, Addres a, Money sal) :
              Employee(fname, lname, a, sal) {
                  position_name = "Dostawca";
              };
    Deliverer(Json::Value deliverer_from_json) : Employee(deliverer_from_json) {};
    ~Deliverer(){};

    void new_tip(Money tip) {tips += tip;}
/*
    Json::Value parse_to_json()
    {
        Json::Value deliverer = Employee::parse_to_json();
        deliverer["position"] = "deliverer";
        return deliverer;
    }*/

    virtual void print(std::ostream& os) const
    {
        this->Employee::print(os);
        os << "\nPosition: Deliverer";
    }
};
