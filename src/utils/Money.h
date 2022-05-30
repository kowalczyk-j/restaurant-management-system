#pragma once
#include <iostream>
#include <stdexcept>

class Money
/*
    Klasa do reprezentowania wartości pieniężnych w złotówkach
*/
{
    unsigned int cents; //kwota w groszach (np. 8,00 zł jako 800)

public:
    //konstruktory
    Money();
    Money(Money const& m);
    explicit Money(int z, int c);
    explicit Money(int c);

    //gettery
    unsigned int get_zlotys() const {return int(cents/100);}
    unsigned int get_cents() const {return cents%100;}
    unsigned int get_in_cents() const {return cents;}

    //przeciążane operatory
    Money operator=(Money const& m);
    Money operator+(Money const& m) const;
    Money operator-(Money const& m) const;
    Money operator*(unsigned int s) const;
    Money operator/(unsigned int s) const;
    Money & operator+=(Money const& m);
    Money & operator-=(Money const& m);
    Money & operator*=(unsigned int s);
    Money & operator/=(unsigned int s);
    bool operator==(Money const& m) const;

    std::string to_string() const;

};

std::ostream& operator<<(std::ostream& os, Money const& m);
