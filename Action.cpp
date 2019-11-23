#include <Action.h>
#include <include/Session.h>
//
// Created by izhakmo on 20/11/2019.

BaseAction:: BaseAction():status(PENDING){}
ActionStatus BaseAction:: getStatus() const { return status;}
void BaseAction:: complete() {status=COMPLETED;}
void BaseAction:: error(const std::string &errorMsg) {}  //TODO
std::string BaseAction:: getErrorMsg() const { return errorMsg;} //TODO
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
    if(got==sess.getUserMap().end()){   //TODO userMap doesn't contain the name
        std::string input2="recommend";
        if(input2=="len"){

        }
        else if(input2=="rer"){

        }
        else if(input2=="gen"){

        }

    }   //TODO  if we got here, then we got an error
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
//

