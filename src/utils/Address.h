#include<iostream>
#include <json/json.h>
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
    Addres(std::string co, std::string r, std::string ci, std::string p_c, std::string s, std::string b, double lat, double lng):
    country(co), region(r), city(ci), postal_code(p_c), street(s), building(b), latitude(lat), longitude(lng){};
    std::string get_country(){return country;}
    std::string get_region(){return region;}
    std::string get_city(){return city;}
    std::string get_postal_code(){return postal_code;}
    std::string get_street(){return street;}
    std::string get_building(){return building;}
    double get_latitude(){return latitude;}
    double get_longitude(){return longitude;}
    std::string to_string(){
        std::string res;
        res = "ul." + street +" "+ building+", "+ postal_code + " "+city;
        return res;
    }

    Json::Value parse_to_json(){
        Json::Value add;
        add["country"] = country;
        add["region"] = region;
        add["city"] = city;
        add["postal_code"] = postal_code;
        add["street"] = street;
        add["building"] = building;
        add["coordinates"]["latitude"] = latitude;
        add["coordinates"]["longitude"] = longitude;

        return add;
    }

};