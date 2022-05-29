#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <fstream>   
#include <json/json.h>
#include "Menu.h"

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
    bool dtypes[3] = {1, 1, 1};
    os << "---Menu---\n\n";
    os << "Przystawki:\n";
    for(auto const &dish : menu.get_dishes())
    {
        if(dish.get_enum_dish_type() == danie_glowne && dtypes[0])
        {
            os << "\nDania główne:\n";
            dtypes[0] = 0;
        }
        else if(dish.get_enum_dish_type() == deser && dtypes[1])
        {
            os << "\nDesery:\n";
            dtypes[1] = 0;
        }
        else if(dish.get_enum_dish_type() == napoje && dtypes[2])
        {
            os << "\nNapoje:\n";
            dtypes[2] = 0;
        }
        os << dish;
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

void Menu::generate_lunch_menu()
{
    ofstream file;
    file.open ("lunch.txt");
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    file << "Lunch menu - " << (now->tm_year + 1900) << '.' 
    << (now->tm_mon + 1) << '.' <<  now->tm_mday << "\n";
    vector<size_t> types;
    for (size_t i = 1; i < dishes.size(); i++)
    {
        if(dishes[i].get_enum_dish_type() != dishes[i-1].get_enum_dish_type())
            types.push_back(i);
    }
    types.push_back(dishes.size());
    srand (time(NULL));
    file << "Przystawka:\n" << dishes[rand() % types[0]].get_name();
    file << "\nDanie główne:\n" << dishes[rand() % (types[1]-types[0])+types[0]].get_name();
    file << "\nDeser:\n" << dishes[rand() % (types[2]-types[1])+types[1]].get_name();
    file.close();
}


Json::Value Menu::parse_menu_to_json()
{
    Json::Value root;
    for(size_t i = 0; i < dishes.size(); i++){
        root.append(dishes[i].parse_dish_to_json());
    }
    return root;
}

Menu Menu::parse_from_json(Json::Value m)
{
    Menu menu;
    for(auto it = m.begin(); it != m.end(); it++){
       menu.add_dish(Dish::parse_dish_from_json(*it));
    }
    return menu;
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
