#include "Task.h"

const std::string Task::ks_default_str = "Undefined";

Task::Task() {
	this->_priority = Task::ks_default_priority;
	this->_taskId = Task::ks_default_str;
	this->_message = Task::ks_default_str;
}

Task::Task(std::string _taskId, std::string _message, int _priority) {
	this->_priority = _priority;
	this->_taskId = _taskId;
	this->_message = _message;
}

Task::Task(const Task& another) {
	this->_priority = another._priority;
	this->_taskId = another._taskId;
	this->_message = another._message;
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

void Task::setTaskMessage(std::string message) {
	this->_message = message;
}

void Task::setPriority(int priority) {
	this->_priority = priority;
}

int Task::getPriority() const {
	return this->_priority;
}
	
std::string Task::getTaskId() const {
	return this->_taskId;
}

std::string Task::getMessage() const {
	return this->_message;
}

std::string Task::toString() const {
	return "{" + this->_taskId + " - " + this->_message + "}";
}

std::ostream& operator << (std::ostream & s, const Task& a) {
	return s << a.toString();
}
