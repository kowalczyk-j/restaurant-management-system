#include "gtest/gtest.h"
#include "src/employees/Cook.h"
#include "src/employees/Deliverer.h"
#include "src/employees/Manager.h"
#include "src/employees/Waiter.h"
#include "src/employees/Staff.h"

TEST(employee, create_employee)
{
    Employee e("name", "last name", 1, 1, Money(10000));

    testing::internal::CaptureStdout();
    e.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 1/1";
    EXPECT_EQ(output, expected);
}

TEST(employee, create_manager)
{
    Manager m("name", "last name", 1, 1, Money(10000));

    testing::internal::CaptureStdout();
    std::cout << m;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 1/1\nPosition: Manager";
    EXPECT_EQ(output, expected);
}

TEST(employee, create_cook)
{
    Cook c("name", "last name", 1, 1, Money(10000), false);

    testing::internal::CaptureStdout();
    std::cout << c;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 1/1\nPosition: Cook";
    EXPECT_EQ(output, expected);
}

TEST(employee, create_chef)
{
    Cook c("name", "last name", 1, 1, Money(10000), true);

    testing::internal::CaptureStdout();
    std::cout << c;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 1/1\nPosition: Chef";
    EXPECT_EQ(output, expected);
}

TEST(employee, create_deliverer)
{
    Deliverer d("name", "last name", 1, 1, Money(10000));

    testing::internal::CaptureStdout();
    std::cout << d;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 1/1\nPosition: Deliverer";
    EXPECT_EQ(output, expected);
}

TEST(employee, create_waiter)
{
    Waiter w("name", "last name", 1, 1, Money(10000), std::vector<unsigned int>{1, 2});

    testing::internal::CaptureStdout();
    std::cout << w;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 1/1\nPosition: Waiter";
    EXPECT_EQ(output, expected);
}

TEST(staff, create_staff)
{
    Deliverer d1("name1", "surname", 1, 1, Money(10000));
    Deliverer d2("name2", "surname", 2, 1, Money(15000));
    std::vector<Deliverer> deliverers = {d1, d2};
    Staff<Deliverer> staff(deliverers);
    EXPECT_EQ(deliverers.size(), staff.number_employed());
    EXPECT_EQ(deliverers, staff.get_staff());
}


TEST(staff, print_staff)
{
    Cook c1("name1", "surname", 1, 1, Money(10000), false);
    Cook c2("name2", "surname", 2, 1, Money(15000), true);
    Staff<Cook> staff(std::vector<Cook>{c1, c2});
    testing::internal::CaptureStdout();
    std::cout << staff;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name1\nSurname: surname\nID: 1/1\nPosition: Cook\n\nName: name2\nSurname: surname\nID: 2/1\nPosition: Chef\n";
    EXPECT_EQ(output, expected);
}

TEST(staff, employ)
{
    Waiter w1("name", "surname", 1, 1, Money(10000), std::vector<unsigned int>{1, 2});
    Waiter w2("name2", "last name", 2, 1, Money(10000), std::vector<unsigned int>{3, 4});
    Staff<Waiter> staff(std::vector<Waiter>{w1});
    EXPECT_EQ(1, staff.number_employed());
    staff.employ(w2);
    EXPECT_EQ(2, staff.number_employed());
}

TEST(staff, employ_already_staff_member)
{
    Waiter w1("name", "surname", 1, 1, Money(10000), std::vector<unsigned int>{1, 2});
    Waiter w2("name2", "last name", 2, 1, Money(10000), std::vector<unsigned int>{3, 4});
    Staff<Waiter> staff(std::vector<Waiter>{w1, w2});
    EXPECT_THROW(staff.employ(w1), StaffExceptions);
}

TEST(staff, fire)
{
    Waiter w1("name", "surname", 1, 1, Money(10000), std::vector<unsigned int>{1, 2});
    Waiter w2("name2", "last name", 2, 1, Money(10000), std::vector<unsigned int>{3, 4});
    Staff<Waiter> staff(std::vector<Waiter>{w1, w2});
    EXPECT_EQ(2, staff.number_employed());
    staff.fire(w2);
    EXPECT_EQ(1, staff.number_employed());
}

TEST(staff, fire_person_not_found)
{
    Waiter w1("name", "surname", 1, 1, Money(10000), std::vector<unsigned int>{1, 2});
    Waiter w2("name2", "last name", 2, 1, Money(10000), std::vector<unsigned int>{3, 4});
    Staff<Waiter> staff(std::vector<Waiter>{w1});
    EXPECT_THROW(staff.fire(w2), StaffExceptions);
}
