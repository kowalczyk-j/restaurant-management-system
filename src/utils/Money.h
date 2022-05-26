#include <iostream>
#include <stdexcept>

class Money
{
    unsigned int cents;

public:
    // constructors
    Money();
    explicit Money(int z, int c);
    explicit Money(int c);

    // getters
    unsigned int get_zlotys() const {return int(cents/100);}
    unsigned int get_cents() const {return cents%100;}

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

};

std::ostream& operator<<(std::ostream& os, Money const& m);
