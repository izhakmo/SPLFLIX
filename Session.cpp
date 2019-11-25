#include <Session.h>
#include <fstream>
#include <json.hpp>
//
// Created by izhakmo on 20/11/2019.
using json=nlohmann::json ;
std::ifstream i("config1.json");
json j;
i>>j;

unordered_map<string, User *>& Session::getUserMap() {
    return userMap;
}

User*Session::searchUser(string name) {
    unordered_map<std::string,User*> tempMap = getUserMap();
    User* userPtr;
    unordered_map<std::string,User*>::const_iterator got = tempMap.find (name);
    if(got==tempMap.end()){
        userPtr = nullptr;
    }
    else{
        userPtr = got->second;
    }

    return userPtr;
}

string Session::getUserChange(){
    return reqUserChange;
}

void Session::setActiveUser(User *user) {
    this->activeUser=user;

}

void Session::setUserChange(string user) {//Change the reqUserChange
    reqUserChange=user;
}

void Session::pushToActionLog(BaseAction *action) {
    actionsLog.push_back (action);
}

vector<Watchable*> Session::getContentVector() {
    return content;
}

vector<BaseAction*> Session::getActionsLog() {
    return actionsLog;
}
string Session::getUserToDelete() {//Get the needToDelete field
    return needToDelete;
}

void Session::setNeedToDelete(string user) {
    needToDelete=user;
}

string Session::getUserToDelete() {//Get the needToDelete field
    return needToDelete;
}


void Session::start() {
    string input;
    cin >> input;
    string delimiter = " ";
    string action = input.substr(0, input.find(delimiter));        //get the first word of the action
    input = input.substr(input.find(delimiter));

    if (action == "createuser")  //action= the first word of the input
        CreateUser();
    else if (action == "changeuser")
        ChangeActiveUser();
    else if (action == "deleteuser")
        DeleteUser();
    else if (action == "dupuser")
        DuplicateUser();
    else if (action == "content")  //TODO check the delimiter func if it doesn't apear
        PrintContentList();
    else if (action == "watchlist")
        PrintWatchHistory();
    else if (action == "watch")
        Watch();
    else if (action == "log")
        PrintActionsLog();
    else if (action == "exit")
        Exit();
    else    //TODO ADD
                    

//====================CreateUser
//    CreateUser::CreateUser(){   //i assume we should add an input string to the baseAction class, that should contain the input to each act
//    }
     void CreateUser::act(Session &sess) {
        string delimiter=" ";
        string input=sess.getInput();
        string userNameRequest=input.substr(0,input.find(delimiter));
        string recAlgorithm=input.substr(input.find(delimiter));
//        unordered_map<string,User*> &map=sess.getUserMap(); //reference, probably not needed
        User *requestedUser=sess.searchUser(userNameRequest);   //return pointer to user with the same name or null if no such element exists
        if(requestedUser== nullptr){    //this is a legal name

            if(recAlgorithm=="gen"){    //creat
                GenreRecommenderUser *addingUser=new GenreRecommenderUser(userNameRequest);
                sess.getUserMap().insert(userNameRequest,*addingUser);
                complete();

            }
            else if(recAlgorithm=="rer"){
                RerunRecommenderUser *addingUser=new RerunRecommenderUser(userNameRequest);
                sess.getUserMap().insert(userNameRequest,*addingUser);
                complete();
            }
            else if(recAlgorithm=="len"){
                LengthRecommenderUser *addingUser=new LengthRecommenderUser(userNameRequest);
                sess.getUserMap().insert(userNameRequest,*addingUser);
                complete();

            }


        }  else{ error("illegal reccomandation or already existed username");

        }



    }


    //=======ChangeActiveUser
    void ChangeActiveUser::act(Session &sess) {
    string input=sess.getInput();
        User *requestedUser=sess.searchUser(input);   //return pointer to user with the same name or null if no such element exists

        if(requestedUser!= nullptr){    //this is a legal name
            sess.setActiveUser(requestedUser);  //TODO ADD FLAG FOR HISTORY AND PRINT...
            complete();
            sess.pushToActionLog()

        }
