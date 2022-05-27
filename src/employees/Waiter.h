#pragma once
#include "Employee.h"
#include <vector>

class Waiter : public Employee
{
private:
    double tips;
    std::vector<unsigned int> tables_to_wait;
public:
    Waiter(std::string fname, std::string lname,
           unsigned int e_id, unsigned int r_id,
           Money sal, std::vector<unsigned int> tables) :
           Employee(fname, lname, e_id, r_id, sal), tables_to_wait(tables) {};

    friend std::ostream& operator<<(std::ostream& os, Waiter waiter)
    {
        waiter.print(os);
        os << "\nPosition: Waiter";
        return os;
    }
};
