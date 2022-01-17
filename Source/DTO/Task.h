#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>

#include <../External/json/json.h>

#include "../DTO/Date.h"

// 3 levels of task priority:
//		0: important  
//		1: medium
//		2: not important

class Task
{
private:
	static const std::string ks_default_str;
	static const int ks_default_priority = 2;

private:
	int _priority;
	Date _dayModify;
	std::string _taskId;
	std::string _message;

public:
	Task();
	Task(std::string, std::string, int);
	Task(Json::Value data);
	Task(const Task&);
	~Task();

public:
	void setTaskMessage(std::string);
	void setPriority(int);
	void setTaskId();

public:
    int getPriority() const;
    std::string getTaskId() const;
    std::string getMessage() const;
    Date getDayModify() const;

public:
	std::string toString() const;

public:
	bool operator == (const Task&) const;
	bool operator <  (const Task&) const;
	bool operator >  (const Task&) const;
	bool operator <= (const Task&) const;
	bool operator >= (const Task&) const;

public:
	friend std::ostream& operator << (std::ostream & s, const Task& a);
};

#endif
