#pragma once
#include "Employee.h"

class Deliverer : public Employee
{
private:
    double tips;
public:
    Deliverer(std::string fname, std::string lname,
              unsigned int e_id, unsigned int r_id, Money sal) :
              Employee(fname, lname, e_id, r_id, sal) {};

    void new_tip(double tip) {tips += tip;}

    friend std::ostream& operator<<(std::ostream& os, Deliverer deli)
    {
        deli.print(os);
        os << "\nPosition: Deliverer";
        return os;
    }
};
