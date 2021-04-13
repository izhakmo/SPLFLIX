#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
class Watchable;
class Session;
using namespace std;

class User{
public:
    User(const std::string& name);
    User(string,User*);
    virtual ~User();
    virtual Watchable* getRecommendation(Session& s) = 0;
    std::string getName() const;
    std::vector<Watchable*> get_history() const;

    virtual string getUserRecType()=0;
protected:
    std::vector<Watchable*> history;
private:
    const std::string name;

};


class LengthRecommenderUser : public User {
public:
    LengthRecommenderUser(const std::string& name);
    LengthRecommenderUser(string,LengthRecommenderUser*);
    virtual Watchable* getRecommendation(Session& s);
    virtual string getUserRecType();
private:
    int average;
    int numSeen;

};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser(const std::string& name);
    RerunRecommenderUser(string,RerunRecommenderUser*);
    virtual Watchable* getRecommendation(Session& s);
    virtual string getUserRecType();
private:
    std::queue<Watchable*> recommendations;

};

class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser(const std::string& name);
    GenreRecommenderUser(string,GenreRecommenderUser*);
    virtual Watchable* getRecommendation(Session& s);
    virtual string getUserRecType();
private:
    vector<string,int > genre;
};

#endif
