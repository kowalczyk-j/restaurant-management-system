#pragma once
#include <vector>

template <typename T> class Staff
{
private:
    std::vector<T> staff;
public:
    Staff(std::vector<T> s) : staff(s) {}
    size_t number_employed() const {return staff.size();}
    std::vector<T> const& get_staff() const {return staff;}
    void fire(const T& staff_member)
    {
        auto found = find(staff.begin(), staff.end(), staff_member);
        if(found == staff.end()) throw PersonNotFound;
        else staff.erase(found);
    }
    void employ(const T& staff_member)
    {
        staff.push_back(staff_member);
    }
    friend std::ostream& operator<<(std::ostream& os, const Staff& staff)
    {
        for(const auto& staff_member : staff)
            os << staff_member;
        return os;
    }
};

