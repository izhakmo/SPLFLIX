//
// Created by ziv on 20/11/2019.
//
#include <iostream>
#include <User.h>
#include "Watchable.h"
#include <Session.h>
using namespace std;
//Constructor
Watchable::Watchable(long id, int length, const std::vector<std::string>& tags)
        :_id(id),_length(length),_tags(tags){
}

string Watchable::tagsToString() const{
    string tag="[";
    for(auto iter=_tags.begin() ;   iter !=_tags.end()-1  ;   iter++){
        tag=tag+*iter+", ";
    }
    tag=tag+_tags.back()+"]";

    return tag;
}

//getters
long Watchable::getId() const { return _id;}
int Watchable::getLength() const {return _length;}
std::vector<std::string> Watchable::getTags() const {return _tags;}

//destructor
Watchable::~Watchable(){
    _tags.clear();
}

//copy constructor
Watchable::Watchable(const Watchable &watch)
        :_id(watch.getId()),_length(watch.getLength()),_tags(watch.getTags()) {}

//copy assignment Operator
//Watchable &Watchable::operator=(const Watchable &watch){
//    if(this==&watch){
//        return *this;
//    }
//
//    _tags.clear();
//    _tags=watch.getTags();
//    _id=watch.getId();
//    _length=watch.getLength();
//
//}



Movie::Movie(long id, const string &name, int length, const std::vector<std::string> &tags)
        :Watchable(id,length,tags),name(name){} //Constructor

string Movie::getName() const {return name;}

string Movie::toString() const {return to_string(getId())+". "+getName()+" "+ to_string(getLength())+" minutes "+tagsToString();}

string Movie::toString2() {
    return getName();

}

Watchable *Movie::getNextWatchable(Session &sess) const {
    return nullptr;
}

long Movie::getNextEpisodeId() const {
    return 0;
}

void Movie::setNextEpisodeId(long num) {

}

Movie::Movie(const Movie &movie):Watchable(movie),name(movie.getName()) {//copy constructor
//    name=movie.getName();
}

Watchable* Movie::clone() {
    return new Movie(*this);


}


Episode::Episode(long id, const string &seriesName, int length, int season, int episode,const std::vector<std::string> &tags)
        :Watchable(id,length,tags),seriesName(seriesName),season(season),episode(episode),nextEpisodeId(){} 

string Episode::getEpisodeNumber() const {return "S"+to_string(season)+"E"+to_string(episode);}
string Episode::getSeriesName() const {return seriesName;}
string Episode::toString() const {return to_string(getId())+". "+getSeriesName()+" "+ getEpisodeNumber()+" "+to_string(getLength())+" minutes "+tagsToString();}

string Episode::toString2() {
    return getSeriesName()+" "+getEpisodeNumber();
}

long Episode::getNextEpisodeId() const {
    return nextEpisodeId;
}


void Episode::setNextEpisodeId(long num) {
    nextEpisodeId=num;
}

Watchable *Episode::getNextWatchable(Session &sess) const {
    long id = this->getNextEpisodeId();
    if(id==0){
        return nullptr;
    }
    vector<Watchable*> vcont = sess.getContentVector();
    Watchable* toReturn = vcont.at(id-1);
    return toReturn;
}

Episode::Episode(const Episode &epi)
:Watchable(epi),seriesName(epi.getSeriesName()),season(epi.getSe()),episode(epi.getEpi()),nextEpisodeId(epi.getNextEpisodeId()) {}

int Episode::getEpi() const {
    return episode;
}

int Episode::getSe() const {
    return season;
}


Watchable* Episode::clone() {
    return new Episode(*this);
}