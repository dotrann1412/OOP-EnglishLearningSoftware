#include "TaskManagement.h"

#include "Connection.h"
#include <../External/json/json.h>
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::priority_queue;
using std::string;

const string TaskManagement::KS_ADMIN_TASK_DATABASE_PATH = "../Data/UserData/AdminTaskList.json";
std::priority_queue<Task>* TaskManagement::k_penddingTask = nullptr;

void TaskManagement::refresh() {

	if(TaskManagement::k_penddingTask) {
		TaskManagement::saveAll();
		delete TaskManagement::k_penddingTask;
		TaskManagement::k_penddingTask = nullptr;
	}

    Json::Value data = TaskManagement::accessDatabase();

    TaskManagement::k_penddingTask = new priority_queue<Task>();
    for(int i = 0, n = data["undone"].size(); i < n; ++i)
        TaskManagement::k_penddingTask->push(Task(data["undone"][i]));

	// done clear for data backup when the batery off
}

void TaskManagement::report(Task task) {
    if(!TaskManagement::k_penddingTask) {
		Json::Value data = TaskManagement::accessDatabase();
		
		Json::Value value;
		value["id"] = task.getTaskId();
		value["message"] = task.getMessage();
		value["priority"] = task.getPriority();
        value["day_modify"] = task.getDayModify().toString();

		data["undone"][data["undone"].size() - 1] = value;

		TaskManagement::saveDatabase(data);
	} else {
        TaskManagement::k_penddingTask->push(task);
	}
}

void TaskManagement::saveAll() {
	Json::Value data = TaskManagement::accessDatabase();

	data["undone"] = Json::Value(Json::arrayValue);

	for(int iter = 0; !TaskManagement::k_penddingTask->empty(); ++iter) {
		Json::Value value;
		Task task = TaskManagement::k_penddingTask->top();

		value["id"] = task.getTaskId();
		value["message"] = task.getMessage();
		value["priority"] = task.getPriority();
        value["day_modify"] = task.getDayModify().toString();
		data["undone"][iter] = value;
		TaskManagement::k_penddingTask->pop();
	}

	delete TaskManagement::k_penddingTask;
    TaskManagement::k_penddingTask = nullptr;

	TaskManagement::saveDatabase(data);
}

bool TaskManagement::emptyTaskList() {
	if(!TaskManagement::k_penddingTask) return true;
	return k_penddingTask->empty();
}

Json::Value TaskManagement::accessDatabase() {
	Json::Value data;
	
	ifstream fileIn = Connection::binFileReader(TaskManagement::KS_ADMIN_TASK_DATABASE_PATH);
	fileIn >> data;
	fileIn.close();

	return data;
}

// just assign task for admin
Task* TaskManagement::getTask(User* user) {
	if(user->getRole() != User::ADMIN)
		return nullptr;

	if(TaskManagement::emptyTaskList()) 
		return nullptr;
	
	Task* task = new Task(TaskManagement::k_penddingTask->top());
	TaskManagement::k_penddingTask->pop();
	return task;
}

void TaskManagement::recordCompletedTask(std::string admin, Task completedTask) {
	Json::Value data = TaskManagement::accessDatabase();
	Json::Value node;
	
	node["who"] = admin;
    node["priority"] = completedTask.getPriority();
	node["id"] = completedTask.getTaskId();
    node["message"] = completedTask.getMessage();
	node["when"] = Date::now().toString();

	data["done"][data["done"].size() - 1] = node;

	TaskManagement::saveDatabase(data);
}

void TaskManagement::saveDatabase(Json::Value data) {
	ofstream fileOut = Connection::binFileWriter(TaskManagement::KS_ADMIN_TASK_DATABASE_PATH);
	fileOut << data;
	fileOut.close();
}
