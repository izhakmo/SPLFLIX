#include <Action.h>
#include <include/Session.h>
//
// Created by izhakmo on 20/11/2019.

BaseAction:: BaseAction():status(PENDING){}
ActionStatus BaseAction:: getStatus() const { return status;}
void BaseAction:: complete() {status=COMPLETED;}
void BaseAction:: error(const std::string &errorMsg) {}
std::string BaseAction:: getErrorMsg() const { return errorMsg;}
void BaseAction:: setStatus(ActionStatus stat){ status=stat;}

void BaseAction::setErrorMsg(string error) {
    errorMsg=error;
}

string BaseAction::printError() {
    string msg = getStatus()+" - "+getErrorMsg();
}


void CreateUser::act(Session &sess) {
    std::string input="user_name";
    std::unordered_map<std::string,User*>::const_iterator got = sess.getUserMap().find (input);
    if(got==sess.getUserMap().end()){   //userMap doesn't contain the name
        std::string input2="recommend";
        if(input2=="len"){

        }
        else if(input2=="rer"){

        }
        else if(input2=="gen"){

        }

    }   //if we got here, then we got an error
    setStatus(ERROR);

    // ChangeActiveUser

ChangeActiveUser::ChangeActiveUser() {
    BaseAction::setErrorMsg("Unable to change user");
    setStatus(PENDING);
    //To be continue
}

void ChangeActiveUser::act(Session &sess) {
    string userName;
    userName=sess.getUserChange();
    User* userTemp = sess.searchUser(userName);
    if(userTemp==nullptr){
        this->setStatus(ERROR);

        cout << printError() << endl;
    }
    else{
        sess.setActiveUser(userTemp);
        complete();
    }
    sess.setUserChange(nullptr);//NEED TO CHECK
    sess.pushToActionLog(this);//NEED TO PUSH THE ACTION LOG TO THE ACTION LOG VECTOR

}

}
    //PrintContentList==========

    PrintContentList::PrintContentList(){
    BaseAction::setErrorMsg("Unable to print the content list");
    setStatus(PENDING);
    }   

     void PrintContentList::act(Session &sess) {
        vector<Watchable *> printer = sess.getContentVector();
        int i=1;
        for (vector<Watchable *>::iterator it = printer.begin(); it != printer.end(); ++it) {
            cout << to_string(i) + ". " << *it << endl;
            i++;
        }
    }   
    string PrintContentList::toString() const {
    string toReturn;
    if(getStatus()==COMPLETED){
        toReturn = "PrintContentList COMPLETED";
    }
    else{
        toReturn = "PrintContentList ERROR: "+getErrorMsg();
    }
    return toReturn;
}   
    

////PrintActionsLog==========

PrintActionsLog::PrintActionsLog(){
    BaseAction::setErrorMsg("Unable to print the action log");
    setStatus(PENDING);
    //To be continue

}

void PrintActionsLog::act(Session &sess){
    vector<BaseAction*> v1 = sess.getActionsLog();
    for (vector<BaseAction*>::reverse_iterator i = v1.rbegin();
         i != v1.rend(); ++i ){
        BaseAction* action1 = *i;
        string toPrint = action1->toString();
        cout << toPrint << endl;
    }
}

string PrintActionsLog::toString() const {
    string toReturn;
    if(getStatus()==COMPLETED){
        toReturn = "PrintActionsLog COMPLETED";
    }
    else{
        toReturn = "PrintActionsLog ERROR: "+getErrorMsg();
    }
    return toReturn;
}
        
  //PrintWatchHistory=====================================

PrintWatchHistory::PrintWatchHistory() {
    BaseAction::setErrorMsg("Unable to print the watch history");
    setStatus(PENDING);
}

  void PrintWatchHistory::act(Session &sess) {
       User* tmp=sess.getActiveUser();

       cout<< "Watch history for "<<&tmp.getName()<<endl;
       int i=1;
       for(vector<Watchable*>::iterator it= tmp->get_history().begin();it!=tmp->get_history().end();++it){
           cout << to_string(i) + ". " << *it<<endl;
           i++;
       }
    }
string PrintWatchHistory::toString() const {
    string toReturn;
    if(getStatus()==COMPLETED){
        toReturn = "PrintWatchHistory COMPLETED";
    }
    else{
        toReturn = "PrintWatchHistory ERROR: "+getErrorMsg();
    }
    return toReturn;
}
