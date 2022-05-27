#include<iostream>
#pragma once

class Addres{
    std::string country;
    std::string region;
    std::string city;
    std::string postal_code;
    std::string street;
    std::string building;
    double latitude;
    double longitude;

    public:
    Addres(std::string co, std::string r, std::string ci, std::string p_c, std::string s, std::string b):
    country(co), region(r), city(ci), postal_code(p_c), street(s), building(b){};
    std::string get_country(){return country;}
    std::string get_region(){return region;}
    std::string get_city(){return city;}
    std::string get_postal_code(){return postal_code;}
    std::string get_street(){return street;}
    std::string get_building(){return building;}
    double get_latitude(){return latitude;}
    double get_longitude(){return longitude;}

};