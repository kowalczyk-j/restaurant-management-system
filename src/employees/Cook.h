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

    friend std::ostream& operator<<(std::ostream& os, Cook cook)
    {
        cook.print(os);
        os << "\nPosition: ";
        cook.is_chef?(os << "Chef"):(os << "Cook");
        return os;
    }
};
