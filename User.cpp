#include "User.h"
#include "Watchable.h"
#include <queue>

//
// Created by izhakmo on 20/11/2019.
using namespace std;
User::User(const std::string &name) :name(name),history(vector<Watchable*>()){}
User::~User() {history.clear();}    //TODO check the Watchable memory release


std::vector<Watchable*> User::get_history() const {
    return history;
}

string User::getName() const {
    return name;
}

//========LengthRecommenderUser============
LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name), numSeen(0),average(0) { }

Watchable* LengthRecommenderUser::getRecommendation(Session &s) {

}

//======RerunRecommenderUser=============
RerunRecommenderUser::RerunRecommenderUser(const std::string& name)
:recommendations(queue<Watchable*>()),User(name){}

Watchable* RerunRecommenderUser::getRecommendation(Session &s) {    //if the Q is empty we return null, else, dequeue and enqueue the element
    if(recommendations.empty())
        return nullptr;     //TODO CHECK VIRTUAL
    else{
        Watchable *rec=recommendations.front();
        recommendations.pop();
        recommendations.push(rec);
        return rec;
    }
}

//===========GenreRecommenderUser===========
GenreRecommenderUser::GenreRecommenderUser(const std::string& name)
:User(name){}
