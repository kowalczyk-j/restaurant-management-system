#include <iostream>

class Employee
{
protected:
    std::string name;
    std::string surname;
    unsigned int employee_id;
    unsigned int restaurant_id; // jesli sieciówka
    double salary;
public:
    Employee(std::string fname, std::string lname,
             unsigned int e_id, unsigned int r_id, double sal) :
             name(fname), surname(lname), employee_id(e_id),
             restaurant_id(r_id), salary(sal) {};
    void give_raise(unsigned int new_sal)
    {
        salary = new_sal;
    }
    virtual void print(std::ostream& os) const // pozniej zdefiniuje na bazie tego operator<<
    {
        os << "\nName: " << name << "\nSurname: " << surname << "\nID: " << employee_id << "/" << restaurant_id;
    }
};
