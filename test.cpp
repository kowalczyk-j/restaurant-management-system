#include "gtest/gtest.h"
#include "src/employees/Cook.h"
#include "src/employees/Deliverer.h"
#include "src/employees/Manager.h"
#include "src/employees/Waiter.h"
#include "src/pantry/Product.h"
#include "src/dish_menu/Dish.h"

TEST(employee, create_manager)
{
    Manager m("name", "last name", Addres(), Money(10000));

    testing::internal::CaptureStdout();
    std::cout << m;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 0\nPosition: Manager";
    EXPECT_EQ(output, expected);
}

TEST(employee, create_cook)
{
    Cook c("name", "last name", Addres(), Money(10000), false);

    testing::internal::CaptureStdout();
    std::cout << c;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 0\nPosition: Cook";
    EXPECT_EQ(output, expected);
}

TEST(employee, create_chef)
{
    Cook c("name", "last name", Addres(), Money(10000), true);

    testing::internal::CaptureStdout();
    std::cout << c;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 0\nPosition: Chef";
    EXPECT_EQ(output, expected);
}

TEST(employee, create_deliverer)
{
    Deliverer d("name", "last name", Addres(), Money(10000));

    testing::internal::CaptureStdout();
    std::cout << d;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 0\nPosition: Deliverer";
    EXPECT_EQ(output, expected);
}

TEST(employee, create_waiter)
{
    Waiter w("name", "last name", Addres(), Money(10000));

    testing::internal::CaptureStdout();
    std::cout << w;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "\nName: name\nSurname: last name\nID: 0\nPosition: Waiter";
    EXPECT_EQ(output, expected);
}

TEST(employee, json_cook)
{
    Cook c("name", "last name", Addres(), Money(10000), false);
    Json::Value employee = c.parse_to_json();
    EXPECT_EQ(employee["name"], "name");
    EXPECT_EQ(employee["surname"], "last name");
    EXPECT_EQ(employee["id"], (unsigned int)0);
    EXPECT_EQ(employee["salary"], (unsigned int)10000);
    EXPECT_EQ(employee["position"], "Kucharz");
    EXPECT_EQ(employee["ischef"], false);
}

TEST(employee, json_chef)
{
    Cook c("name", "last name", Addres(), Money(10000), true);
    Json::Value employee = c.parse_to_json();
    EXPECT_EQ(employee["name"], "name");
    EXPECT_EQ(employee["surname"], "last name");
    EXPECT_EQ(employee["id"], (unsigned int)0);
    EXPECT_EQ(employee["salary"], (unsigned int)10000);
    EXPECT_EQ(employee["position"], "Kucharz");
    EXPECT_EQ(employee["ischef"], true);
}

TEST(employee, json_deliverer)
{
    Deliverer d("name", "last name", Addres(), Money(10000));
    Json::Value employee = d.parse_to_json();
    EXPECT_EQ(employee["name"], "name");
    EXPECT_EQ(employee["surname"], "last name");
    EXPECT_EQ(employee["id"], (unsigned int)0);
    EXPECT_EQ(employee["salary"], (unsigned int)10000);
    EXPECT_EQ(employee["position"], "Dostawca");
}

TEST(employee, json_waiter)
{
    Waiter w("name", "last name", Addres(), Money(10000));
    Json::Value employee = w.parse_to_json();
    EXPECT_EQ(employee["name"], "name");
    EXPECT_EQ(employee["surname"], "last name");
    EXPECT_EQ(employee["id"], (unsigned int)0);
    EXPECT_EQ(employee["salary"], (unsigned int)10000);
    EXPECT_EQ(employee["position"], "Kelner");
}

TEST(employee, json_manager)
{
    Manager m("name", "last name", Addres(), Money(10000));
    Json::Value employee = m.parse_to_json();
    EXPECT_EQ(employee["name"], "name");
    EXPECT_EQ(employee["surname"], "last name");
    EXPECT_EQ(employee["id"], (unsigned int)0);
    EXPECT_EQ(employee["salary"], (unsigned int)10000);
    EXPECT_EQ(employee["position"], "Manager");
}

TEST(employee, create_cook_from_json)
{
    Cook c1("name", "surname", Addres(), Money(10000), false);
    c1.save_to_json("cook.json");
    Cook c2(parse_employee_from_json("cook.json"));
    EXPECT_EQ(c2.get_id(), 0);
    EXPECT_EQ(c2.get_name(), "name");
    EXPECT_EQ(c2.get_salary(), Money(10000));
    EXPECT_EQ(c2.get_surname(), "surname");
    EXPECT_EQ(c2.get_ischef(), false);
}

TEST(employee, create_chef_from_json)
{
    Cook c1("name", "surname", Addres(), Money(10000), true);
    c1.save_to_json("chef.json");
    Cook c2(parse_employee_from_json("chef.json"));
    EXPECT_EQ(c2.get_id(), 0);
    EXPECT_EQ(c2.get_name(), "name");
    EXPECT_EQ(c2.get_salary(), Money(10000));
    EXPECT_EQ(c2.get_surname(), "surname");
    EXPECT_EQ(c2.get_ischef(), true);
}

TEST(employee, create_deliverer_from_json)
{
    Deliverer d1("name", "surname", Addres(), Money(10000));
    d1.save_to_json("deliverer.json");
    Deliverer d2(parse_employee_from_json("deliverer.json"));
    EXPECT_EQ(d2.get_id(), 0);
    EXPECT_EQ(d2.get_name(), "name");
    EXPECT_EQ(d2.get_salary(), Money(10000));
    EXPECT_EQ(d2.get_surname(), "surname");
}

TEST(employee, create_manager_from_json)
{
    Manager m1("name", "surname", Addres(), Money(10000));
    m1.save_to_json("manager.json");
    Manager m2(parse_employee_from_json("manager.json"));
    EXPECT_EQ(m2.get_id(), 0);
    EXPECT_EQ(m2.get_name(), "name");
    EXPECT_EQ(m2.get_salary(), Money(10000));
    EXPECT_EQ(m2.get_surname(), "surname");
}

TEST(employee, create_waiter_from_json)
{
    Waiter w1("name", "surname", Addres(), Money(10000));
    w1.save_to_json("waiter.json");
    Waiter w2(parse_employee_from_json("waiter.json"));
    EXPECT_EQ(w2.get_id(), 0);
    EXPECT_EQ(w2.get_name(), "name");
    EXPECT_EQ(w2.get_salary(), Money(10000));
    EXPECT_EQ(w2.get_surname(), "surname");
}

// //-----------------------------PRODUCT/PANTRY testing


TEST(product, create_empty_product)
{
    Product p;
    EXPECT_EQ(p.get_name(), "");
    EXPECT_EQ(p.get_quantity(), 0);
    EXPECT_EQ(p.get_enum_unit(), none);
    EXPECT_EQ(p.get_allergen(), "");
    EXPECT_EQ(p.get_available_quantity(), 0);
}


TEST(product, create_product)
{
    Product p("name", ml, "allergen", 10 );
    EXPECT_EQ(p.get_name(), "name");
    EXPECT_EQ(p.get_quantity(), 10);
    EXPECT_EQ(p.get_enum_unit(), ml);
    EXPECT_EQ(p.get_allergen(), "allergen");
    EXPECT_EQ(p.get_available_quantity(), 10);
}


TEST(product, test_setters)
{
    Product p("name", ml, "allergen", 10 );
    p.set_name("new name");
    p.set_id(10);
    p.set_allergen("new allergen");
    EXPECT_EQ(p.get_name(), "new name");
    EXPECT_EQ(p.get_quantity(), 10);
    EXPECT_EQ(p.get_id(), 10);
}

TEST(product, quantity_operators)
{
    Product p("name", ml, "allergen", 10 );
    p += 10;
    EXPECT_EQ(p.get_quantity(), 20);
    p -= 10;
    EXPECT_EQ(p.get_quantity(), 10);
    p -= 10;
    EXPECT_EQ(p.get_quantity(), 0);

}
TEST(product, json_product)
{
    Product p("name", ml, "allergen", 10 );
    Json::Value product = p.parse_to_json();
    EXPECT_EQ(product["name"], "name");
    EXPECT_EQ(product["quantity"], 10);
    EXPECT_EQ(product["unit"], p.get_enum_unit());
    EXPECT_EQ(product["allergen"], "allergen");
    EXPECT_EQ(product["available_quantity"], 10);
}

TEST(product, reserve_product)
{
    Product p("name", ml, "allergen", 10 );
    p.reserve(5);
    EXPECT_EQ(p.get_available_quantity(), 5);
    p.reserve(5);
    EXPECT_EQ(p.get_available_quantity(), 0);
}

TEST(product, release_product)
{
    Product p("name", ml, "allergen", 10 );
    p.reserve(5);
    EXPECT_EQ(p.get_available_quantity(), 5);
    p.release(5);
    EXPECT_EQ(p.get_available_quantity(), 10);

}

TEST(product, use_product)
{
    Product p("name", ml, "allergen", 10 );
    p.reserve(5);
    EXPECT_EQ(p.get_available_quantity(), 5);
    p.use_product(5);
    EXPECT_EQ(p.get_quantity(), 5);
}

// //-----------------------------DISH testing

TEST(dish, create_dish)
{
    Dish d1(1, "Kaszanka", danie_glowne, Money(600), 0);

    testing::internal::CaptureStdout();
    std::cout << &d1;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "Kaszanka\t6,00zł\n";
    EXPECT_EQ(output, expected);
}

TEST(dish, json_dish)
{
    Ingredient p1(1, 2);
    Dish d1(1, "Kaszanka", danie_glowne, Money(600), 0, {p1}, {"alergen"});

    Json::Value dish = d1.parse_to_json();
    EXPECT_EQ(dish["id"], (unsigned int)1);
    EXPECT_EQ(dish["name"], "Kaszanka");
    EXPECT_EQ(dish["type"], (int)2);
    EXPECT_EQ(dish["price"], (unsigned int)600);
    EXPECT_EQ(dish["is_vegan"], (bool)0);
    EXPECT_EQ(dish["products"][0]["stock_id"], (unsigned int)1);
    EXPECT_EQ(dish["products"][0]["quantity"], (int)2);
}

TEST(dish, add_ingredient)
{
    Ingredient p1(1, 2);
    Ingredient p2(2, 200);
    Dish d1(1, "Kaszanka", danie_glowne, Money(600), 0, {p1}, {"alergen"});
    d1.add_ingredient(p2);
    EXPECT_EQ(d1.get_ingredients().size(), 2);
    EXPECT_EQ(d1.get_ingredients()[0].stock_id, p1.stock_id);
    EXPECT_EQ(d1.get_ingredients()[0].quantity, p1.quantity);
    EXPECT_EQ(d1.get_ingredients()[1].stock_id, p2.stock_id);
    EXPECT_EQ(d1.get_ingredients()[1].quantity, p2.quantity);
}

TEST(dish, remove_ingredient)
{
    Ingredient p1(1, 2);
    Ingredient p2(2, 200);
    Dish d1(1, "Kaszanka", danie_glowne, Money(600), 0, {p1, p2}, {"alergen"});
    d1.remove_ingredient(1);
    EXPECT_EQ(d1.get_ingredients().size(), 1);
    EXPECT_EQ(d1.get_ingredients()[0].stock_id, p1.stock_id);
    EXPECT_EQ(d1.get_ingredients()[0].quantity, p1.quantity);
    d1.remove_ingredient(0);
    EXPECT_EQ(d1.get_ingredients().size(), 0);
}

TEST(dish, remove_ingredient_errors)
{
    Ingredient p1(1, 2);
    Ingredient p2(2, 200);
    Dish d1(1, "Kaszanka", danie_glowne, Money(600), 0, {p1, p2}, {"alergen"});
    EXPECT_THROW(d1.remove_ingredient(2), dish_exceptions);
    EXPECT_THROW(d1.remove_ingredient(-1), dish_exceptions);
}

TEST(dish, print_alergens)
{
    Ingredient p1(1, 2);
    Ingredient p2(2, 200);
    Dish d1(1, "Kaszanka", danie_glowne, Money(600), 0, {p1, p2}, {"alergen1, alergen2"});

    testing::internal::CaptureStdout();
    d1.print_allergens();
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "Alergeny: alergen1, alergen2\n";
    EXPECT_EQ(output, expected);
}

TEST(dish, print_ingredients)
{
    Ingredient p1(1, 2);
    Ingredient p2(2, 200);
    Dish d1(1, "Kaszanka", danie_glowne, Money(600), 0, {p1, p2}, {"alergen1, alergen2"});

    testing::internal::CaptureStdout();
    d1.print_ingredients();
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "Lista składników - Kaszanka: \nId składniku: 1 Ilość: 2; \nId składniku: 2 Ilość: 200; \n";
    EXPECT_EQ(output, expected);
}

