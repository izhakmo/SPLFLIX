#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"
#include <User.h>
#include <Watchable.h>
using namespace std;

class User;
class Watchable;

class Session{
public:
    Session(const std::string &configFilePath);
    ~Session();
    void start();
    void copy(const Session &other);
    Session& operator=(const Session &sess);    //copy assign
    Session(const Session& sess);   //copy const
    Session &operator=(Session &&sess); //move assign
    Session (Session&&ses); //move const
    User* searchUser(string name);
    unordered_map<string,User*>& getUserMap();
    //string getUserToDelete();
    string getUserChange();// Get the reqUserChange
    //void setUserChange(string user);
    void setActiveUser(User* user);
    void pushToActionLog(BaseAction *action);
    vector<Watchable*>& getContentVector();
    vector<BaseAction*>&getActionsLog();//get the actions log vector
    void setNeedToDelete(string user);//set the needToDelete field
    User* getActiveUser();
    //string getInput();
    void AddNewUserToMap(string name,User* user_ptr);
    long getNeedToWatchId();
    void setNeedToWatchId(long num);
    void useJson(const string &configFilePath);
    void AllGeners(string tag);
    vector<string> &getTagsVector();
    //string getNameCreation();
    //string getDuplicator();
    bool checkIfNumber(string num);
    vector<string>& getVectorOfWords();
    void setVectorOfWords(vector<string> vec);
    void setTagsVector(vector<string> vec);

private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
    string duplicator;
    string reqUserChange;// New field for changeUser
    string needToDelete;//New field for DeleteUser
    long needToWatchId;//the id of the content user want to watch
    vector<string> tagsVector;//All the Tags of Watchable
    string nameCreation;
    vector<string> vectorOfWords;
};
#endif