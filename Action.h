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
	ActionStatus getStatus() const;// Done
	virtual void act(Session& sess)=0;
	virtual std::string toString() const=0;
	void setStatus(ActionStatus stat);//Done
    std::string getErrorMsg();
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
	virtual void act(Session& sess);
	virtual std::string toString() const;
};

class ChangeActiveUser : public BaseAction {
public:
    ChangeActiveUser();
	virtual void act(Session& sess);
	virtual std::string toString() const;
};

class DeleteUser : public BaseAction {
public:
    DeleteUser();
	virtual void act(Session & sess);
	virtual std::string toString() const;
};


class DuplicateUser : public BaseAction {
public:
	virtual void act(Session & sess);
	virtual std::string toString() const;
};

class PrintContentList : public BaseAction {
public:
	virtual void act (Session& sess);
	virtual std::string toString() const;
};

class PrintWatchHistory : public BaseAction {
public:
	virtual void act (Session& sess);
	virtual std::string toString() const;
};


class Watch : public BaseAction {
public:
	virtual void act(Session& sess);
	virtual std::string toString() const;
};


class PrintActionsLog : public BaseAction {
public:
	virtual void act(Session& sess);
	virtual std::string toString() const;
};

class Exit : public BaseAction {
public:
	virtual void act(Session& sess);
	virtual std::string toString() const;
};
#endif
