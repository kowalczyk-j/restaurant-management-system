#pragma once
#include <fstream>
#include <iostream>
#include <json/json.h>
#include "../utils/Money.h"
#include "../utils/Address.h"

class Employee
{
protected:
    unsigned int employee_id;
    std::string name;
    std::string surname;
    Addres address;
    Money salary;

public:
    //konstruktor klasy z parametrami
    Employee(unsigned int e_id=0, std::string fname="", std::string lname="", Addres a = Addres(), Money sal = Money()) :
             employee_id(e_id),name(fname), surname(lname), address(a), salary(sal){};
    Employee(Json::Value employee_from_json);

    //gettery
    std::string const& get_name() const {return name;}
    std::string const& get_surname() const {return surname;}
    unsigned int get_employee_id() const {return employee_id;}
    Money const& get_salary() const {return salary;}
    Addres const& get_address() const {return address;}

    //settery
    void set_name(std::string name) {this->name = name;}
    void set_surname(std::string surname) {this->surname = surname;}
    void set_employee_id(unsigned int id) {employee_id = id;}
    void set_salary(Money new_sal) {salary = new_sal;}
    void set_address(Addres new_address) {address = new_address;}

    //konwertery do formatu JSON
    virtual Json::Value parse_to_json();
    void save_to_json(std::string path);

    bool operator==(Employee other) const {return (employee_id == other.employee_id);}

    virtual void print(std::ostream& os) const;
};

Json::Value parse_employee_from_json(std::string path);
