#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <map>
class Watchable;
class Session;
using namespace std;

class User{
public:
    User(const std::string& name);
    User(string,User*);
    virtual User* clone()=0;
    virtual ~User();
    virtual Watchable* getRecommendation(Session& s) = 0;
    std::string getName() const;
    std::vector<Watchable*>&get_history();
    vector<Watchable*>get_history ()const;
    virtual string getUserRecType()=0;
    bool contentInHistory(Watchable* a);
    virtual int getAverage();
    virtual int getNumSeen();
    virtual void update(int i);
    virtual void setAverage(int i);
    virtual void setNumSeen(int i);
    virtual  int getNumOfRecs();
    virtual void setNumOfRecs(int i);
    virtual vector<pair<int,string>>& getpopGenreVector();

    virtual void copyAcount(User* user,Session& sess)=0;
protected:
    std::vector<Watchable*> history;
private:
    const std::string name;

};


class LengthRecommenderUser : public User {
public:
    LengthRecommenderUser(const std::string& name);
    LengthRecommenderUser* clone();
    //LengthRecommenderUser(string,LengthRecommenderUser*);
    virtual Watchable* getRecommendation(Session& s);
    virtual string getUserRecType();
    int getAverage();
    void setAverage(int i);
    void update(int length);
    int getNumSeen();
    void setNumSeen(int i);
    void copyAcount(User* user,Session& sess);
private:
    int average;
    int numSeen;

};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser(const std::string& name);
    RerunRecommenderUser* clone();
    //RerunRecommenderUser(string,RerunRecommenderUser*);
    virtual Watchable* getRecommendation(Session& s);
    virtual string getUserRecType();
    //void update(int i);
    void copyAcount(User* user,Session& sess);
    int getNumOfRecs();
    void setNumOfRecs(int i);

private:
    int numberOfRecs;

};

class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser(const std::string& name);
    GenreRecommenderUser* clone();
    //GenreRecommenderUser(string,User*);
    virtual Watchable* getRecommendation(Session& s);
    virtual string getUserRecType();
    string getpopularTag();
    //void update(int i);
    virtual void update(int i);
    vector<pair<int,string>>& getpopGenreVector();
    void setPopGenre(vector<pair<int,string>> vec);
    void addGenreToList(string genreToAdd);
    //  void addNewGenre(string tag);
    void updateGenreList(int placeInVector);
    void copyAcount(User* user,Session& sess);

private:
    vector<pair<int,string>> popGenre;
};

#endif
