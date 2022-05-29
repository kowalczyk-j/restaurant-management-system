#include "Employee.h"


void Employee::print(std::ostream& os) const
{
    os << "\nName: " << name << "\nSurname: " << surname << "\nID: " << employee_id;
}

Json::Value Employee::parse_to_json()
{
    Json::Value employee;
    employee["name"] = name;
    employee["surname"] = surname;
    employee["id"] = employee_id;
    employee["salary"] = salary.get_in_cents();
    employee["address"] = address.parse_to_json();
    return employee;
}

Json::Value Employee::parse_from_json(std::string path)
{
    std::ifstream file(path);
    Json::Reader reader;
    Json::Value employee;
    reader.parse(file, employee);
    return employee;
}
