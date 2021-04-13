#ifndef WATCHABLE_H_
#define WATCHABLE_H_

#include <string>
#include <vector>
using namespace std;

class Session;

class Watchable{
public:
    Watchable(long id, int length, const std::vector<std::string>& tags);
    virtual ~Watchable();
    virtual std::string toString() const = 0;
    virtual Watchable* getNextWatchable(Session&) const = 0;
    long getId() const;
    int getLength() const;
    std::vector<std::string> getTags() const;
    Watchable(const Watchable &watch);
    //Watchable &operator=(const Watchable &watch);
    string tagsToString() const;
    virtual long getNextEpisodeId() const = 0;
    virtual void setNextEpisodeId(long num) = 0;
    virtual Watchable* clone()=0;
    virtual string toString2()=0;
private:
    const long _id;
    int _length;
    std::vector<std::string> _tags;
};

class Movie : public Watchable{
public:
    Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags);
    Movie(const Movie &movie);
    virtual std::string toString() const;
    string toString2();
    virtual Watchable* getNextWatchable(Session&) const;
    string getName() const ;
    long getNextEpisodeId() const;
    virtual void setNextEpisodeId(long num);
    Watchable *clone();

private:
    std::string name;

};


class Episode: public Watchable{
public:
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags);
    Episode(const Episode &epi);
    Watchable* clone();
    virtual std::string toString() const;
    string toString2();
    virtual Watchable* getNextWatchable(Session&) const;
    string getSeriesName() const;
    string getEpisodeNumber() const;
    long getNextEpisodeId() const;
    int getEpi() const;
    void setNextEpisodeId(long num);
    int getSe() const ;
private:
    std::string seriesName;
    int season;
    int episode;
    long nextEpisodeId;//NEED TO ADD TO THE CONSTRUCTOR
};


#endif
