#include <iostream>
#include "Session.h"
#include "json.hpp"
#include <fstream>
#include <Watchable.h>
#include <User.h>
#include <Action.h>
using namespace std;


//constructor
Session::Session(const std::string &configFilePath)
:content(vector<Watchable*>()),actionsLog(vector<BaseAction*>()),userMap(unordered_map<string,User*>()),activeUser(nullptr),duplicator(""),
reqUserChange(""),needToDelete(""),needToWatchId(0),
tagsVector(vector<string>()),nameCreation(""),
 vectorOfWords(vector<string>())
{
    useJson(configFilePath);
    LengthRecommenderUser* defaultUser = new LengthRecommenderUser("default");
    this->AddNewUserToMap("default",defaultUser);
    setActiveUser(defaultUser);

}

Session::~Session() {
    tagsVector.clear();
    activeUser= nullptr;
    for(auto it=userMap.begin();it!=userMap.end();++it){
        delete (it->second);
    }
    userMap.clear();
    vectorOfWords.clear();
    for(auto it=content.begin();it!=content.end();++it){
        delete(*it);
    }
    content.clear();
    for(auto it=actionsLog.begin();it!=actionsLog.end();++it){//TODO
        delete(*it);
    }
    actionsLog.clear();
}//TODO CREATE THE DESTRUCTOR


//DEEP COPY
void Session::copy(const Session &other) {

    for(auto &i: other.content){
        Watchable *newCont = i->clone();
        this->getContentVector().push_back(newCont);
    }
    for(auto &j: other.actionsLog){
        this->actionsLog.push_back(j->clone());
    }
    for(auto &k: other.userMap){
        this->userMap[k.first]=k.second->clone();
        for(auto &h: k.second->get_history()){
            long id = h->getId();
            this->userMap.at(k.first)->get_history().push_back(this->content.at(id));
        }
    }
    activeUser = userMap.find(other.activeUser->getName())->second;
}



Session::Session(const Session &sess): content(),actionsLog(),userMap(),activeUser(),duplicator(),
                                       reqUserChange(),needToDelete(),needToWatchId(),
                                       tagsVector(),nameCreation(),
                                       vectorOfWords() {
    vectorOfWords=sess.vectorOfWords;
    tagsVector=sess.tagsVector;

    for(auto & i : sess.content){      //copy contents
        Watchable *newCont = i->clone();
        this->getContentVector().push_back(newCont);
    }
    for(auto & i : sess.actionsLog){ //copy actionLogs
        BaseAction * newAct = i->clone();
        this->getActionsLog().push_back(newAct);
    }
    for(auto & it : sess.userMap){
        User* newUser = it.second->clone();
//        int userHistorySize=us
        for(auto & i : it.second->get_history()){//Copy history to the new content
            long j = i->getId();
            newUser->get_history().push_back(this->getContentVector().at(j-1));
        }
        this->AddNewUserToMap(newUser->getName(),newUser);//Add the new user to the userMap of the new Session
    }
    string userToActivate=sess.activeUser->getName();
    this->setActiveUser(this->searchUser(userToActivate));

}



Session& Session::operator=(const Session &sess) {//Copy assignment operator
    if(this==&sess){
        return *this;
    }
    delete this;
    copy(sess);
    return *this;

}

Session& Session::operator=(Session &&sess) {//Move Assignment Operator
    if(this!=&sess){
        delete this;
        content= sess.getContentVector();
        actionsLog = sess.getActionsLog();
        userMap = sess.getUserMap();
        activeUser = sess.getActiveUser();
        tagsVector=sess.getTagsVector();
        sess.content.clear();
        sess.actionsLog.clear();
        sess.userMap.clear();
        sess.activeUser = nullptr;
        sess.vectorOfWords.clear();
        sess.duplicator.clear();
        sess.reqUserChange.clear();
        sess.needToDelete.clear();
        sess.needToWatchId = 0;
        sess.tagsVector.clear();
        sess.nameCreation.clear();
    }
    return *this;
}


//JSON FUNCTION================================================

using json=nlohmann::json;

void Session:: useJson(const string &configFilePath) {
    ifstream i(configFilePath);
    json j;
    i >> j;
    string s=j.dump(1);
    i.close();
    int g=1;
    for(auto &x: j["movies"].items()){
        string name=x.value()["name"];
        int m=x.value()["length"];
        vector<string> tagsVector;
        for(auto tag:x.value()["tags"].items()){
            tagsVector.push_back(tag.value());
            this->AllGeners(tag.value());
        }
        Watchable* m1 = new Movie(g,name,m,tagsVector);
        vector<Watchable*> vcontent = this->getContentVector();
        vcontent.push_back(m1);
        this->getContentVector().push_back(m1);
        g++;
    }
    for(auto &x: j["tv_series"].items()){
        string name = x.value()["name"];
        int m = x.value()["episode_length"];
        vector<string> tagsVector;
        int numOfSea = 1;
        int numOfEpi;
        for(auto tag:x.value()["tags"].items()){
            tagsVector.push_back(tag.value());
            this->AllGeners(tag.value());
        }
        int number=0;
        number = x.value()["seasons"].size();
        int totalSeasons = number;
        for(auto &s: x.value()["seasons"].items()){
            numOfEpi = s.value();
            for(int i=1;i<=numOfEpi;i++){
                Watchable* newContent = new Episode(g,name,m,numOfSea,i,tagsVector);//NEED TO ENTER THE NEXT EPISODE ID
                if(i<numOfEpi){
                    newContent->setNextEpisodeId(g+1);
                }
                if(i==numOfEpi && numOfSea<totalSeasons){
                    newContent->setNextEpisodeId(g+1);
                }
                this->getContentVector().push_back(newContent);
                for(unsigned i=0;i<tagsVector.size();i++) {
                }
                g++;
            }
            numOfSea++;
        }

    }

}

//JSON FUNCTION ENDS HERE===============================================

User*Session::searchUser(string name) {
    unordered_map<std::string,User*> &tempMap = getUserMap();
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

unordered_map<string, User *>& Session::getUserMap() {
    return userMap;
}

string Session::getUserChange(){
    return reqUserChange;
}

void Session::setActiveUser(User *user) {
    this->activeUser=user;

}

void Session::pushToActionLog(BaseAction *action) {
    actionsLog.push_back (action);
}

vector<Watchable*>& Session::getContentVector() {
    return content;
}

vector<BaseAction*>& Session::getActionsLog() {
    return actionsLog;
}

void Session::setNeedToDelete(string user) {
    needToDelete=user;
}

long Session::getNeedToWatchId() {
    return needToWatchId;

}

void Session::setNeedToWatchId(long num) {
    needToWatchId=num;
}

User *Session::getActiveUser() {
    return activeUser;
}


void Session::start() {
    cout<<"SPLFLIX is now on!"<<endl;
    string input;
    string word = "";
    while(input!="exit") {
        getVectorOfWords().clear();
        getline(cin,input);
        for(char i : input){
            if(i==' '){
                getVectorOfWords().push_back(word);
                word="";
            }
            else{
                word=word+i;
            }
        }
        getVectorOfWords().push_back(word);
        word="";

        if (vectorOfWords[0] == "createuser") { //action= the first word of the input
            CreateUser *ac1 = new CreateUser();
            nameCreation=input;
            ac1->act(*this);
        }
        else if (vectorOfWords[0] == "changeuser") {
            ChangeActiveUser *ac1= new ChangeActiveUser();
            reqUserChange=input;
            ac1->act(*this);
        }
        else if (vectorOfWords[0] == "deleteuser") {
            DeleteUser *ac1 = new DeleteUser();
            ac1->act(*this);
        }
        else if (vectorOfWords[0] == "dupuser") {
            DuplicateUser *ac1 = new DuplicateUser();
            duplicator=input;
            ac1->act(*this);
        }

        else if (vectorOfWords[0] == "content") {
            PrintContentList *ac1=new PrintContentList();
            ac1->act(*this);
        }
        else if (vectorOfWords[0] == "watchhist") {
            PrintWatchHistory *ac1 = new PrintWatchHistory();
            ac1->act(*this);
        }

        else if (vectorOfWords[0] == "watch"){
            bool ans;
            Watch *ac1 = new Watch();
            ans = checkIfNumber(getVectorOfWords()[1]);
            if(ans== false){//NOT A NUMBER
                ac1->setStatus(ERROR);
                ac1->setErrorMsg("The input you entered is not a number");
                this->pushToActionLog(ac1);
                string toReturn = ac1->toString();
                cout<<toReturn<<endl;
            }
            else{
                setNeedToWatchId(stol(getVectorOfWords()[1]));
                ac1->act(*this);
            }
        }
        else if (vectorOfWords[0] == "log") {
            PrintActionsLog *ac1=new PrintActionsLog();
            ac1->act(*this);
        }
        else if (vectorOfWords[0] == "exit") {
            Exit *ac1 = new Exit();
            ac1->act(*this);

        }
        else {
            cout << "illegal input" << endl;//TODO ADD ERRORS

        }
        }



}







void Session::AddNewUserToMap(string name, User *user_ptr) {    //TODO ADDED, CHECK IT
    pair<string,User*> adder(name,user_ptr);
    userMap.insert(adder);
}






//===============================allGenere======================
void Session::AllGeners(string tag) {
    vector<string> &vec = this->getTagsVector();
    bool ans = false;
    for(const auto & i : vec){
        if(i==tag){
            ans = true;
        }
    }
    if(ans== false){
        vec.push_back(tag);
    }

}

vector<string>&Session::getTagsVector(){
    return tagsVector;
}

//==================checkIfNumber==============================
bool Session::checkIfNumber(string s) {
    //int i=0;
    while(s.size()>0){
        if(s[0]>='0'    &&  s[0]<='9'){
            s=s.substr(1);
        }
        else
            return false;
    }
    return true;

}

    vector<string>& Session::getVectorOfWords() { return vectorOfWords;}

    void Session::setTagsVector(vector<string> vec) {
    tagsVector.clear();
    for(const auto & i : vec){
        tagsVector.push_back(i);
    }
}

    void Session::setVectorOfWords(vector<string> i) {
    vectorOfWords.clear();
    for(const auto & x : i){
        vectorOfWords.push_back(x);
    }
}