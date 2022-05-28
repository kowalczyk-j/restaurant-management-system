#include "Restaurant.h"
#include <vector>


class RestaurantNet{
    std::vector<Restaurant> restaurants;

    public:
    RestaurantNet(std::vector<Restaurant> res): restaurants(res){};
    std::vector<Restaurant> get_restaurants(){return restaurants;}
};