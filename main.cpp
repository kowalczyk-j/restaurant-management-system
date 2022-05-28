#include "src/restaurant/RestaurantNet.h"
#include <json/json.h>
#include <fstream>

using namespace std;

int main(){
    Product p = Product("jablko",670, g);
    Product p1 = Product("mieso",500, g);
    Product p2 = Product("sok jablkowy",1000, ml);
    Product p3 = Product("jajka",60, szt, {"jaja"});
    Product p4  = Product("koperek",100, g);
    Product p5 = Product("orzechy ziemne",4000, g, {"orzechy"});
    Product p6 = Product("orzechy nerkowca",3000, g, {"orzechy"});
    cout << p.get_name()<< " " << p.get_quantity() << " " << p.get_unit() << endl;


    Pantry pan;
    set<string> s;
    pan.add_product("jablko", 6, g, "");

    Addres a = Addres("Polska", "Mazowieckie", "Warszawa", "00-000", "Pl. Politechniki", "1", 53, 20);
    map<string, Product> map = {{"jablko", p}, {"jajka", p3}, {"orzechy ziemne", p5}, {"orzechy nerkowca", p6}};
    Dish d1 = Dish(1, "jajka z orzechami", przystawka, Money(500), 0, map, {"jaja"});
    Dish d2 = Dish(2, "szarlotka", deser, Money(600), 1, map);
    std::vector<Dish> dishes;
    dishes.push_back(d1);
    Menu m = Menu(dishes);
    m.add_dish(d2);
    Cook c = Cook("Jan", "Kowalski", 1, 5, Money(800000), 0);
    vector<Employee> ve;
    ve.push_back(c);


    DeliveryOrder oso =  DeliveryOrder(1, dishes, a, 10);
    vector<DeliveryOrder*> vd;
    //vd.push_back(os);
    Json::Value v = m.parse_menu_to_json();
    std::ofstream file;
    file.open("file.json");


    Json::StyledWriter styledWriter;
    file << styledWriter.write(v);

    file.close();

    //Restaurant r1 = Restaurant(1, "Magnoliowa", a, pan, m, ve, vd);
    //Restaurant r2 = Restaurant(2, "Różana", a, pan, m, ve, vd);

    // vector<Restaurant> vr;
    // vr.push_back(r1);
    // vr.push_back(r2);

    // RestaurantNet rn = RestaurantNet(vr);

    d1.print_ingredients();
    d1.print_allergens();
    return 0;
}