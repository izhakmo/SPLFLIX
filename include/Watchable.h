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
    Watchable(Watchable &watch);
    Watchable &operator=(const Watchable &watch);

     string tagsToString() const;
private:
    const long _id;
    int _length;
    std::vector<std::string> _tags;
};

class Movie : public Watchable{
public:
    Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
    string getName() const ;
private:
    std::string name;
};


class Episode: public Watchable{
public:
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
    string getSeriesName() const;
    string getEpisodeNumber() const;
    long getNextEpisodeId() const;
private:
    std::string seriesName;
    int season;
    int episode;
    long nextEpisodeId;
};

#endif
