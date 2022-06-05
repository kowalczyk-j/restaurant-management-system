#pragma once
#include "Employee.h"

class Waiter : public Employee
{
private:
    Money tips;

public:
    Waiter(std::string fname, std::string lname, Addres a, Money sal) :
           Employee(fname, lname, a, sal) {
               position_name = "Kelner";
           };
    Waiter(Json::Value waiter_from_json) : Employee(waiter_from_json) {};

    void new_tip(Money tip) {tips += tip;}

    Json::Value parse_to_json()
    {
        Json::Value waiter = Employee::parse_to_json();
        waiter["tips"] = tips.get_in_cents();
        return waiter;
    }

    void print(std::ostream& os) const
    {
        this->Employee::print(os);
        os << "\nPosition: Waiter";
    }

    friend std::ostream& operator<<(std::ostream& os, Waiter const& w)
    {
        w.print(os);
        return os;
    }
};
