#ifndef TASK_MANAGEMENT_H
#define TASK_MANAGEMENT_H

#include <queue>
#include <string>

#include "../DTO/Admin.h"
#include "../DTO/User.h"
#include "../DTO/Task.h"

// manage task for all admin
class TaskManagement
{
private:
	static const std::string KS_ADMIN_TASK_DATABASE_PATH;

private:
	static std::priority_queue<Task> *k_penddingTask;

private:
	TaskManagement();
	~TaskManagement();

public:
	static void refresh();
	static void saveAll();

public:
	static vector<Task> taskList();
	static Task* getTask(User*);
	static void recordCompletedTask(std::string who, Task completedTask);
	// record who send the report and the message
	static void report(Task);
	static bool emptyTaskList();

private:
	static Json::Value accessDatabase();
	static void saveDatabase(Json::Value);
};

#endif