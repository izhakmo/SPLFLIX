#include <Session.h>
#include <fstream>
#include <json.hpp>
//
// Created by izhakmo on 20/11/2019.
using json=nlohmann::json ;
std::ifstream i("config1.json");
json j;
i>>j;

unordered_map<string, User *>& Session::getUserMap() {
    return userMap;
}

User*Session::searchUser(string name) {
    unordered_map<std::string,User*> tempMap = getUserMap();
    User* userPtr;
    unordered_map<std::string,User*>::const_iterator got = tempMap.find (name);
    if(got==tempMap.end()){
        userPtr = nullptr;
    }
    else{
        userPtr = got->second;
    }

    return userPtr;
}


//

