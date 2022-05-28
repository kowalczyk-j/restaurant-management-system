#pragma once
#include <fstream>
#include <vector>

enum StaffExceptions {PersonNotFound, AlreadyStaffMember};

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
        auto found = find(staff.begin(), staff.end(), staff_member);
        if(found != staff.end()) throw AlreadyStaffMember;
        else staff.push_back(staff_member);
    }

    void parse_to_json(std::string path)
    {
        Json::Value json_staff(Json::arrayValue);
        for(auto& staff_member : staff)
            json_staff.append(staff_member.parse_to_json());

        std::ofstream file;
        file.open(path);
        Json::StyledWriter writer;
        file << writer.write(json_staff);
        file.close();
    }

    friend std::ostream& operator<<(std::ostream& os, const Staff& staff)
    {
        for(const auto& staff_member : staff.get_staff())
            os << staff_member << std::endl;
        return os;
    }
};

