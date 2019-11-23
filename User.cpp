#include "User.h"
#include <queue>

//
// Created by izhakmo on 20/11/2019.
using namespace std;
User::User(const std::string &name) :name(name),history(vector<Watchable*>()){}


std::vector<Watchable*> User::get_history() const {
    return history;
}

string User::getName() const {
    return name;
}

//========LengthRecommenderUser============
LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name), numSeen(0),average(0) {

}

//======RerunRecommenderUser=============
RerunRecommenderUser::RerunRecommenderUser(const std::string& name)
:recommendations(queue<Watchable*>()),User(name){}

//===========GenreRecommenderUser===========
