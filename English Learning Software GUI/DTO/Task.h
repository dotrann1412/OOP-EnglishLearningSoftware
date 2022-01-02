#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>

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
	std::string _taskId;
	std::string _message;

public:
	Task();
	Task(std::string, std::string, int);
	Task(const Task&);
	~Task();

public:
	void setTaskMessage(std::string);
	void setPriority(int);

public:
	int getPriority();
	std::string getTaskId();
	std::string getMessage();

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