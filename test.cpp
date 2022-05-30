#include "gtest/gtest.h"
#include "src/employees/Cook.h"
#include "src/employees/Deliverer.h"
#include "src/employees/Manager.h"
#include "src/employees/Waiter.h"
#include "src/employees/Staff.h"

TEST(employee, create_employee)
{
    Employee e(1, "name", "last name", Addres(), Money(10000));

    testing::internal::CaptureStdout();
    e.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 1";
    EXPECT_EQ(output, expected);
}

TEST(employee, create_manager)
{
    Manager m(1, "name", "last name", Addres(), Money(10000));

    testing::internal::CaptureStdout();
    std::cout << m;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 1\nPosition: Manager";
    EXPECT_EQ(output, expected);
}

TEST(employee, create_cook)
{
    Cook c(1, "name", "last name", Addres(), Money(10000), false);

    testing::internal::CaptureStdout();
    std::cout << c;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 1\nPosition: Cook";
    EXPECT_EQ(output, expected);
}

TEST(employee, create_chef)
{
    Cook c(1, "name", "last name", Addres(), Money(10000), true);

    testing::internal::CaptureStdout();
    std::cout << c;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 1\nPosition: Chef";
    EXPECT_EQ(output, expected);
}

TEST(employee, create_deliverer)
{
    Deliverer d(1, "name", "last name", Addres(), Money(10000));

    testing::internal::CaptureStdout();
    std::cout << d;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 1\nPosition: Deliverer";
    EXPECT_EQ(output, expected);
}

TEST(employee, create_waiter)
{
    Waiter w(1, "name", "last name", Addres(), Money(10000));

    testing::internal::CaptureStdout();
    std::cout << w;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 1\nPosition: Waiter";
    EXPECT_EQ(output, expected);
}

TEST(employee, json_employee)
{
    Employee e(1, "name", "last name", Addres(), Money(10000));
    Json::Value employee = e.parse_to_json();
    EXPECT_EQ(employee["name"], "name");
    EXPECT_EQ(employee["surname"], "last name");
    EXPECT_EQ(employee["id"], (unsigned int)1);
    EXPECT_EQ(employee["salary"], (unsigned int)10000);
}

TEST(employee, json_cook)
{
    Cook c(1, "name", "last name", Addres(), Money(10000), false);
    Json::Value employee = c.parse_to_json();
    EXPECT_EQ(employee["name"], "name");
    EXPECT_EQ(employee["surname"], "last name");
    EXPECT_EQ(employee["id"], (unsigned int)1);
    EXPECT_EQ(employee["salary"], (unsigned int)10000);
    EXPECT_EQ(employee["position"], "cook");
    EXPECT_EQ(employee["ischef"], false);
}

TEST(employee, json_chef)
{
    Cook c(1, "name", "last name", Addres(), Money(10000), true);
    Json::Value employee = c.parse_to_json();
    EXPECT_EQ(employee["name"], "name");
    EXPECT_EQ(employee["surname"], "last name");
    EXPECT_EQ(employee["id"], (unsigned int)1);
    EXPECT_EQ(employee["salary"], (unsigned int)10000);
    EXPECT_EQ(employee["position"], "cook");
    EXPECT_EQ(employee["ischef"], true);
}

TEST(employee, json_deliverer)
{
    Deliverer d(1, "name", "last name", Addres(), Money(10000));
    Json::Value employee = d.parse_to_json();
    EXPECT_EQ(employee["name"], "name");
    EXPECT_EQ(employee["surname"], "last name");
    EXPECT_EQ(employee["id"], (unsigned int)1);
    EXPECT_EQ(employee["salary"], (unsigned int)10000);
    EXPECT_EQ(employee["position"], "deliverer");
}

TEST(employee, json_waiter)
{
    Waiter w(1, "name", "last name", Addres(), Money(10000));
    Json::Value employee = w.parse_to_json();
    EXPECT_EQ(employee["name"], "name");
    EXPECT_EQ(employee["surname"], "last name");
    EXPECT_EQ(employee["id"], (unsigned int)1);
    EXPECT_EQ(employee["salary"], (unsigned int)10000);
    EXPECT_EQ(employee["position"], "waiter");
}

TEST(employee, json_manager)
{
    Manager m(1, "name", "last name", Addres(), Money(10000));
    Json::Value employee = m.parse_to_json();
    EXPECT_EQ(employee["name"], "name");
    EXPECT_EQ(employee["surname"], "last name");
    EXPECT_EQ(employee["id"], (unsigned int)1);
    EXPECT_EQ(employee["salary"], (unsigned int)10000);
    EXPECT_EQ(employee["position"], "manager");
}

TEST(employee, create_employee_from_json)
{
    Employee e1(1, "name", "surname", Addres(), Money(10000));
    e1.save_to_json("employee.json");
    Employee e(parse_employee_from_json("employee.json"));
    EXPECT_EQ(e.get_employee_id(), 1);
    EXPECT_EQ(e.get_name(), "name");
    EXPECT_EQ(e.get_salary(), Money(10000));
    EXPECT_EQ(e.get_surname(), "surname");
}

TEST(employee, create_cook_from_json)
{
    Cook c1(1, "name", "surname", Addres(), Money(10000), false);
    c1.save_to_json("cook.json");
    Cook c2(parse_employee_from_json("cook.json"));
    EXPECT_EQ(c2.get_employee_id(), 1);
    EXPECT_EQ(c2.get_name(), "name");
    EXPECT_EQ(c2.get_salary(), Money(10000));
    EXPECT_EQ(c2.get_surname(), "surname");
    EXPECT_EQ(c2.get_ischef(), false);
}

TEST(employee, create_chef_from_json)
{
    Cook c1(1, "name", "surname", Addres(), Money(10000), true);
    c1.save_to_json("chef.json");
    Cook c2(parse_employee_from_json("chef.json"));
    EXPECT_EQ(c2.get_employee_id(), 1);
    EXPECT_EQ(c2.get_name(), "name");
    EXPECT_EQ(c2.get_salary(), Money(10000));
    EXPECT_EQ(c2.get_surname(), "surname");
    EXPECT_EQ(c2.get_ischef(), true);
}

TEST(employee, create_deliverer_from_json)
{
    Deliverer d1(1, "name", "surname", Addres(), Money(10000));
    d1.save_to_json("deliverer.json");
    Deliverer d2(parse_employee_from_json("deliverer.json"));
    EXPECT_EQ(d2.get_employee_id(), 1);
    EXPECT_EQ(d2.get_name(), "name");
    EXPECT_EQ(d2.get_salary(), Money(10000));
    EXPECT_EQ(d2.get_surname(), "surname");
}

TEST(employee, create_manager_from_json)
{
    Manager m1(1, "name", "surname", Addres(), Money(10000));
    m1.save_to_json("manager.json");
    Manager m2(parse_employee_from_json("manager.json"));
    EXPECT_EQ(m2.get_employee_id(), 1);
    EXPECT_EQ(m2.get_name(), "name");
    EXPECT_EQ(m2.get_salary(), Money(10000));
    EXPECT_EQ(m2.get_surname(), "surname");
}

TEST(employee, create_waiter_from_json)
{
    Waiter w1(1, "name", "surname", Addres(), Money(10000));
    w1.save_to_json("waiter.json");
    Waiter w2(parse_employee_from_json("waiter.json"));
    EXPECT_EQ(w2.get_employee_id(), 1);
    EXPECT_EQ(w2.get_name(), "name");
    EXPECT_EQ(w2.get_salary(), Money(10000));
    EXPECT_EQ(w2.get_surname(), "surname");
}

TEST(staff, create_staff)
{
    Deliverer d1(1, "name", "last name", Addres(), Money(10000));
    Deliverer d2(2, "name", "last name", Addres(), Money(10000));
    std::vector<Deliverer> deliverers = {d1, d2};
    Staff<Deliverer> staff(deliverers);
    EXPECT_EQ(deliverers.size(), staff.size());
    EXPECT_EQ(deliverers, staff.get_staff());
}

TEST(staff, print_staff)
{
    Cook c1(1, "name1", "last name", Addres(), Money(10000), false);
    Cook c2(2, "name2", "last name", Addres(), Money(10000), true);
    Staff<Cook> staff(std::vector<Cook>{c1, c2});
    testing::internal::CaptureStdout();
    std::cout << staff;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name1\nSurname: last name\nID: 1\nPosition: Cook\n\nName: name2\nSurname: last name\nID: 2\nPosition: Chef\n";
    EXPECT_EQ(output, expected);
}

TEST(staff, employ)
{
    Waiter w1(1, "name1", "last name", Addres(), Money(10000));
    Waiter w2(2, "name2", "last name", Addres(), Money(10000));
    Staff<Waiter> staff(std::vector<Waiter>{w1});
    EXPECT_EQ(1, staff.size());
    staff.employ(w2);
    EXPECT_EQ(2, staff.size());
}

TEST(staff, employ_already_staff_member)
{
    Manager m1(1, "name", "last name", Addres(), Money(10000));
    Manager m2(2, "name2", "last name", Addres(), Money(10000));
    Staff<Manager> staff(std::vector<Manager>{m1, m2});
    EXPECT_THROW(staff.employ(m1), StaffExceptions);
}

TEST(staff, fire)
{
    Waiter w1(1, "name", "last name", Addres(), Money(10000));
    Waiter w2(2, "name2", "last name", Addres(), Money(10000));
    Staff<Waiter> staff(std::vector<Waiter>{w1, w2});
    EXPECT_EQ(2, staff.size());
    staff.fire(1);
    EXPECT_EQ(1, staff.size());
}

TEST(staff, fire_out_of_bounds)
{
    Waiter w1(1, "name", "last name", Addres(), Money(10000));
    Waiter w2(2, "name2", "last name", Addres(), Money(10000));
    Staff<Waiter> staff(std::vector<Waiter>{w1, w2});
    EXPECT_EQ(2, staff.size());
    EXPECT_THROW(staff.fire(3), StaffExceptions);
}

TEST(staff, fire_negative_index)
{
    Waiter w1(1, "name", "last name", Addres(), Money(10000));
    Waiter w2(2, "name2", "last name", Addres(), Money(10000));
    Staff<Waiter> staff(std::vector<Waiter>{w1, w2});
    EXPECT_THROW(staff.fire(-3), StaffExceptions);
}

TEST(staff, position)
{
    Waiter w1(1, "name", "last name", Addres(), Money(10000));
    Waiter w2(2, "name2", "last name", Addres(), Money(10000));
    Staff<Waiter> staff(std::vector<Waiter>{w1, w2});
    EXPECT_EQ(staff[0], w1);
    EXPECT_EQ(staff[1], w2);
}

TEST(staff, position_out_of_bounds)
{
    Waiter w1(1, "name", "last name", Addres(), Money(10000));
    Waiter w2(2, "name2", "last name", Addres(), Money(10000));
    Staff<Waiter> staff(std::vector<Waiter>{w1, w2});
    EXPECT_THROW(staff[3], StaffExceptions);
}

TEST(staff, position_negative_index)
{
    Waiter w1(1, "name", "last name", Addres(), Money(10000));
    Waiter w2(2, "name2", "last name", Addres(), Money(10000));
    Staff<Waiter> staff(std::vector<Waiter>{w1, w2});
    EXPECT_THROW(staff[-1], StaffExceptions);
}

TEST(staff, position_new_value)
{
    Waiter w1(1, "name", "last name", Addres(), Money(10000));
    Waiter w2(2, "name2", "last name", Addres(), Money(10000));
    Waiter w3(3, "name3", "last name", Addres(), Money(10000));
    Staff<Waiter> staff(std::vector<Waiter>{w1, w2});
    staff[1] = w3;
    std::vector<Waiter> expected{w1, w3};
    EXPECT_EQ(staff.get_staff(), expected);
    EXPECT_EQ(staff.size(), 2);
}

TEST(staff, save_to_json)
{
    Waiter w1(1, "name", "last name", Addres(), Money(10000));
    Waiter w2(2, "name2", "last name", Addres(), Money(10000));
    Waiter w3(3, "name3", "last name", Addres(), Money(10000));
    Staff<Waiter> staff(std::vector<Waiter>{w1, w2, w3});
    save_staff_to_json(staff.parse_to_json(), "waiters.json");
    std::ifstream file;
    file.open("waiters.json");
    EXPECT_EQ(file.is_open(), true); // checks if file exists
    file.close();
}

TEST(staff, create_staff_from_json)
{
    Staff<Waiter> staff(parse_staff_from_json("waiters.json"));
    EXPECT_EQ(staff.size(), 3);
}

TEST(dish, create_dish)
{
    Dish d1("Kaszanka", danie_glowne, Money(600), 0);

    testing::internal::CaptureStdout();
    std::cout << d1;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "Kaszanka\t6,00zł\n";
    EXPECT_EQ(output, expected);
}

TEST(dish, json_dish)
{
    Product p1("cebula", 1, szt);
    Dish d1("Kaszanka", danie_glowne, Money(600), 0, {p1}, {"alergen"});
    
    Json::Value dish = d1.parse_dish_to_json();
    EXPECT_EQ(dish["name"], "Kaszanka");
    EXPECT_EQ(dish["type"], (int)2);
    EXPECT_EQ(dish["price"], (unsigned int)600);
    EXPECT_EQ(dish["is_vegan"], (bool)0);
    std::string allergens = dish["allergens"][0].asString();
    EXPECT_EQ(allergens, "alergen");
    std::string product_name = dish["products"][0]["name"].asString();
    int product_quantity = dish["products"][0]["quantity"].asInt();
    int product_unit = dish["products"][0]["unit"].asInt();
    EXPECT_EQ(dish["products"][0]["name"], product_name);
    EXPECT_EQ(dish["products"][0]["quantity"], product_quantity);
    EXPECT_EQ(dish["products"][0]["unit"], product_unit);
}

