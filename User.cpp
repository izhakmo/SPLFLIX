#include "User.h"
using namespace std;

//
// Created by izhakmo on 20/11/2019.
User::User(const std::string &name) :name(name),historynew vector<Watchable*>(){}


std::vector<Watchable*> User::get_history() const {
    return history;
}

const std::string & User::getName() const {
    return name;
}

//========LengthRecommenderUser============
LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name), numSeen(0) {

}


