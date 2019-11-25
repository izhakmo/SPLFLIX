#include "User.h"
#include "Watchable.h"
#include <queue>

//
// Created by izhakmo on 20/11/2019.
using namespace std;
User::User(const std::string &name) :name(name),history(vector<Watchable*>()){}
User::User(string name,User* ToCopy):name(name) {   //copyConstructor from other User
    history=(ToCopy->get_history());

}

User::~User() {history.clear();}    //TODO check the Watchable memory release


std::vector<Watchable*> User::get_history() const {
    return history;
}

string User::getName() const {
    return name;
}

//========LengthRecommenderUser============
LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name), numSeen(0),average(0) {

}
string LengthRecommenderUser::getUserRecType() {return "len";}

Watchable* LengthRecommenderUser::getRecommendation(Session &s) {

}
LengthRecommenderUser::LengthRecommenderUser(string name, LengthRecommenderUser *UserToCopy):User(name,
                                                                                                  reinterpret_cast<User *>(&UserToCopy)) {
    numSeen=UserToCopy->numSeen;
    average=UserToCopy->average;
}

//======RerunRecommenderUser=============
RerunRecommenderUser::RerunRecommenderUser(const std::string& name)
:recommendations(queue<Watchable*>()),User(name){}

RerunRecommenderUser::RerunRecommenderUser(string name, RerunRecommenderUser *UserToCopy):User(name,
                                                                                               reinterpret_cast<User *>(&UserToCopy)) {
    recommendations=(UserToCopy->recommendations);
}

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

string RerunRecommenderUser::getUserRecType() {return "rer";}

//===========GenreRecommenderUser===========
GenreRecommenderUser::GenreRecommenderUser(const std::string& name)
:User(name){
 //   genre=
}

string GenreRecommenderUser::getUserRecType() { return "gen";}

GenreRecommenderUser::GenreRecommenderUser(string name,GenreRecommenderUser* UserToCopy):User(name,
                                                                                              reinterpret_cast<User *>(&UserToCopy)) {
    genre(UserToCopy->genre);   //TODO IN ALL CONSTRUCTOR DUPLICATE ALL FIELDS

}
