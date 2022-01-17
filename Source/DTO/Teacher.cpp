#include "Teacher.h"

#include "../External/md5/md5.h"
#include "../BUS/UserManagement.h"

#include <algorithm>

using std::sort;
using std::string;
using std::vector;

// this constructor is used to parse username and data of that user
// -> user objct
Teacher::Teacher(string username, Json::Value data)
    : User(username, data) {

   	for(const auto& x: data["courses"]) 
   		_coursesAdded.push_back(x.asString());

	sort(_coursesAdded.begin(), _coursesAdded.end());

	// make sure that no course appear in list more than one time
	_coursesAdded.resize(
		unique(_coursesAdded.begin(), _coursesAdded.end()) 
		- _coursesAdded.begin());
}

Teacher::~Teacher() {

}

vector<string> Teacher::getCoursesAddedList() {
    return _coursesAdded;
}

string Teacher::toString() const {
	return "";
}

ostream& operator << (ostream& s, const Teacher& a) {
    return s << a.toString();
}

Json::Value Teacher::toJsonValue() const {
	Json::Value data = User::toJsonValue();
    data["courses_added"]= Json::arrayValue;

	for(int i = 0; i < _coursesAdded.size(); ++i) {
        data["courses_added"][i] = _coursesAdded[i];
	}

	return data;
}
