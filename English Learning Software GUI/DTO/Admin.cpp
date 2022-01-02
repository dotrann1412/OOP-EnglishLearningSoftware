#include "Admin.h"

#include "../BUS/Connection.h"
#include "../External/md5/md5.h"

#include <json/json.h>

#include "../BUS/UserManagement.h"

std::priority_queue<Task>* Admin::ks_task_list = nullptr;
const std::string Admin::ks_admin_task_list_database_path = "../Data/UserData/AdminTaskList.json";
int Admin::s_instanceCount = 0;

Admin::Admin(std::string _id, std::string _userName, std::string _password, 
		std::string _name, std::string _phoneNumber, std::string _email, 
        Date _date, bool _gender, int _role, std::vector<std::string> _courseslist)
        : User(_id, _userName, _password, _name, _phoneNumber, _email, _date, _gender, _role, _courseslist) {

    if(!Admin::s_instanceCount)
        Admin::initializeTaskList();

	if(!Admin::ks_task_list->empty())
		this->_assigned = new Task(Admin::ks_task_list->top()),
        Admin::ks_task_list->pop();
		
    ++Admin::s_instanceCount;
}

// for development
Admin::Admin()
: User("hehe", "hehe") {
    this->_role = User::ADMIN;
	if(!Admin::s_instanceCount)
		Admin::initializeTaskList();

	if(!Admin::ks_task_list->empty())
		this->_assigned = new Task(Admin::ks_task_list->top()),
		Admin::ks_task_list->pop();
		
    ++Admin::s_instanceCount;
}

Admin::~Admin() {
	--Admin::s_instanceCount;

	if(this->_assigned) {
		Admin::ks_task_list->push(*this->_assigned);
		delete this->_assigned;
		this->_assigned = nullptr;
	}

	if(!Admin::s_instanceCount)
        Admin::endSession();
}

void Admin::initializeTaskList() {
	Json::Value data;
	std::ifstream fileIn = Connection::binFileReader(Admin::ks_admin_task_list_database_path);
	fileIn >> data;
	fileIn.close();

	Admin::ks_task_list = new priority_queue<Task>();
	for(const auto& x: data["undone"])
		Admin::ks_task_list->push(Task(x["id"].asString(), 
			x["message"].asString(), x["priority"].asInt()));
}

void Admin::endSession() {
	Json::Value data;
	std::ifstream fileIn = Connection::binFileReader(Admin::ks_admin_task_list_database_path);
	fileIn >> data;
	fileIn.close();

	data["undone"] = Json::Value(Json::arrayValue);

	for(int iter = 0; !Admin::ks_task_list->empty(); ++iter) {
		Json::Value value;
		Task task = Admin::ks_task_list->top();

		value["id"] = task.getTaskId();
		value["message"] = task.getMessage();
		value["priority"] = task.getPriority();

		data["undone"][iter] = value;
		Admin::ks_task_list->pop();
	}

	delete Admin::ks_task_list;
    Admin::ks_task_list = nullptr;

	std::ofstream fileOut = Connection::binFileWriter(Admin::ks_admin_task_list_database_path);
	fileOut << data;
	fileOut.close();
}

bool Admin::markAsDone() {
	if(!this->_assigned) return false;

	Json::Value data;
	std::ifstream fileIn = Connection::binFileReader(Admin::ks_admin_task_list_database_path);
	fileIn >> data;
	fileIn.close();

	Json::Value value;
	value["id"] = this->_assigned->getTaskId();
	value["message"] = this->_assigned->getMessage();
	value["priority"] = this->_assigned->getPriority();
	value["who"] = this->_userName;

	delete this->_assigned;
	this->_assigned = nullptr;

	data["done"][data["done"].size()] = value;

	std::ofstream fileOut = Connection::binFileWriter(Admin::ks_admin_task_list_database_path);
	fileOut << data;
	fileOut.close();
	return true;
}

Task Admin::pendingTask() {
	if(!this->_assigned) return Task("###", "Nothing to do", -1);
	return *this->_assigned;
}

bool Admin::setRole(const string& password, const std::string& id, int role) {
	return false;
}

bool Admin::removeAccount(const std::string& password, const std::string& id) {
	return false;
}

bool Admin::addNewTask(const Task& newtask) {
	Admin::ks_task_list->push(newtask);
	return true;
}

std::vector<Task> Admin::exactTaskList() {
	vector<Task> result;
	while(!Admin::ks_task_list->empty())
		result.push_back(Admin::ks_task_list->top()),
		Admin::ks_task_list->pop();
	
	for(const auto& x: result)
		Admin::ks_task_list->push(x);

	return result;
}

std::string Admin::toString() const {
	return User::toString();
}

#include <iostream>


Admin* Admin::getInstance(std::string username, std::string password) {
	Json::Value data = User::getData();

	password = md5(password);
    if(data == Json::nullValue
        || data[username] == Json::nullValue
		|| data[username]["password"].asString() != password) 
		return nullptr;

	data = data[username];

	std::vector<std::string> courses;
	for(const auto& x: data["courses"])
		courses.push_back(x.asString());

	return new Admin (
		data["id"].asString(), 
		username, 
		password, 
		data["name"].asString(), 
		data["phone_number"].asString(), 
		data["email"].asString(), 
		data["date_of_birth"].asString(), 
		data["gender"].asBool(), 
		data["role"].asInt(),
		courses
	);
}
