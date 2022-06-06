#include "Employee.h"

Employee::Employee(Json::Value employee_from_json)
{
    employee_id = employee_from_json["id"].asUInt();
    name = employee_from_json["name"].asString();
    surname = employee_from_json["surname"].asString();
    std::string country = employee_from_json["address"]["country"].asString();
    std::string region = employee_from_json["address"]["region"].asString();
    std::string city = employee_from_json["address"]["city"].asString();
    std::string post = employee_from_json["address"]["postal_code"].asString();
    std::string street = employee_from_json["address"]["street"].asString();
    std::string building = employee_from_json["address"]["building"].asString();
    double latitude = employee_from_json["address"]["coordinates"]["latitude"].asDouble();
    double longitude = employee_from_json["address"]["coordinates"]["longitude"].asDouble();
    address = Addres(city, post, street, building, country, region, latitude, longitude);
    salary = Money(employee_from_json["salary"].asUInt());
}

void Employee::print(std::ostream& os) const
{
    os << "\nName: " << name << "\nSurname: " << surname << "\nID: " << employee_id;
}

Json::Value Employee::parse_to_json()
{
    Json::Value employee;
    employee["name"] = name;
    employee["surname"] = surname;
    employee["salary"] = salary.get_in_cents();
    employee["address"] = address.parse_to_json();
    employee["position"] = position_name;
    employee["id"] = employee_id;
    return employee;
}

void Employee::save_to_json(std::string path)
{
    std::ofstream file;
    file.open(path);
    Json::StyledWriter writer;
    file << writer.write(this->parse_to_json());
    file.close();
}

Json::Value parse_employee_from_json(std::string path)
{
    std::ifstream file(path);
    Json::Reader reader;
    Json::Value employee;
    reader.parse(file, employee);
    return employee;
}
