#pragma once
#include "Employee.h"
#include <vector>

class Waiter : public Employee
{
private:
    double tips;
    std::vector<unsigned int> tables_to_wait; // each waiter has a specified list of tables (numbered) they wait
public:
    Waiter(std::string fname, std::string lname,
           unsigned int e_id, unsigned int r_id,
           Money sal, std::vector<unsigned int> tables) :
           Employee(fname, lname, e_id, r_id, sal), tables_to_wait(tables) {};

    void new_tip(double tip) {tips += tip;}
    void set_tables_to_wait(std::vector<unsigned int> tables) {tables_to_wait = tables;}

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
