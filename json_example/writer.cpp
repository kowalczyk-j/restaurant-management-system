#include <iostream>
#include <fstream>
#include <json/json.h> // or jsoncpp/json.h , or json/json.h etc.


int main() {

    Json::Value event;
    Json::Value test;
    test["test"] = "Test";
    test["prapa"] = "ma";
    Json::Value vec(Json::arrayValue);
    vec.append(test);
    vec.append(Json::Value(2));
    vec.append(Json::Value(3));

    event["competitors"]["home"]["name"] = "Liverpool";
    event["competitors"]["away"]["code"] = 89223;
    event["competitors"]["away"]["name"] = "Aston Villa";
    event["competitors"]["away"]["code"]=vec;

    std::cout << event << std::endl;

    std::ofstream file;
    file.open("json_example/file.json");


    Json::StyledWriter styledWriter;
    file << styledWriter.write(event);

    file.close();
}