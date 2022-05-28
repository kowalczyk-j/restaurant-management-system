#include "Employee.h"

void Employee::print(std::ostream& os) const
{
    os << "\nName: " << name << "\nSurname: " << surname << "\nID: " << employee_id << "/" << restaurant_id;
}

void Employee::parse_to_json(std::string path)
{
    Json::Value employee;
    employee["name"] = name;
    employee["surname"] = surname;
    employee["id"] = employee_id;
    employee["restaurant id"] = restaurant_id;
    employee["salary"] = salary.to_string();
    std::ofstream file;
    file.open(path);
    Json::StyledWriter writer;
    file << writer.write(employee);

    file.close();
}

Json::Value Employee::parse_from_json(std::string path)
{
    std::ifstream file(path);
    Json::Reader reader;
    Json::Value employee;
    reader.parse(file, employee);
    return employee;
}