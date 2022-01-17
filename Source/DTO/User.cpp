#include "User.h"

#include <sstream>
#include <algorithm>

#include "../BUS/Connection.h"
#include "../BUS/UserManagement.h"
#include "../External/md5/md5.h"
#include "../BUS/Helper.h"

using std::string;
using std::vector;
using std::sort;
using std::stringstream;

const string 	User::ks_default_str = "Undefined";
const bool 		User::ks_default_gender = 0;
const int 		User::ks_default_role = 0;
const int       User::ks_default_id_len = 6;

User::User() {
	this->_userName = User::ks_default_str;
    this->_id = User::ks_default_str;
	this->_password = User::ks_default_str;
	this->_name = User::ks_default_str;
	this->_gender = User::ks_default_gender;
	this->_role = User::ks_default_role;
	this->_rating = 0;
	this->_phoneNumber = User::ks_default_str;
	this->_email = User::ks_default_str;
	this->_dayOfBirth = User::ks_default_str;
}

// because we let username as primary key
// this constructor help us to parse an json value -> user object
// if error happen with the data
// -> some field will be fill by "null" in string
User::User(string username, Json::Value data) {
	this->_userName = username;
    this->_id = data["id"].asString();
	this->_password = data["password"].asString();
	this->_name = data["name"].asString();
	this->_gender = data["gender"].asBool();
	this->_role = data["role"].asInt();
	this->_rating = data["rating"].asInt();
	this->_phoneNumber = data["phone_number"].asString();
	this->_email = data["email"].asString();
    this->_dayOfBirth = Date(data["day_of_birth"].asString());
	for(const auto& course: data["courses"])
        this->_courses.push_back(course.asString());
}

User::~User() {

}

string User::getId() const {
	return this->_id;
}

string User::getUserName() const {
	return this->_userName;
}

string User::getPassword() const {
    return this->_password;
}

string User::getName() const {
	return this->_name;
}

bool User::getGender() const {
	return this->_gender;
}

int User::getRole() const {
	return this->_role;
}

int User::getRating() const {
    return this->_rating;
}

bool User::isRegistered(string id) const {
	for (auto x: _courses) {
		if(x == id)
			return true;
	}
	return false;
}

void User::setId(string _id) {
	this->_id = _id;
}

void User::setName(string _name) {
	this->_name = _name;
}

void User::setGender(bool _gender) {
	this->_gender = _gender;
}

void User::setRole(int _role) {
	this->_role = _role;
}

void User::setRating(int rating) {
    this->_rating = rating;
}

bool User::changePassword(string oldPassword, string newPassword) {
    if(this->_password != md5(oldPassword))
        return false;

    this->_password = md5(newPassword);
    UserManagement::saveChange(this);
	return true;
}

string User::getPhoneNumber() const {
	return this->_phoneNumber;
}

string User::getEmail() const {
	return this->_email;
}

Date User::getDayOfBirth() const {
	return this->_dayOfBirth;
}

string User::toString() const{
	stringstream ss;

	ss << "{" 
		<< this->_id << ", " 
		<< this->_name << ", "
		<< (this->_gender ? "female" : "male") << ", "
		<< (this->_role == 0 ? "normie" : "admin")
		<< "}";

	return ss.str();
}

void User::setPhoneNumber(string phoneNumber) {
	this->_phoneNumber = phoneNumber;
}

void User::setEmail(string email) {
	this->_email = email;
}

void User::setDayOfBirth(Date dayOfBirth) {
	this->_dayOfBirth = dayOfBirth;
}

ostream& operator << (ostream& s, const User& user) {
	return s << user.toString();
}

bool User::addCourses(string id) {
    for(const auto& x: this->_courses) {
        if(x == id) return false;
    }

	this->_courses.push_back(id);
	return true;
}

vector<string> User::getCourses() {
	return this->_courses;
}

bool User::removeCourses(string id) {
    for(int i = 0, n = this->_courses.size();i < n; ++i){
		if(this->_courses[i] == id) {
			swap(this->_courses[i], this->_courses[this->_courses.size() - 1]);
			this->_courses.pop_back();
			return true;
		}
	}
	return false;
}

Json::Value User::toJsonValue() const {
    Json::Value data;
    data["courses"] = Json::arrayValue;

    for(int i = 0; i < _courses.size(); ++i) {
        data["courses"][i] = _courses[i];
    }

    data["day_of birth"] = _dayOfBirth.toString();
    data["email"] = _email;
    data["gender"] = _gender;
    data["id"] = _id;
    data["name"] = _name;
    data["password"] = _password;
    data["phone_number"] = _phoneNumber;
    data["rating"] = _rating;
    data["role"] = _role;

    return data;
}
