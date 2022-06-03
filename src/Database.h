#pragma once
#include <iostream>
#include <exception>
#include <map>
#include <vector>
#include <functional>

enum exception {KeyNotFound, NotUniqueKey};

template <typename T>
class Database
{
    unsigned int next_id = 1001;
    std::map<unsigned int, T*> data;

    public:
    ~Database(){
         for(typename std::map<unsigned int, T*>::iterator it = data.begin(); it != data.end(); ++it) {
            delete it->second;
        }
    }
    T* operator[](unsigned int id) const{
        if(data.find(id) == data.end()){
            throw KeyNotFound;
        }
        return data.at(id);
    }

    unsigned int add_data(T* data_to_add){
        data_to_add->set_id(next_id);
        data[next_id] = data_to_add;
        unsigned int data_id = next_id;
        this->move_to_next_free_id();
        return data_id;
    }

    void remove_data(unsigned int id){
        if(data.find(id) == data.end()){
            throw KeyNotFound;
        }
        delete data[id];
        data.erase(id);
        this->free_up_id(id);
    }

    void add_data_with_id(T* data_to_add){
        if(data.find(data_to_add->get_id()) == data.end()){
            throw NotUniqueKey;
        }
        data[data_to_add->get_id()] = data_to_add;
    }

    void remove_data_without_deleting(unsigned int id){
        if(data.find(id) == data.end()){
            throw KeyNotFound;
        }
        data.erase(id);
    }

    std::vector<T*> get_full_data(){
        std::vector<T*> full_data;
        for(typename std::map<unsigned int, T*>::iterator it = data.begin(); it != data.end(); ++it) {
            full_data.push_back(it->second);
        }
        return full_data;
    }

    size_t size(){return data.size();}

    bool is_in_database(unsigned int id){
        if(data.find(id) == data.end()) return false;
        else return true;
    }

    void  move_to_next_free_id(){
        while(this->is_in_database(next_id)){
            next_id ++;
        }
    }

    void free_up_id(unsigned int free_id){
        next_id = free_id;
    }

};