#include <vector>

template <typename T> class Staff
{
private:
    std::vector<T> staff;
public:
    Staff(std::vector<T> s) : staff(s) {}
    void fire(const T& staff_member)
    {
        remove(staff.begin(), staff.end(), staff_member);
    }
    void employ(const T& staff_member)
    {
        staff.push_back(staff_member);
    }
    friend std::ostream& operator<<(std::ostream& os, const Staff& staff) const
    {
        for(const auto& staff_member : staff)
            os << staff_member;
        return os;
    }
};

