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
    std::string position_name;
    Addres address;
    Money salary;

public:
    //konstruktor klasy z parametrami
    Employee(std::string fname="", std::string lname="", Addres a = Addres(), Money sal = Money()) :
             name(fname), surname(lname), address(a), salary(sal){
                 employee_id=0;
             };
    Employee(Json::Value employee_from_json);

    //destruktor (wymagany ze względu na abstrakcyjnosć klasy)
    virtual ~Employee(){};

    //gettery
    std::string const& get_name() const {return name;}
    std::string const& get_surname() const {return surname;}
    unsigned int get_id() const {return employee_id;}
    Money const& get_salary() const {return salary;}
    Addres const& get_address() const {return address;}
    std::string const& get_position() const {return position_name;}

    //settery
    void set_name(std::string name) {this->name = name;}
    void set_surname(std::string surname) {this->surname = surname;}
    void set_id(unsigned int id) {employee_id = id;}
    void set_salary(Money new_sal) {salary = new_sal;}
    void set_address(Addres new_address) {address = new_address;}

    //konwertery do formatu JSON
    virtual Json::Value parse_to_json();

    bool operator==(Employee * other) const {return (employee_id == other->employee_id);}

    virtual void print(std::ostream& os) const = 0;

};


