#pragma once
#include <iostream>
#include <vector>
#include "Dish.h"

class Menu
{
    std::vector<Dish> dishes;

public:
    std::vector<Dish> get_dishes() const { return dishes; };
    size_t size() const { return dishes.size(); };
    Menu(std::vector<Dish> di) : dishes(di)
    {}
    void add_dish(Dish const& dish);
    void remove_dish(int dish_idx);

    class iterator
    {
        std::vector<Dish>::const_iterator current;
        std::vector<Dish>::const_iterator start;
        std::vector<Dish>::const_iterator stop;
    public:
        iterator(std::vector<Dish>::const_iterator const &cstart,
                std::vector<Dish>::const_iterator const &cstop);
        bool operator==(iterator const& rt) const
        {
            return (current == rt.current);
        }
        bool operator!=(iterator const& rt) const
        {
            return not operator==(rt);
        }
        iterator operator++();
        Dish const& operator*() const
        {
            return *current;
        }
    };
    };
    iterator begin() const {
        return iterator(dishes.cbegin(), dishes.cend());
    }
    iterator end() const {
        return iterator(dishes.cbegin(), dishes.cend());
    }
    friend std::ostream &operator<<(std::ostream &os, Menu const &menu);
};
