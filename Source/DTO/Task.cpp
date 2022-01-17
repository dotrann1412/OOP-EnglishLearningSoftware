#include "Task.h"

using std::string;
using std::ostream;
using std::istream;

const string Task::ks_default_str = "Undefined";

Task::Task() {
	this->_priority = Task::ks_default_priority;
	this->_taskId = Task::ks_default_str;
	this->_message = Task::ks_default_str;
	this->_dayModify = Date::now();
}

Task::Task(Json::Value data) {
    this->_priority = data["priority"].asInt();
    this->_taskId = data["id"].asString();
    this->_message = data["message"].asString();
    this->_dayModify = Date(data["day_modify"].asString());
}

// create new task -> set day for the current day
Task::Task(string _taskId, string _message, int _priority) {
	this->_priority = _priority;
	this->_taskId = _taskId;
	this->_message = _message;
	this->_dayModify = Date::now();
}

Task::Task(const Task& another) {
	this->_priority = another._priority;
	this->_taskId = another._taskId;
	this->_message = another._message;
    this->_dayModify = another._dayModify;
}

Task::~Task() {

}

bool Task::operator == (const Task& another) const {
	return this->_priority == another._priority;
}

bool Task::operator <  (const Task& another) const {
	return this->_priority > another._priority;
}

bool Task::operator >  (const Task& another) const {
	return this->_priority < another._priority;
}

bool Task::operator <= (const Task& another) const {
	return this->_priority >= another._priority;
}

bool Task::operator >= (const Task& another) const {
	return this->_priority <= another._priority;
}

void Task::setTaskMessage(string message) {
	this->_message = message;
}

void Task::setPriority(int priority) {
	this->_priority = priority;
}

int Task::getPriority() const {
	return this->_priority;
}

Date Task::getDayModify() const {
	return this->_dayModify;
}
	
string Task::getTaskId() const {
	return this->_taskId;
}

string Task::getMessage() const {
	return this->_message;
}

string Task::toString() const {
	return "{" + this->_taskId + " - " + this->_message + "}";
}

ostream& operator << (ostream & s, const Task& a) {
	return s << a.toString();
}
