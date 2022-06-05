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
    EXPECT_EQ(employee["position"], "cook");
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
    EXPECT_EQ(employee["position"], "cook");
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
    EXPECT_EQ(employee["position"], "deliverer");
}

TEST(employee, json_waiter)
{
    Waiter w("name", "last name", Addres(), Money(10000));
    Json::Value employee = w.parse_to_json();
    EXPECT_EQ(employee["name"], "name");
    EXPECT_EQ(employee["surname"], "last name");
    EXPECT_EQ(employee["id"], (unsigned int)0);
    EXPECT_EQ(employee["salary"], (unsigned int)10000);
    EXPECT_EQ(employee["position"], "waiter");
}

TEST(employee, json_manager)
{
    Manager m("name", "last name", Addres(), Money(10000));
    Json::Value employee = m.parse_to_json();
    EXPECT_EQ(employee["name"], "name");
    EXPECT_EQ(employee["surname"], "last name");
    EXPECT_EQ(employee["id"], (unsigned int)0);
    EXPECT_EQ(employee["salary"], (unsigned int)10000);
    EXPECT_EQ(employee["position"], "manager");
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

//-----------------------------PRODUCT/PANTRY testing


TEST(product, create_empty_product)
{
    Product p;
    EXPECT_EQ(p.get_name(), "");
    EXPECT_EQ(p.get_quantity(), 0);
    EXPECT_EQ(p.get_enum_unit(), none);
    EXPECT_EQ(p.get_allergen(), "");
}


TEST(product, create_product)
{
    Product p("name", 10, ml, "allergen");
    EXPECT_EQ(p.get_name(), "name");
    EXPECT_EQ(p.get_quantity(), 10);
    EXPECT_EQ(p.get_enum_unit(), ml);
    EXPECT_EQ(p.get_allergen(), "allergen");
}


TEST(product, test_setters)
{
    Product p("name", 10, ml, "allergen");
    p.set_name("new name");
    p.set_quantity(20);
    p.set_allergen("new allergen");
    EXPECT_EQ(p.get_name(), "new name");
    EXPECT_EQ(p.get_quantity(), 20);
    EXPECT_EQ(p.get_allergen(), "new allergen");
}

TEST(product, quantity_operators)
{
    Product p("name", 10, ml, "allergen");
    p += 10;
    EXPECT_EQ(p.get_quantity(), 20);
    p -= 10;
    EXPECT_EQ(p.get_quantity(), 10);
    p -= 10;
    EXPECT_EQ(p.get_quantity(), 0);

}

TEST(product, throw_exception_while_adding_negative_quantity)
{
    // this tests _that_ the expected exception is thrown
    EXPECT_THROW({
        try
        {
            Product p("name", 10, ml, "allergen");
            p += -20;
            }
        catch( const invalid_argument& e )
        {
            // and this tests that it has the correct message
            EXPECT_STREQ( "Quantity cannot be negative!", e.what() );
            throw;
        }
    }, invalid_argument);
}

TEST(pantry, create_empty_pantry)
{
    Pantry p;
    EXPECT_EQ(p.get_all_products().size(), 0);
}

TEST(pantry, add_product)
{
    Pantry p;
    Product p1("name", 10, ml, "allergen");
    p.add_product(p1);
    EXPECT_EQ(p.get_all_products().size(), 1);
}

TEST(pantry, add_quantity)
{
    Pantry p;
    Product p1("name", 10, ml, "allergen");
    p.add_product(p1);
    p.add_quantity("name", 10);
    EXPECT_EQ(p.get_all_products().size(), 1);
    EXPECT_EQ(p.get_product("name").get_quantity(), 20);
}

TEST(pantry, remove_quantity)
{
    Pantry p;
    Product p1("name", 10, ml, "allergen");
    p.add_product(p1);
    p.remove_quantity("name", 10);
    EXPECT_EQ(p.get_all_products().size(), 1);
    EXPECT_EQ(p.get_product("name").get_quantity(), 0);
}

TEST(pantry, add_product_object)
{
    Pantry p;
    Product p1("name", 10, ml, "allergen");
    p.add_product(p1);
    EXPECT_EQ(p.get_all_products().size(), 1);
}

TEST(pantry, add_product_manually)
{
    Pantry p;
    p.add_product("name", 10, ml, "allergen");
    EXPECT_EQ(p.get_all_products().size(), 1);

}

TEST(pantry, remove_product_by_name)
{
    Pantry p;
    Product p1("name", 10, ml, "allergen");
    p.add_product(p1);
    p.remove_product("name");
    EXPECT_EQ(p.get_all_products().size(), 0);
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

TEST(dish, add_ingredient)
{
    Product p1("cebula", 1, szt);
    Dish d1("Kaszanka", danie_glowne, Money(600), 0, {p1}, {"alergen"});
    Product p2("sos", 30, ml);
    d1.add_ingiridnet(p2);
    EXPECT_EQ(d1.get_ingredients().size(), 2);
    EXPECT_EQ(d1.get_ingredients()[0].get_name(), p1.get_name());
    EXPECT_EQ(d1.get_ingredients()[1].get_name(), p2.get_name());
}

TEST(dish, remove_ingredient)
{
    Product p1("cebula", 1, szt);
    Product p2("sos", 30, ml);
    Dish d1("Kaszanka", danie_glowne, Money(600), 0, {p1, p2}, {"alergen"});
    d1.remove_ingridient(2);
    EXPECT_EQ(d1.get_ingredients().size(), 1);
    EXPECT_EQ(d1.get_ingredients()[0].get_name(), p1.get_name());
}

TEST(dish, remove_ingredient_errors)
{
    Product p1("cebula", 1, szt);
    Product p2("sos", 30, ml);
    Dish d1("Kaszanka", danie_glowne, Money(600), 0, {p1, p2}, {"alergen"});
    EXPECT_THROW(d1.remove_ingridient(3), dish_exceptions);
    EXPECT_THROW(d1.remove_ingridient(-1), dish_exceptions);
}

TEST(dish, print_alergens)
{
    Product p1("cebula", 1, szt, "alergen1");
    Product p2("sos", 30, ml, "alergen2");
    Dish d1("Kaszanka", danie_glowne, Money(600), 0, {p1, p2}, {"alergen", "alergen1"});

    testing::internal::CaptureStdout();
    d1.print_allergens();
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "Alergeny: alergen, alergen1, alergen2\n";
    EXPECT_EQ(output, expected);
}

TEST(dish, print_ingredients)
{
    Product p1("cebula", 1, szt, "alergen1");
    Product p2("sos", 30, ml, "alergen2");
    Dish d1("Kaszanka", danie_glowne, Money(600), 0, {p1, p2}, {"alergen", "alergen1"});

    testing::internal::CaptureStdout();
    d1.print_ingredients();
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "Lista składników - Kaszanka: \ncebula - 1 szt; \nsos - 30 ml; \n";
    EXPECT_EQ(output, expected);
}

