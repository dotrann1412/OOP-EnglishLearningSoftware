#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Task.h"

#include <queue>

class Admin : public User
{
private:
    static const std::string ks_admin_task_list_database_path;

private:
	static std::priority_queue<Task>* ks_task_list;
	static int s_instanceCount;

private:
	Task* _assigned;

public:
	Admin(std::string _id, std::string _userName, std::string _password, 
		std::string _name, std::string _phoneNumber, std::string _email, 
		Date _date, bool _gender, int _role, std::vector<std::string> v = std::vector<std::string>());
	
	Admin();
	
	~Admin();

private:
	static void initializeTaskList();
	static void endSession();
	static std::vector<Task> exactTaskList();
	
public:
	// change role of an user != admin
	// because of security reason, we need to verify the administrator 
	// information before
	// level up the role for an user or kick them out the system. 
	bool setRole(const std::string& password, const string& id, 
		int role = User::STUDENT);
	
	bool removeAccount(const std::string& password, 
		const std::string& id);

public:
	bool markAsDone();
	void refresh();
	Task pendingTask();

public:
	std::string toString() const;

public:
	static bool addNewTask(const Task&);

public:
	static Admin* getInstance(std::string username, std::string password);
};

#endif
