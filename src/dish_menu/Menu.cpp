#include <iostream>
#include <vector>
#include <algorithm>
#include "Menu.h"
#include <json/json.h>

static bool compare_dish_type(Dish left, Dish right)
{
    return (left.get_enum_dish_type() < right.get_enum_dish_type());
}

static bool operator==(Dish left, dish_type right)
{
    return (left.get_enum_dish_type() == right);
}

Menu::Menu(std::vector<Dish> dishes)
{
    sort(dishes.begin(), dishes.end(), compare_dish_type);
    this->dishes = dishes;
}

std::ostream& operator<<(std::ostream& os, Menu  menu)
{
    os << "---Menu---\n";
    // for(size_t i = 0; i < menu.size(); i++)
    // {
    //     os << menu.get_dishes()[i];
    // }
    for(auto const &dish : menu.get_dishes())    //dlaczego nie działa?
    {
        os << dish << endl;
    }
    return os;
}
void Menu::add_dish(Dish const& dish)
{
    auto place = find(dishes.begin(), dishes.end(), dish.get_enum_dish_type());
    dishes.insert(place, dish);
}
void Menu::remove_dish(unsigned int dish_idx)
{
    dishes.erase(dishes.begin() + dish_idx);
}

Json::Value Menu::parse_menu_to_json()
{
    Json::Value root;
    for(size_t i = 0; i < dishes.size(); i++){
        root.append(dishes[i].parse_dish_to_json());
    }
    return root;
}
// Menu::iterator::iterator(std::vector<Dish>::const_iterator const &cstart,
//  std::vector<Dish>::const_iterator const &cstop) : start(cstart), stop(cstop)
// {
//     auto type_less = [](Dish const &left, Dish const &right)
//     { return left.get_enum_dish_type() < right.get_enum_dish_type(); };
//     current = std::min_element(start, stop, type_less);
// }

// static bool operator==(Dish const& dish, int dish_type)
// {
//     return dish.get_enum_dish_type() == dish_type;
// }

// Menu::iterator Menu::iterator::operator++()
// {
//     int cur_val = current->get_enum_dish_type();
//     current = find(current+1, stop, cur_val);
//     if(current == stop) // if no more items of previous dish_type
//     {
//         if(cur_val <= napoje)
//         {
//             cur_val++;
//             current = find(start, stop, cur_val);
//         }
//         else
//             current = stop;
//     }
//     return *this;
// }
