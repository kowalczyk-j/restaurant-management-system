#pragma once
#include <vector>
#include "Employee.h"

class Deliverer : public Employee
{
private:
    Money tips;
    std::vector<int> orders_to_serve;

public:
    Deliverer(unsigned int e_id, std::string fname, std::string lname, Addres a, Money sal) :
              Employee(e_id, fname, lname, a, sal) {};
    Deliverer(Json::Value deliverer_from_json) : Employee(deliverer_from_json) {};

    void new_tip(Money tip) {tips += tip;}

    Json::Value parse_to_json()
    {
        Json::Value deliverer = Employee::parse_to_json();
        deliverer["position"] = "deliverer";
        return deliverer;
    }

    friend std::ostream& operator<<(std::ostream& os, Deliverer deli)
    {
        deli.print(os);
        os << "\nPosition: Deliverer";
        return os;
    }
};
