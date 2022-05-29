    #include"Money.h"

    Money::Money(){
        cents = 0;
    }
    Money::Money(int z, int c){
        if(z < 0 or c < 0) throw std::out_of_range("Kwota nie może być ujemna");
        else cents = z*100 + c;
    }
    Money::Money(int c){
        if(c >= 0) cents = c;
        else throw std::out_of_range("Kwota nie może być ujemna");
    }
    Money::Money(Money const& m ){
        cents = m.cents;
    }
    Money Money::operator=(Money const& m){
        cents = m.cents;
        return *this;
    }
    Money Money::operator+(Money const& m) const{
        Money rm (cents+m.cents);
        return rm;
    }
    Money Money::operator-(Money const& m) const{
        Money rm = Money(cents-m.cents);
        return rm;
    }
    Money Money::operator*(unsigned int s) const{
        Money rm = Money(cents*s);
        return rm;
    }
    Money Money::operator/(unsigned int s) const{
        Money rm = Money(int(cents/s));
        return rm;
    }
    Money & Money::operator+=(Money const& m){
        this->cents += m.cents;
        return *this;
    }
    Money & Money::operator-=(Money const& m){
        this->cents -= m.cents;
        return *this;
    }
    Money & Money::operator*=(unsigned int s){
        this->cents *= s;
        return *this;
    }
    Money & Money::operator/=(unsigned int s){
        this->cents /= s;
        return *this;
    }
    bool Money::operator==(Money const& m) const{
        return cents == m.cents;
    }

    std::string Money::to_string() const{
        std::string res;
        if (get_cents() < 10){
            res += std::to_string(get_zlotys());
            res += ",0";
            res += std::to_string(get_cents());
            res += "zł";
            return res;
        }
        else{
            res += std::to_string(get_zlotys());
            res += ",";
            res += std::to_string(get_cents());
            res += "zł";
            return res;
        }
    }



std::ostream& operator<<(std::ostream& os, Money const& m){
    if (m.get_cents() < 10){
        return os << m.get_zlotys() << ",0"<< m.get_cents()<<"zł";
    }
    else{
        return os << m.get_zlotys() << ','<<  m.get_cents()<<"zł";
    }
}