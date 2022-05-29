#pragma once
#include <fstream>
#include <vector>

enum StaffExceptions {AlreadyStaffMember, PositionOutOfBounds};

template <typename T> class Staff
{
private:
    std::vector<T> staff;
public:
    Staff(std::vector<T> s) : staff(s) {}
    size_t number_employed() const {return staff.size();}
    std::vector<T> const& get_staff() const {return staff;}
    size_t size(){return staff.size();}

    T & operator[](size_t pos)
    {
        if(pos<=number_employed())
            return staff[pos];
        else throw PositionOutOfBounds;
    }

    T const& operator[](size_t pos) const
    {
        if(pos<=number_employed())
            return staff[pos];
        else throw PositionOutOfBounds;
    }

    void fire(size_t position)
    {
        if(position<=number_employed())
            staff.erase(staff.begin() + position);
        else throw PositionOutOfBounds;
    }

    void employ(const T& staff_member)
    {
        auto found = find(staff.begin(), staff.end(), staff_member);
        if(found != staff.end()) throw AlreadyStaffMember;
        else staff.push_back(staff_member);
    }

    Json::Value parse_to_json()
    {
        Json::Value json_staff(Json::arrayValue);
        for(auto& staff_member : staff)
            json_staff.append(staff_member.parse_to_json());

        return json_staff;
    }

    friend std::ostream& operator<<(std::ostream& os, const Staff& staff)
    {
        for(const auto& staff_member : staff.get_staff())
            os << staff_member << std::endl;
        return os;
    }
};

