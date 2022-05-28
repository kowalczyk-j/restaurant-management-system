#include "src/restaurant/RestaurantNet.h"
#include <json/json.h>
#include <fstream>

using namespace std;

int main(){
    Product p = Product("jablko",670, g);
    Product p1 = Product("mieso",500, g);
    Product p2 = Product("sok jablkowy",1000, ml);
    Product p3 = Product("jajka",60, szt);
    Product p4  = Product("koperek",100, g);
    Product p5 = Product("ziemniaki",4000, g);
    cout << p.get_name()<< " " << p.get_quantity() << " " << p.get_unit() << endl;


    Pantry pan;
    set<string> s;
    pan.add_product("jablko", 6, g,  s);

    Addres a = Addres("Polska", "Mazowieckie", "Warszawa", "00-000", "Pl. Politechniki", "1", 53, 20);
    std::map<std::string, Product> map = {{"jablko", p}};
    Dish d1 = Dish(1, "zupa pomidorowa", przystawka, Money(500), 1, map);
    std::vector<Dish> dishes;
    dishes.push_back(d1);
    Menu m = Menu(dishes);
    Cook c = Cook("Jan", "Kowalski", 1, 5, Money(800000), 0);
    vector<Employee> ve;
    ve.push_back(c);


    DeliveryOrder oso =  DeliveryOrder(1, dishes, a, 10);
    vector<DeliveryOrder*> vd;
    //vd.push_back(os);
    Json::Value v = oso.parse_to_JSON();
    std::ofstream file;
    file.open("file.json");


    Json::StyledWriter styledWriter;
    file << styledWriter.write(v);

    file.close();

    Restaurant r1 = Restaurant(1, "Magnoliowa", a, pan, m, ve, vd);
    Restaurant r2 = Restaurant(2, "Różana", a, pan, m, ve, vd);

    vector<Restaurant> vr;
    vr.push_back(r1);
    vr.push_back(r2);

    RestaurantNet rn = RestaurantNet(vr);

    return 0;
}