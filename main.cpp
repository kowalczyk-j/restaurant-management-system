#include "src/restaurant/Restaurant.h"

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

    Addres a = Addres("Polska", "Mazowieckie", "Warszawa", "00-000", "Pl. Politechniki", "1");
    std::map<std::string, Product> map = {{"jablko", p}};
    Dish d1 = Dish(1, "zupa pomidorowa", przystawka, Money(500), 1, map);
    std::vector<Dish> dishes;
    dishes.push_back(d1);
    Menu m = Menu(dishes);

    //Restaurant r = Restaurant(a, pan, m);



    return 0;
}