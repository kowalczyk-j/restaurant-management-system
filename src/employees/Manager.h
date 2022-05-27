#pragma once
#include "Employee.h"

class Manager : public Employee
{
public:
    Manager(std::string fname, std::string lname,
            unsigned int e_id, unsigned int r_id, Money sal) :
            Employee(fname, lname, e_id, r_id, sal) {};
    friend std::ostream& operator<<(std::ostream& os, Manager manager)
    {
        manager.print(os);
        os << "\nPosition: Manager";
        return os;
    }
};
