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

    switch (action){
        case "createuser":  //action= the first word of the input
            CreateUser();
            break;
        case "changeuser":
            ChangeActiveUser();
            break;
        case "deleteuser":
            DeleteUser();
            break;
        case "dupuser":
            DuplicateUser();
            break;
        case "content":
            PrintContentList();
            break;
        case "watchlist":
            PrintWatchHistory();
            break;
        case "watch":
            Watch();
            break;
        case "log":
            PrintActionsLog();
            break;
        case "exit":
            Exit();
            break;
        default:
            error("illegal input");
        }



}



    //====================CreateUser
//    CreateUser::CreateUser(){   //i assume we should add an input string to the baseAction class, that should contain the input to each act
//    }
     void CreateUser::act(Session &sess) {
        string delimiter=" ";
        string input=sess.getInput();
        string userNameRequest=input.substr(0,input.find(delimiter));
        string recAlgorithm=input.substr(input.find(delimiter));
        User *requestedUser=sess.searchUser(userNameRequest);   //return pointer to user with the same name or null if no such element exists
        if(requestedUser== nullptr){    //this is a legal name

            if(recAlgorithm=="gen"){    //creat
                GenreRecommenderUser *addingUser=new GenreRecommenderUser(userNameRequest);
                sess.AddNewUserToMap(userNameRequest,(*GenreRecommenderUser)addingUser);
                complete();

            }
            else if(recAlgorithm=="rer"){
                RerunRecommenderUser *addingUser=new RerunRecommenderUser(userNameRequest);
                sess.AddNewUserToMap(userNameRequest,(RerunRecommenderUser*)addingUser);
                complete();
            }
            else if(recAlgorithm=="len"){
                LengthRecommenderUser *addingUser=new LengthRecommenderUser(userNameRequest);
                sess.AddNewUserToMap(userNameRequest,(LengthRecommenderUser*)addingUser);
                complete();

            }
            else{
             error("illegal reccomandation or already existed username");
            }


        }  else{ error("illegal reccomandation or already existed username");

        }



    }


    //=======ChangeActiveUser
    void ChangeActiveUser::act(Session &sess) {
        string input = sess.getInput();
        User *requestedUser = sess.searchUser(
                input);   //return pointer to user with the same name or null if no such element exists

        if (requestedUser != nullptr) {    //this is a legal name
            sess.setActiveUser(requestedUser);
            complete();

        }
    }

    void Session::AddNewUserToMap(string name, User *user_ptr) {
    pair<string,User*> adder(name,user_ptr);
    userMap.insert(adder);
}






//===========allGenere========
vector <string,int> Session::AllGeners() {
    vector<Watchable*> allContent=getContentVector();
    vector<string,int> Allgenres;
    int i=0;
    for(vector<Watchable*>::iterator it=allContent.begin(); it!=allContent.end();++it){

        vector<string> tags;
        for(int i=0;i<tags.size();i++){
            tags.at(i);
        }
    }

}

void DuplicateUser::act(Session &sess) {
    string delimiter=" ";
    string input=sess.getInput();
    string UserToCopy=input.substr(0,input.find(delimiter));    //first word
    string NewUserName=input.substr(input.find(delimiter));     //second word
    User *requestedUser=sess.searchUser(UserToCopy);   //return pointer to user with the same name or null if no such element exists
    if(requestedUser!= nullptr){    //this is a legal name
        User *newName=sess.searchUser(NewUserName);

        if(newName== nullptr){  //no user with the new name
            string userReqType=requestedUser->getUserRecType(); //string with len, rer or gen
            if(userReqType=="gen"){
                GenreRecommenderUser CopyAcount(NewUserName,(GenreRecommenderUser*)requestedUser);
            }
            else if(userReqType=="rer"){
                RerunRecommenderUser CopyAcount(NewUserName,(RerunRecommenderUser*)requestedUser);
            }
            else{
                LengthRecommenderUser CopyAcount(NewUserName,(LengthRecommenderUser*)requestedUser);
            }
                complete();
        }
//        else{error();}
    }
//    else{error();}
