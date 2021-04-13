#include <iostream>
#include "Action.h"
#include <Session.h>
#include <User.h>
using namespace std;

BaseAction::BaseAction(): errorMsg(""), status(PENDING) {//BaseAction constructor

}

BaseAction::~BaseAction() {}

BaseAction::BaseAction(const BaseAction &action):errorMsg(action.getErrorMsg()),status(action.getStatus()) {    //copyConst

}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::setErrorMsg(string error) {
    errorMsg=error;
}

void BaseAction::setStatus(ActionStatus stat) {
    status=stat;

}


void BaseAction::complete() {
    status=COMPLETED;

}

void BaseAction::error(const std::string &errorMsg) {
    status=ERROR;
    cout<<errorMsg<<endl;
}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}


//====================CreateUser================
CreateUser::CreateUser() {
    setErrorMsg("Unable to create a new user");
}

CreateUser::~CreateUser() {}

CreateUser* CreateUser::clone() {
    CreateUser* ac1= new CreateUser();
    ac1->setStatus(this->getStatus());
    ac1->setErrorMsg(this->getErrorMsg());
    return ac1;
}

string CreateUser::toString() const {
    string toReturn;
    if(getStatus()==COMPLETED){
        toReturn = "CreateUser COMPLETED";
    }
    else{
        string str = getErrorMsg();
        toReturn = "CreateUser ERROR: "+str;
    }
    return toReturn;
}


void CreateUser::act(Session &sess) {
    if (sess.getVectorOfWords().size() != 3) {
        string err = getErrorMsg();
        error(err);
        sess.pushToActionLog(this);
    }
    else{
        User *requestedUser = sess.searchUser(
                sess.getVectorOfWords()[1]);   //return pointer to user with the same name or null if no such element exists
        if (requestedUser == nullptr) {    //this is a legal name

            if (sess.getVectorOfWords()[2] == "gen") {    //creat
                GenreRecommenderUser *addingUser = new GenreRecommenderUser(sess.getVectorOfWords()[1]);
                sess.AddNewUserToMap(sess.getVectorOfWords()[1], addingUser);  //TODO
                complete();
                sess.pushToActionLog(this);

            } else if (sess.getVectorOfWords()[2] == "rer") {
                RerunRecommenderUser *addingUser = new RerunRecommenderUser(sess.getVectorOfWords()[1]);
                sess.AddNewUserToMap(sess.getVectorOfWords()[1], addingUser);
                complete();
                sess.pushToActionLog(this);
            } else if (sess.getVectorOfWords()[2] == "len") {
                LengthRecommenderUser *addingUser = new LengthRecommenderUser(sess.getVectorOfWords()[1]);
                sess.AddNewUserToMap(sess.getVectorOfWords()[1], addingUser);
                complete();
                sess.pushToActionLog(this);
            }
            else{
                string err = getErrorMsg();
                error(err);
                sess.pushToActionLog(this);
            }
        }
        else{
            string err = getErrorMsg();
            error(err);
            sess.pushToActionLog(this);
        }
    }
}


//=======ChangeActiveUser
ChangeActiveUser::ChangeActiveUser() {
    BaseAction::setErrorMsg("Unable to change user");
}

ChangeActiveUser::~ChangeActiveUser() {}

void ChangeActiveUser::act(Session &sess) {
    string input = sess.getUserChange();
    if(sess.getVectorOfWords().size()==2) {
        User *requestedUser = sess.searchUser(
                sess.getVectorOfWords()[1]);   //return pointer to user with the same name or null if no such element exists

        if (requestedUser != nullptr) {    //this is a legal name
            sess.setActiveUser(requestedUser);
            complete();
            sess.pushToActionLog(this);
        }
    }
    if(getStatus()!=COMPLETED){
        string err = getErrorMsg();
        error(err);
        sess.pushToActionLog(this);
    }
}


string ChangeActiveUser::toString() const {
    string toReturn;
    if(getStatus()==COMPLETED){
        toReturn = "ChangeActiveUser COMPLETED";
    }
    else{
        string str = getErrorMsg();
        toReturn = "ChangeActiveUser ERROR: "+str;
    }


    return toReturn;
}

ChangeActiveUser *ChangeActiveUser::clone() {
    ChangeActiveUser *ac1 = new ChangeActiveUser();
    ac1->setStatus(this->getStatus());
    ac1->setErrorMsg(this->getErrorMsg());
    return ac1;
}


//DeleteUser

DeleteUser::DeleteUser(){// constructor
    BaseAction::setErrorMsg("Unable to delete the user");
    setStatus(PENDING);
}

DeleteUser::~DeleteUser() {}

void DeleteUser::act(Session &sess) {
    if (sess.getVectorOfWords().size() == 2) {
        string userName = sess.getVectorOfWords()[1];//username we want to delete
        User *userTemp = sess.searchUser(userName);
        if (userTemp == nullptr) {
            setStatus(ERROR);
            // delete userTemp;
            cout << "ERROR" << endl;

        } else {
            delete &(*userTemp);
            sess.getUserMap().erase(userName);
            complete();
        }
        sess.setNeedToDelete("");
        sess.pushToActionLog(this);
    }
    if(getStatus()==PENDING){
        setStatus(ERROR);
        sess.pushToActionLog(this);
        cout<<this->toString()<<endl;
    }
}
string DeleteUser::toString() const {
    string toReturn;
    if(getStatus()==COMPLETED){
        toReturn = "DeleteUser COMPLETED";
    }
    else{
        toReturn = "DeleteUser ERROR: "+getErrorMsg();
    }
    return toReturn;
}

DeleteUser *DeleteUser::clone() {
    DeleteUser *ac1 = new DeleteUser();
    ac1->setStatus(this->getStatus());
    ac1->setErrorMsg(this->getErrorMsg());
    return ac1;
}



//PrintContentList==========

PrintContentList::PrintContentList(){
    BaseAction::setErrorMsg("Unable to print the content list");
    setStatus(PENDING);
}

PrintContentList::~PrintContentList() {}

void PrintContentList::act(Session &sess) {
    vector<Watchable *> &printer = sess.getContentVector();
    if (sess.getVectorOfWords().size() != 1) {
        setStatus(ERROR);
        sess.pushToActionLog(this);
        cout << this->toString() << endl;
    } else {
        for (unsigned i = 0; i < printer.size(); i++) {
            Watchable *m1 = printer.at(i);
            string toPrint = m1->toString();
            cout << toPrint << endl;
        }
        complete();
        sess.pushToActionLog(this);
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

PrintContentList *PrintContentList::clone() {
    PrintContentList *ac1 = new PrintContentList();
    ac1->setStatus(this->getStatus());
    ac1->setErrorMsg(this->getErrorMsg());
    return ac1;
}


//PrintActionsLog======================

PrintActionsLog::PrintActionsLog(){
    BaseAction::setErrorMsg("Unable to print the action log");
    setStatus(PENDING);

}

PrintActionsLog::~PrintActionsLog() {}

void PrintActionsLog::act(Session &sess){
    if(sess.getVectorOfWords().size() == 1) {
        vector<BaseAction *> v1 = sess.getActionsLog();
        for (vector<BaseAction *>::reverse_iterator i = v1.rbegin();
             i != v1.rend(); ++i) {
            BaseAction *action1 = *i;
            string toPrint = action1->toString();
            cout << toPrint << endl;
        }
        complete();
        sess.pushToActionLog(this);
    }
    else{
        setStatus(ERROR);
        sess.pushToActionLog(this);
        cout<<this->toString()<<endl;
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


PrintActionsLog *PrintActionsLog::clone() {
    PrintActionsLog *ac1 = new PrintActionsLog();
    ac1->setStatus(this->getStatus());
    ac1->setErrorMsg(this->getErrorMsg());
    return ac1;
}

//PrintWatchHistory======================================================

PrintWatchHistory::PrintWatchHistory() {
    BaseAction::setErrorMsg("Unable to print the watch history");
    setStatus(PENDING);
}

PrintWatchHistory::~PrintWatchHistory() {}

void PrintWatchHistory::act(Session &sess) {
    if(sess.getVectorOfWords().size() == 1) {
        User *tmp = sess.getActiveUser();

        cout << "Watch history for " << tmp->getName() << ":" << endl;
        vector<Watchable *> v2 = tmp->get_history();
        int i = 0;
        for (unsigned j = 0; j < v2.size(); j++) {
            cout << to_string(i+1) + ". " << v2.at(i)->toString2() << endl;
            i++;
        }
        complete();
        sess.pushToActionLog(this);
    }
    else{
        setStatus(ERROR);
        sess.pushToActionLog(this);
        cout<<this->toString()<<endl;
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


PrintWatchHistory *PrintWatchHistory::clone() {
    PrintWatchHistory *ac1 = new PrintWatchHistory();
    ac1->setStatus(this->getStatus());
    ac1->setErrorMsg(this->getErrorMsg());
    return ac1;
}




//====================!!!!!!!!!!!!WATCH!!!!!!!!!========================

Watch::Watch() {
    BaseAction::setErrorMsg("illegal id content");
    setStatus(PENDING);
}

Watch::~Watch() {}

void Watch::act(Session &sess) {
    unsigned ourId = sess.getNeedToWatchId();//TODO CHECK THE INT ARGUMENT
    vector<Watchable *> vcontent = sess.getContentVector();
    if (vcontent.size() < ourId || ourId < 0) {
        setStatus(ERROR);
        string error = "There is no such content number";//TODO GETERRORMSG
        cout << error << endl;
    } else {
        User *user = sess.getActiveUser();
        vector<Watchable *> &v1 = user->get_history();
        Watchable *cont6 = vcontent.at(ourId-1);
        v1.push_back(cont6);
        complete();
        int length = cont6->getLength();
        user->update(length);
        cout << "Watching " << cont6->toString2() << endl;
    }
    sess.pushToActionLog(this);
    if (this->getStatus() == COMPLETED) {
        Watchable *cont3 = vcontent.at(ourId-1);
        Watchable *cont = cont3->getNextWatchable(sess);
        if (cont != nullptr) {
            string input;
            cout << "We recommend watching " << cont->toString2() << " continue watching? [y/n]" << endl;
            while (input != "y" || input != "n") {
                getline(cin, input);
                if (input == "y") {
                    long id = cont->getId();
                    sess.setNeedToWatchId(id);
                    Watch *ac1 = new Watch();
                    ac1->act(sess);
                }
                if (input == "n") {
                    break;
                }
                if(input!="y" && input!="n") {
                    cout << "illegal input" << endl;
                }

                break;


            }

        }
        else {
            User* user1 = sess.getActiveUser();
            Watchable *cont4 = user1->getRecommendation(sess);
            if(cont4== nullptr){
                return;
            }
            cout << "We recommend watching " << cont4->toString2() << " continue watching? [y/n]" << endl;
            string input2;
            while (input2 != "y" || input2 != "n") {
                getline(cin, input2);
                if (input2 == "y") {
                    Watch *watch2 = new Watch();
                    long id1 = cont4->getId();
                    sess.setNeedToWatchId(id1);
                    watch2->act(sess);
                }
                if (input2 == "n") {
                    break;
                }
                if(input2!="y" && input2!="n") {
                    cout << "illegal input" << endl;
                }
                break;

            }
        }
    }
}

    string Watch::toString() const {
        string toReturn;
        if (getStatus() == COMPLETED) {
            toReturn = "Watch COMPLETED";
        }
        else {
            toReturn = "Watch ERROR: " + getErrorMsg();
        }
        return toReturn;

    }


Watch *Watch::clone() {
    Watch *ac1 = new Watch();
    ac1->setStatus(this->getStatus());
    ac1->setErrorMsg(this->getErrorMsg());
    return ac1;
}

//================================DuplicateUser==================================
    DuplicateUser::DuplicateUser() {
        BaseAction::setErrorMsg("couldn't duplicate user");
        setStatus(PENDING);
}

DuplicateUser::~DuplicateUser() {}

void DuplicateUser::act(Session &sess) {
    if (sess.getVectorOfWords().size() == 3) {
        User *requestedUser = sess.searchUser(sess.getVectorOfWords()[1]);
        if (requestedUser != nullptr) {    //this is a legal name
            User *newName = sess.searchUser(sess.getVectorOfWords()[2]);

            if (newName == nullptr) {  //no user with the new name
                string userReqType = requestedUser->getUserRecType(); //string with len, rer or gen
                if (userReqType == "gen") {
                    User *newUser = new GenreRecommenderUser(sess.getVectorOfWords()[2]);
                    newUser->copyAcount(requestedUser, sess);
                } else if (userReqType == "rer") {
                    User *newUser = new RerunRecommenderUser(sess.getVectorOfWords()[2]);
                    newUser->copyAcount(requestedUser, sess);
                } else {
                    User *newUser = new LengthRecommenderUser(sess.getVectorOfWords()[2]);
                    newUser->copyAcount(requestedUser, sess);;
                }

                //TODO ADD FLAG AND ADD TO HISTORY
                complete();
                sess.pushToActionLog(this);
            }
        }
    }
    if (getStatus() == PENDING) {
        setStatus(ERROR);
        sess.pushToActionLog(this);
        cout << this->toString() << endl;
    }
}

string DuplicateUser::toString() const {
    string toReturn;
    if (getStatus() == COMPLETED) {
        toReturn = "DuplicateUser COMPLETED";
    } else {
        toReturn = "DuplicateUser ERROR: " + getErrorMsg();
    }
    return toReturn;

}

DuplicateUser *DuplicateUser::clone() {
    DuplicateUser *ac1 = new DuplicateUser();
    ac1->setStatus(this->getStatus());
    ac1->setErrorMsg(this->getErrorMsg());
    return ac1;
}

//=========================EXIT===============================================
Exit::Exit() {
    BaseAction::setErrorMsg("couldn't exit the program");
    setStatus(PENDING);
}

Exit::~Exit() {}


void Exit::act(Session &sess) {
    if(sess.getVectorOfWords().size()==1) {
        complete();
        sess.pushToActionLog(this);
    }
    else{
        setStatus(ERROR);
        sess.pushToActionLog(this);
        cout<<this->toString()<<endl;
    }
}


string Exit::toString() const {
    string toReturn;
    if (getStatus() == COMPLETED) {
        toReturn = "Exit COMPLETED";
    }
    else {
        toReturn = "Exit ERROR: " + getErrorMsg();
    }
    return toReturn;

}

Exit *Exit::clone() {
    Exit *ac1 = new Exit();
    ac1->setStatus(this->getStatus());
    ac1->setErrorMsg(this->getErrorMsg());
    return ac1;
}