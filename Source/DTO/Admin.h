#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Task.h"

class Admin : public User
{
private:
	static int s_instanceCount;

private:
	Task* _assigned;

public:
	Admin(std::string username, Json::Value data);
	Admin();
	
	~Admin();

public:
	bool markAsDone(); // auto set new task when complete
	Task pendingTask(); // return the current task

public:
	std::string toString() const;
};

#endif
