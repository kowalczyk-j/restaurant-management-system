#include <iostream>
#include <fstream>
#include <json/json.h> // or jsoncpp/json.h , or json/json.h etc.

using namespace std;

int main() {
    ifstream ifs("json_example/alice.json");


    Json::Reader reader;
    Json::Value obj;
    bool parsingSuccessful = reader.parse(ifs, obj);
    cout << "Book: " << obj["book"].asString() << endl;
    cout << "Year: " << obj["year"].asUInt() << endl;
    const Json::Value& characters = obj["characters"]; // array of characters
    for (int i = 0; i < characters.size(); i++){
        cout << "    name: " << characters[i]["name"].asString();
        cout << " chapter: " << characters[i]["chapter"].asUInt();
        cout << endl;
    }
}