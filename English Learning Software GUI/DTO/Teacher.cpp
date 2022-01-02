#include "Teacher.h"

#include "../External/md5/md5.h"
#include "../BUS/UserManagement.h"

#include <algorithm>

Teacher::Teacher(std::string _id, std::string _userName, std::string _password, 
		std::string _name, std::string _phoneNumber, std::string _email, 
		Date _date, bool _gender, int _role, std::vector<std::string> _courseslist,
		std::vector<std::string> _coursesAdded)
	: User(_id, _userName, _password, _name, _phoneNumber, _email, _date, _gender, _role, _courseslist) {

	this->_coursesAdded.assign(_coursesAdded.begin(), _coursesAdded.end());
	
	std::sort(this->_coursesAdded.begin(), this->_coursesAdded.end());

	this->_coursesAdded.resize(
		std::unique(this->_coursesAdded.begin(), this->_coursesAdded.end()) 
		- this->_coursesAdded.begin());
}

Teacher::~Teacher() {

}

std::vector<std::string> Teacher::getCoursesAddedList() {
	return std::vector<std::string>();
}

std::string Teacher::toString() {
	return "";
}

void Teacher::add(std::string id) {

}

void Teacher::save() {
	User::save();

	Json::Value data = User::getData();

	data[this->_userName]["courses_added"] = Json::Value(Json::arrayValue);
	for(int i = 0; i < this->_courses.size(); ++i)
		data[this->_userName]["courses_added"][i] = this->_coursesAdded[i];

	User::updateData(data);
}

void Teacher::report(std::string) {

}

std::ostream& operator << (std::ostream& s, const Teacher& a) {
	return s;
}

Teacher* Teacher::getInstance(std::string username, std::string password) {
	Json::Value data = User::getData();

	password = md5(password);
	if(data == "null" 
        || data[username] == Json::nullValue
		|| data[username]["password"].asString() != password) 
		return nullptr;

	data = data[username];

	std::vector<std::string> courses;
	for(const auto& x: data["courses"])
		courses.push_back(x.asString());

	std::vector<std::string> courses_added;
	for(const auto& x: data["courses_added"])
		courses.push_back(x.asString());

	return new Teacher (
		data["id"].asString(), 
		username, 
		password, 
		data["name"].asString(), 
		data["phone_number"].asString(), 
		data["email"].asString(), 
		data["date_of_birth"].asString(), 
		data["gender"].asBool(), 
		data["role"].asInt(), 
		courses, 
		courses_added 
	);
}
