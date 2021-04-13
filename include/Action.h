#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
using namespace std;

class Session;

enum ActionStatus{
	PENDING, COMPLETED, ERROR
};


class BaseAction{
public:
	BaseAction();//   Done?
    virtual ~BaseAction();
	virtual BaseAction* clone()=0;
	BaseAction(const BaseAction &action);
	ActionStatus getStatus() const;// Done
	virtual void act(Session& sess)=0;
	virtual std::string toString() const=0;
	void setStatus(ActionStatus stat);//Done
    //std::string getErrorMsg();
    void setErrorMsg(string error);//  Set ERROR MSG



protected:
	void complete();
	void error(const std::string& errorMsg);
    std::string getErrorMsg() const ;

private:
	std::string errorMsg;//    First field
	ActionStatus status;//     Second field
};

class CreateUser  : public BaseAction {
public:
    CreateUser();//CreateUser Constructor
    ~CreateUser();
    CreateUser* clone();
	virtual void act(Session& sess);
	virtual std::string toString() const;
};

class ChangeActiveUser : public BaseAction {
public:
    ChangeActiveUser();
    ~ChangeActiveUser();
    ChangeActiveUser* clone();
	virtual void act(Session& sess);
	virtual std::string toString() const;
};

class DeleteUser : public BaseAction {
public:
    DeleteUser();
    ~DeleteUser();
	DeleteUser* clone();
    virtual void act(Session & sess);
	virtual std::string toString() const;
};


class DuplicateUser : public BaseAction {
public:
    DuplicateUser();
    ~DuplicateUser();
    DuplicateUser* clone();
	virtual void act(Session & sess);
	virtual std::string toString() const;
};

class PrintContentList : public BaseAction {
public:
    PrintContentList();
    ~PrintContentList();
    PrintContentList* clone();
	virtual void act (Session& sess);
	virtual std::string toString() const;
};

class PrintWatchHistory : public BaseAction {
public:
    PrintWatchHistory();
    ~PrintWatchHistory();
    PrintWatchHistory* clone();
	virtual void act (Session& sess);
	virtual std::string toString() const;
};


class Watch : public BaseAction {
public:
    Watch();
    ~Watch();
    Watch* clone();
	virtual void act(Session& sess);
	virtual std::string toString() const;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    ~PrintActionsLog();
    PrintActionsLog* clone();
	virtual void act(Session& sess);
	virtual std::string toString() const;
};

class Exit : public BaseAction {
public:
    Exit();
    ~Exit();
    Exit* clone();
	virtual void act(Session& sess);
	virtual std::string toString() const;
};
#endif
