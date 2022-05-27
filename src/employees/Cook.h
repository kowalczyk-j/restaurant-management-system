#include "Employee.h"

class Cook : public Employee
{
private:
    bool is_chef;
public:
    Cook(std::string fname, std::string lname,
         unsigned int e_id, unsigned int r_id, Money sal, bool chef) :
         Employee(fname, lname, e_id, r_id, sal), is_chef(chef) {};

    void print(std::ostream& os)
    {
        Employee::print(os);
        os << "\nPosition: Cook";
    }
};
