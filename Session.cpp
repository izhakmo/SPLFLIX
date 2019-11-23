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

string Session::getUserChange(){
    return reqUserChange;
}

void Session::setActiveUser(User *user) {
    this->activeUser=user;

}

void Session::setUserChange(string user) {//Change the reqUserChange
    reqUserChange=user;
}

void Session::pushToActionLog(BaseAction *action) {
    actionsLog.push_back (action);
}

vector<Watchable*> Session::getContentVector() {
    return content;
}

vector<BaseAction*> Session::getActionsLog() {
    return actionsLog;
}
string Session::getUserToDelete() {//Get the needToDelete field
    return needToDelete;
}

void Session::setNeedToDelete(string user) {
    needToDelete=user;
}

string Session::getUserToDelete() {//Get the needToDelete field
    return needToDelete;
}

//

