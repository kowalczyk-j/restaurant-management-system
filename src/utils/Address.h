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
    Addres(std::string ci="", std::string p_c="", std::string s="", std::string b="", std::string co="", std::string r="", double lat=0, double lng=0):
    country(co), region(r), city(ci), postal_code(p_c), street(s), building(b), latitude(lat), longitude(lng){};
    std::string get_city(){return city;}
    std::string get_postal_code(){return postal_code;}
    std::string get_street(){return street;}
    std::string get_building(){return building;}
    std::string get_country(){return country;}
    std::string get_region(){return region;}
    double get_latitude(){return latitude;}
    double get_longitude(){return longitude;}

    void set_city(std::string c){city = c;}
    void set_postal_code(std::string p_c){postal_code = p_c;}
    void set_street(std::string s){street = s;}
    void set_building(std::string b){building = b;}
    void set_country(std::string c){country = c;}
    void set_region(std::string r){region = r;}



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