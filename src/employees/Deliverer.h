#include "Employee.h"

class Deliverer : public Employee
{
private:
    double tips;
public:
    Deliverer(std::string fname, std::string lname,
              unsigned int e_id, unsigned int r_id, Money sal) :
              Employee(fname, lname, e_id, r_id, sal) {};

    void print(std::ostream& os)
    {
        Employee::print(os);
        os << "\nPosition: Deliverer";
    }
};
