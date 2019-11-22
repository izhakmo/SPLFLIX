#include <Watchable.h>

//
// Created by izhakmo on 20/11/2019.

//Constructor
Watchable::Watchable(long id, int length, const std::vector<std::string>& tags)
:_id(id),_length(length){
    _tags=tags;

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




Movie::Movie(long id, const std::string &name, int length, const std::vector<std::string> &tags)
:name(name),Watchable(id,length,tags){} //Constructor


Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,const std::vector<std::string> &tags)
:Watchable(id,length,tags),seriesName(seriesName),season(season),episode(episode),nextEpisodeId(){} //TODO NEXTEPISODEID MUST BE CHECKED



//

