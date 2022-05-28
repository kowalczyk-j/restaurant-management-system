#pragma once
#include <iostream>
#include "../utils/Money.h"

class Employee
{
protected:
    std::string name;
    std::string surname;
    unsigned int employee_id;
    unsigned int restaurant_id; // jesli sieciówka
    Money salary;
public:
    Employee(std::string fname, std::string lname,
             unsigned int e_id, unsigned int r_id, Money sal) :
             name(fname), surname(lname), employee_id(e_id),
             restaurant_id(r_id), salary(sal) {};

    std::string get_name() {return name;}
    std::string get_surname() {return surname;}
    unsigned int get_employee_id() {return employee_id;}

    void set_name(std::string name) {this->name = name;}
    void set_surname(std::string surname) {this->surname = surname;}
    void set_employee_id(unsigned int id) {employee_id = id;}
    void give_raise(Money new_sal) {salary = new_sal;}

    virtual void print(std::ostream& os) const
    {
        os << "\nName: " << name << "\nSurname: " << surname << "\nID: " << employee_id << "/" << restaurant_id;
    }

    bool operator==(Employee other) const
    {
        return (employee_id == other.employee_id && restaurant_id == other.restaurant_id);
    }
};
