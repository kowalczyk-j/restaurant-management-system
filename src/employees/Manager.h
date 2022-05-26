#include "Employee.h"

class Manager : public Employee
{
public:
    Manager(std::string fname, std::string lname,
            unsigned int e_id, unsigned int r_id, double sal) :
            Employee(fname, lname, e_id, r_id, sal) {};
    void print(std::ostream& os)
    {
        Employee::print(os);
        os << "\nPosition: Manager";
    }
};
