#include "User.h"
#include "Watchable.h"
#include <queue>
#include <Session.h>
#include <Action.h>
#include "algorithm"
//
// Created by izhakmo on 20/11/2019.
using namespace std;
User::User(const std::string &name) :history(vector<Watchable*>()),name(name){}
User::~User() {
    for (auto & i : get_history()) {
        i = nullptr;
    }
}
std::vector<Watchable*>& User::get_history() {
    return history;
}

string User::getName() const {
    return name;
}

int User::getAverage() {
    return 0;
}

void User::update(int i) {

}

int User::getNumSeen() {
    return 0;
}

void User::setAverage(int i) {

}

void User::setNumSeen(int i) {

}

vector<Watchable*> User::get_history() const {
    return history;
}

//========LengthRecommenderUser============
LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name), average(0),numSeen(0) { }


string LengthRecommenderUser::getUserRecType() {return "len";}


Watchable* LengthRecommenderUser::getRecommendation(Session &s) {
    User *currentUser = s.getActiveUser();
    vector<Watchable *> historyVec = currentUser->get_history();
    vector<Watchable *> contVec = s.getContentVector();
    int avg = currentUser->getAverage();
    int min = 1000000000;//TODO
    //Watchable *toReturn = contVec.at(0);
    Watchable* toReturn= nullptr;
    for (auto & i : contVec) {
        int length = i->getLength();
        bool found2 = false;
        for (auto & j : historyVec) {
            if (i->getId() == j->getId()) {
                found2 = true;
            }
        }
        if (found2 == false && (abs(length - avg) < min)) {
            toReturn = i;
            min = abs(i->getLength() - avg);
        }
        if (found2 == false && min == 0) {
            return toReturn;
        }

    }
    return toReturn;
}

void LengthRecommenderUser::update(int length) {
    int avg = this->getAverage();
    int numseen = this->getNumSeen();
    avg = (avg*numseen)+length;
    int update = numseen+1;
    this->setNumSeen(update);
    avg = avg/(this->getNumSeen());
    setAverage(avg);

}

int LengthRecommenderUser::getAverage() {
    return average;
}
int LengthRecommenderUser::getNumSeen() {
    return numSeen;
}

void LengthRecommenderUser::setNumSeen(int i){
    numSeen=i;
}
void LengthRecommenderUser::setAverage(int i){
    average=i;
}


void LengthRecommenderUser::copyAcount(User *user,Session& sess) {
    int avg = user->getAverage();
    int numseen = user->getNumSeen();
    vector<Watchable*> &historyVec = user->get_history();
    sess.AddNewUserToMap(this->getName(),this);
    this->setAverage(avg);
    this->setNumSeen(numseen);
    vector<Watchable*> &newHistoVec = this->get_history();
    for(auto p : historyVec){
        newHistoVec.push_back(p);
    }
}

LengthRecommenderUser* LengthRecommenderUser::clone() {
    int avg = this->getAverage();
    int numSeen = this->getNumSeen();
    string name = this->getName();
    LengthRecommenderUser* newUser = new LengthRecommenderUser(name);
    newUser->setNumSeen(numSeen);
    newUser->setAverage(avg);
    return newUser;
}



//======RerunRecommenderUser=============
RerunRecommenderUser::RerunRecommenderUser(const std::string& name):User(name),numberOfRecs(0){}

string RerunRecommenderUser::getUserRecType() { return "rer";}


Watchable* RerunRecommenderUser::getRecommendation(Session &s) {
    numberOfRecs++;
    return this->get_history()[numberOfRecs-1];
}

int RerunRecommenderUser::getNumOfRecs() {
    return numberOfRecs;
}

void RerunRecommenderUser::setNumOfRecs(int i) {
    numberOfRecs=i;
}

void RerunRecommenderUser::copyAcount(User *user, Session &sess) {
    sess.AddNewUserToMap(this->getName(),this);
    vector<Watchable*> &historyVec = user->get_history();
    vector<Watchable*> &newHistoVec = this->get_history();
    int numofrecs = user->getNumOfRecs();
    this->setNumOfRecs(numofrecs);
    for(auto p : historyVec){
        newHistoVec.push_back(p);
    }
}

RerunRecommenderUser* RerunRecommenderUser::clone() {
    int numOfRecs = this->getNumOfRecs();
    string name =this->getName();
    RerunRecommenderUser* newUser = new RerunRecommenderUser(name);
    newUser->setNumOfRecs(numOfRecs);
    return newUser;
}


GenreRecommenderUser::GenreRecommenderUser(const std::string& name):User(name),popGenre(vector<pair<int,string>>()){

}


Watchable* GenreRecommenderUser::getRecommendation(Session &s) {
    vector<Watchable*>&allContent=s.getContentVector();
    for(auto & i : popGenre){    //todo IIIIIII
        string popularTag=i.second;  //TODO it will return the tag of the index

        for(auto & j : allContent){
            vector<string> contentTags=j->getTags();

            for(const auto & contentTag : contentTags) {
                if (contentTag==popularTag){
                    if(!contentInHistory(j)){
                        return j;
                    }
                }
            }
        }
    }   //TODO if no such elemet- return null
    return nullptr;
}

string GenreRecommenderUser::getUserRecType() { return "gen";}


bool User::contentInHistory(Watchable *a) {
    vector<Watchable*>&myHistory=get_history();
    for(auto & i : myHistory){
        if(a==i){
            return true;
        }
    }

    return false;
}

int User::getNumOfRecs() {
    return 0;
}

void User::setNumOfRecs(int i) {

}

vector<pair<int, string>> &User::getpopGenreVector() {
    ;
    return getpopGenreVector();
}

vector<pair<int,string>>& GenreRecommenderUser::getpopGenreVector() { return popGenre;}


void GenreRecommenderUser::updateGenreList(int placeInVector) {
    vector<pair<int,string>>&toUpdate=getpopGenreVector();
    toUpdate[placeInVector].first--;

}

void GenreRecommenderUser::addGenreToList(string genreToAdd) {
    popGenre.push_back(make_pair(0,genreToAdd));
};

void GenreRecommenderUser::update(int i) {
    vector<string>lastWatchGenres=get_history().back()->getTags();
    bool found;
    for(const auto & lastWatchGenre : lastWatchGenres){
        found= false;
        for(unsigned j=0;j<popGenre.size()&& !found;j++){
            if(popGenre[j].second==lastWatchGenre){
                found= true;
                updateGenreList(j);
            }
        }
        if(!found){
            addGenreToList(lastWatchGenre);
        }
    }
    sort(popGenre.begin(),popGenre.end());
    for(unsigned i=0;i<popGenre.size();i++){
    }
};

void GenreRecommenderUser::copyAcount(User *user, Session &sess) {
    sess.AddNewUserToMap(this->getName(),this);
    vector<Watchable*> &historyVec = user->get_history();
    vector<Watchable*> &newHistoVec = this->get_history();
    for(auto p : historyVec){
        newHistoVec.push_back(p);
    }
    vector<pair<int,string>> &copyvec = user->getpopGenreVector();
    for(const auto & i : copyvec){
        this->getpopGenreVector().push_back(i);
    }

}

GenreRecommenderUser* GenreRecommenderUser::clone() {
    string name = this->getName();
    GenreRecommenderUser* newUser = new GenreRecommenderUser(name);
    newUser->setPopGenre(this->getpopGenreVector());
    return newUser;
}

void GenreRecommenderUser::setPopGenre(vector<pair<int, string>> vec) {
    this->popGenre=vec;
}
