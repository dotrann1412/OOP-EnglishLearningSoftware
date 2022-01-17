#include "Admin.h"

#include "../BUS/TaskManagement.h"
#include "../BUS/Connection.h"
#include "../External/md5/md5.h"

#include <../External/json/json.h>

#include "../BUS/UserManagement.h"

using std::string;
using std::vector;

int Admin::s_instanceCount = 0;

Admin::Admin(string username, Json::Value data)
        : User(username, data) {

    if(!Admin::s_instanceCount)
        TaskManagement::refresh();

    this->_assigned = TaskManagement::getTask(this);
    ++Admin::s_instanceCount;
}

Admin::~Admin() {
	--Admin::s_instanceCount;

	if(this->_assigned) {
		TaskManagement::report(*_assigned);
		delete this->_assigned;
		this->_assigned = nullptr;
	}

	if(!Admin::s_instanceCount)
        TaskManagement::saveAll();
}

bool Admin::markAsDone() {
	if(!this->_assigned) return false;
    TaskManagement::recordCompletedTask(_userName, *_assigned);
    delete this->_assigned;
    this->_assigned = TaskManagement::getTask(this);
	return true;
}

Task Admin::pendingTask() {
    if(!this->_assigned)
        return Task("###", "Nothing to do", -1);
	return *this->_assigned;
}

string Admin::toString() const {
	return User::toString();
}
