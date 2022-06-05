#include<iostream>
#include <json/json.h>
#pragma once

class Addres{
    std::string country;        //kraj
    std::string region;         //region (województwo)
    std::string city;           //miasto
    std::string postal_code;    //kod pocztowy
    std::string street;         //ulica
    std::string building;       //budynek
    double latitude;            //szerokość geograficzna
    double longitude;           //długość geograficzna

    public:
    //konstruktor
    Addres(std::string ci="", std::string p_c="", std::string s="", std::string b="", std::string co="", std::string r="", double lat=0, double lng=0):
    country(co), region(r), city(ci), postal_code(p_c), street(s), building(b), latitude(lat), longitude(lng){};

    //gettery
    std::string const& get_city() const {return city;}
    std::string const& get_postal_code() const {return postal_code;}
    std::string const& get_street() const {return street;}
    std::string const& get_building() const {return building;}
    std::string const& get_country() const {return country;}
    std::string const& get_region() const {return region;}
    double get_latitude() const {return latitude;}
    double get_longitude() const {return longitude;}

    //settery
    void set_city(std::string const& c){city = c;}
    void set_postal_code(std::string const& p_c){postal_code = p_c;}
    void set_street(std::string const& s){street = s;}
    void set_building(std::string const& b){building = b;}
    void set_country(std::string const& c){country = c;}
    void set_region(std::string const& r){region = r;}
    void set_latitude(double lat){latitude = lat;}
    void set_longitude(double lng){longitude = lng;}



    std::string to_string() const{
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

    static Addres parse_from_json(Json::Value add){
        return Addres(add["city"].asString(),
                      add["postal_code"].asString(),
                      add["street"].asString(),
                      add["building"].asString(),
                      add["country"].asString(),
                      add["region"].asString(),
                      add["coordinates"]["latitude"].asDouble(),
                      add["coordinates"]["longitude"].asDouble());
    }
};