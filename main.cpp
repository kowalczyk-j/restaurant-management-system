#include "src/restaurant/RestaurantNet.h"
#include <json/json.h>
#include <fstream>

using namespace std;

int main(){
    Product p = Product("Jabłko",670, g);
    Product p1 = Product("Mięso",500, g);
    Product p2 = Product("Sok Jabłkowy",1000, ml);
    Product p3 = Product("jajka",60, szt);
    Product p4  = Product("koperek",100, g);
    Product p5 = Product("ziemniaki",4000, g);
    cout << p.get_name()<< " " << p.get_quantity() << " " << p.get_unit() << endl;


    Pantry pan;
    string s;
    pan.add_product("Jabłko", 6, g,  s);
    pan.add_product("Mięso",500, g, s);
    pan.add_product("Sok Jabłkowy",1000, ml, s);

    Addres a1 = Addres( "Warszawa", "00-000", "Plac Politechniki", "1", "Polska", "Mazowieckie", 52.220154, 21.011968);
    Addres a2 = Addres( "Warszawa", "00-000", "Plac Politechniki", "1", "Polska", "Mazowieckie", 52.216184, 20.239073);
    std::map<std::string, Product> map = {{"jablko", p}};
    Dish d1 = Dish(1, "zupa pomidorowa", przystawka, Money(500), 1, map);
    std::vector<Dish> dishes;
    dishes.push_back(d1);
    Menu m = Menu(dishes);
    Cook c = Cook(1, "Adam", "Wiśniewski", a1, Money(800000), 1);
    /*std::vector<Cook> vc;
    std::vector<Manager> vm;
    std::vector<Deliverer> vd;
    std::vector<Waiter> vw;
    vc.push_back(c);


    DeliveryOrder * os = new DeliveryOrder(1, dishes, a1, 10);
    std::vector<DeliveryOrder*> vde;
    vde.push_back(os);
    Restaurant r1 =  Restaurant(1, "Magnoliowa", a1, pan, m, vc, vd, vm, vw, vde);
    Restaurant r2 =  Restaurant(2, "Różana", a2, pan, m, vc, vd, vm, vw, vde);*/

    std::ofstream file;
    Json::Value op = c.parse_to_json();
    file.open("file.json");


    Json::StyledWriter styledWriter;
    file << styledWriter.write(op);

    file.close();

    return 0;
}