#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"
using namespace std;

class User;
class Watchable;

class Session{
public:
    Session(const std::string &configFilePath);
    ~Session();
    void start();
    std::unordered_map<std::string,User*> getUserMap();
    User* searchUser(string name);
    string getUserChange();// Get the reqUserChange
    void setUserChange(string user);
    void setActiveUser(User* user);
    void pushToActionLog(BaseAction *action);
    
    vector<Watchable*> getContentVector() ;
private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
    string reqUserChange;// New field for changeUser

};
#endif
