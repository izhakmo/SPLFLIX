#include <Watchable.h>

//
// Created by izhakmo on 20/11/2019.
using namespace std;

//Constructor
Watchable::Watchable(long id, int length, const std::vector<std::string>& tags)
:_id(id),_length(length){
    _tags=tags;

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
}   //TODO CHECK

//copy constructor
Watchable::Watchable(Watchable &watch)
:_id(watch.getId()),_length(watch.getLength()),_tags(watch.getTags()) {}

//copy assignment Operator
Watchable &Watchable::operator=(const Watchable &watch){
    if(this==&watch){
        return *this;
    }


//    _tags.clear();
//    _tags=watch.getTags();
//    _id=watch.getId();
//    _length=watch.getLength();

}




Movie::Movie(long id, const string &name, int length, const std::vector<std::string> &tags)
:name(name),Watchable(id,length,tags){} //Constructor

string Movie::getName() const {return name;}

string Movie::toString() const {return getName()+" "+ to_string(getLength())+" minutes "+tagsToString();}


Episode::Episode(long id, const string &seriesName, int length, int season, int episode,const std::vector<std::string> &tags)
:Watchable(id,length,tags),seriesName(seriesName),season(season),episode(episode),nextEpisodeId(){} //TODO NEXTEPISODEID MUST BE CHECKED

string Episode::getEpisodeNumber() const {return "S"+to_string(season)+"E"+to_string(episode);}
string Episode::getSeriesName() const {return seriesName;}
string Episode::toString() const {return getSeriesName()+" "+ getEpisodeNumber()+" "+to_string(getLength())+" minutes "+tagsToString();}
long Episode::getNextEpisodeId() const {}

//

