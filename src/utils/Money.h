#pragma once
#include <iostream>
#include <stdexcept>

class Money
{
    unsigned int cents;

public:
    // constructors
    Money();
    Money(Money const& m);
    explicit Money(int z, int c);
    explicit Money(int c);

    // getters
    unsigned int get_zlotys() const {return int(cents/100);}
    unsigned int get_cents() const {return cents%100;}
    unsigned int get_in_cents() const {return cents;}

    // overloaded operators
    Money operator=(Money const& m);
    Money operator+(Money const& m) const;
    Money operator-(Money const& m) const;
    Money operator*(unsigned int s) const;
    Money operator/(unsigned int s) const;
    Money & operator+=(Money const& m);
    Money & operator-=(Money const& m);
    Money & operator*=(unsigned int s);
    Money & operator/=(unsigned int s);

    std::string to_string() const;

};

std::ostream& operator<<(std::ostream& os, Money const& m);
