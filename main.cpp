#include "src/restaurant/Restaurant.h"
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

    Pantry pan;
    string s;
    pan.add_product("Jabłko", 6, g,  s);
    pan.add_product("Mięso",500, g, s);
    pan.add_product("Sok Jabłkowy",1000, ml, s);

    Addres a1 = Addres( "Warszawa", "00-000", "Plac Politechniki", "1", "Polska", "Mazowieckie", 52.220154, 21.011968);
    Addres a2 = Addres( "Warszawa", "00-000", "Plac Politechniki", "1", "Polska", "Mazowieckie", 52.216184, 20.239073);
    std::vector< Product> map = {p};
    Dish d1 = Dish("zupa pomidorowa", przystawka, Money(500), true, map);
    std::vector<Dish> dishes;
    dishes.push_back(d1);
    Menu m = Menu(dishes);
    Cook c = Cook(1, "Adam", "Wiśniewski", a1, Money(800000), 0);
    Waiter w = Waiter(2, "Alicja", "Polska", a1, Money(800000));
    Deliverer d = Deliverer(3, "Tomasz", "Niewierny", a1, Money(800000));
    Manager man = Manager(4, "Jan", "Nowak", a1, Money(800000));
    std::vector<Cook> vc;
    std::vector<Manager> vm;
    std::vector<Deliverer> vd;
    std::vector<Waiter> vw;
    vc.push_back(c);
    vw.push_back(w);
    vm.push_back(man);
    vd.push_back(d);


    DeliveryOrder os = DeliveryOrder(1, dishes, a1, 10);
    std::vector<DeliveryOrder> vde;
    std::vector<OnSiteOrder> vso;
    vde.push_back(os);
    Restaurant r1 =  Restaurant(1, "Magnoliowa", a1, pan, m, vc, vd, vm, vw, vde, vso);
    Restaurant r2 =  Restaurant(2, "Różana", a2, pan, m, vc, vd, vm, vw, vde, vso);

    std::cout<<r1.get_cooks()[0] << std::endl;
    std::cout<<r1.get_managers()[0] << std::endl;
    std::cout << r1.get_menu();
    return 0;
}