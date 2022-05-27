//#include "src/restaurant/Restaurant.h"
#include "src/pantry/Product.h"

using namespace std;

int main(){

    Product p = Product("jablko",6, g);
    cout << p.get_name()<< " " << p.get_quantity() << " " << p.get_unit() << endl;
    return 0;
}