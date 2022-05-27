#include <iostream>
#include <vector>
#include "../dish menu/Dish.h"

class AbstractOrder{
    protected:
    unsigned int order_id;
    std::vector<Dish> ordered_dishes;

    public:
    unsigned int get_order_id() const {return order_id;}
    std::vector<Dish> get_ordered_dishes() const {return ordered_dishes;}
    Money get_order_value() const;
    virtual void print() const = 0;
};