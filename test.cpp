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

TEST(staff, create_staff)
{
    Deliverer d1(1, "name", "last name", Addres(), Money(10000));
    Deliverer d2(2, "name", "last name", Addres(), Money(10000));
    std::vector<Deliverer> deliverers = {d1, d2};
    Staff<Deliverer> staff(deliverers);
    EXPECT_EQ(deliverers.size(), staff.number_employed());
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
    EXPECT_EQ(1, staff.number_employed());
    staff.employ(w2);
    EXPECT_EQ(2, staff.number_employed());
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
    EXPECT_EQ(2, staff.number_employed());
    staff.fire(1);
    EXPECT_EQ(1, staff.number_employed());
}

TEST(staff, fire_out_of_bounds)
{
    Waiter w1(1, "name", "last name", Addres(), Money(10000));
    Waiter w2(2, "name2", "last name", Addres(), Money(10000));
    Staff<Waiter> staff(std::vector<Waiter>{w1, w2});
    EXPECT_EQ(2, staff.number_employed());
    EXPECT_THROW(staff.fire(3), StaffExceptions);
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

TEST(staff, position_new_value)
{
    Waiter w1(1, "name", "last name", Addres(), Money(10000));
    Waiter w2(2, "name2", "last name", Addres(), Money(10000));
    Waiter w3(3, "name3", "last name", Addres(), Money(10000));
    Staff<Waiter> staff(std::vector<Waiter>{w1, w2});
    staff[1] = w3;
    std::vector<Waiter> expected{w1, w3};
    EXPECT_EQ(staff.get_staff(), expected);
    EXPECT_EQ(staff.number_employed(), 2);
}