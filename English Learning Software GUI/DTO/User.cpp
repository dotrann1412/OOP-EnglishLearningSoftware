#include "User.h"

#include <sstream>
#include <algorithm>

#include "../BUS/Connection.h"
#include "../BUS/UserManagement.h"
#include "../External/md5/md5.h"
#include "../BUS/Helper.h"

const std::string 	User::ks_default_str = "Undefined";
const bool 			User::ks_default_gender = 0;
const int 			User::ks_default_role = 0;
const int           User::ks_default_id_len = 6;

const std::string User::ks_database_path = "../Data/UserData/UserData.json";

bool User::isValidPassword(std::string password) {
	for(auto x: password) 
		if(x == ' ' || x == '\t') 
			return false;
	return true;
}

// this constructors to create object with data from data base
User::User(std::string _id, std::string _userName, std::string _password, 
		std::string _name, std::string _phoneNumber, std::string _email, 
		Date _date, bool _gender, int _role, std::vector<std::string> _courses){
	
	this->_id = _id;
	this->_userName = _userName;
    this->_password = _password;
	this->_name = _name;
	this->_gender = _gender;
	this->_role = _role;
	this->_phoneNumber = _phoneNumber;
	this->_email = _email;
	this->_dayOfBirth = _date;

	this->_courses.assign(_courses.begin(), _courses.end());
	
	std::sort(this->_courses.begin(), this->_courses.end());

	this->_courses.resize(
		std::unique(this->_courses.begin(), this->_courses.end()) 
		- this->_courses.begin());
}


// this constructor for create new User
User::User(std::string uname, std::string password) {
	this->_userName = uname;
	this->_password = md5(password);
	this->_role = User::ks_default_role;

    this->_id = Helper::randomStr(User::ks_default_id_len, "US");
	this->_phoneNumber = User::ks_default_str;
	this->_email = User::ks_default_str;
	this->_name = User::ks_default_str;
	this->_dayOfBirth = Date::now();
	this->_gender = User::ks_default_gender;
	this->_courses = std::vector<std::string>();
}

User::~User() {

}

std::string User::getId() {
	return this->_id;
}

std::string User::getUserName() {
	return this->_userName;
}

std::string User::getName() {
	return this->_name;
}

bool User::getGender() {
	return this->_gender;
}

int User::getRole() {
	return this->_role;
}

void User::setId(std::string _id) {
	this->_id = _id;
}

void User::setName(std::string _name) {
	this->_name = _name;
}

void User::setGender(bool _gender) {
	this->_gender = _gender;
}

void User::setRole(int _role) {
	this->_role = _role;
}

bool User::changePassword(std::string oldPassword, std::string newPassword) {
	if(!User::isValidPassword(newPassword)
		|| !UserManagement::verify(this->_userName, oldPassword)) return false;

	Json::Value value = User::getData();
	value[this->_userName]["password"] = this->_password = md5(newPassword);
	User::updateData(value);
	return true;
}

std::string User::getPhoneNumber() {
	return this->_phoneNumber;
}

std::string User::getEmail() {
	return this->_email;
}

Date User::getDayOfBirth() {
	return this->_dayOfBirth;
}

std::string User::toString() const{
	std::stringstream ss;

	ss << "{" 
		<< this->_id << ", " 
		<< this->_name << ", "
		<< (this->_gender ? "female" : "male") << ", "
		<< (this->_role == 0 ? "normie" : "admin")
		<< "}";

	return ss.str();
}

void User::setPhoneNumber(std::string phoneNumber) {
	this->_phoneNumber = phoneNumber;
}

void User::setEmail(std::string email) {
	this->_email = email;
}

void User::setDayOfBirth(Date dayOfBirth) {
	this->_dayOfBirth = dayOfBirth;
}

std::ostream& operator << (std::ostream& s, const User& user) {
	return s << user.toString();
}

bool User::addCourses(std::string id) {
	for(auto x: this->_courses) 
		if(x == id) return false;
	this->_courses.push_back(id);
	return true;
}

std::vector<std::string> User::getCourses() {
	return this->_courses;
}

bool User::removeCourses(std::string id) {
	for(int i = 0; i < this->_courses.size(); ++i){
		if(this->_courses[i] == id) {
			swap(this->_courses[i], this->_courses[this->_courses.size() - 1]);
			this->_courses.pop_back();
			return true;
		}
	}
	return false;
}

void User::report(std::string message) {
	//send request to TaskManagement
	
}

void User::save() {
	Json::Value data = User::getData();

    if(data == Json::nullValue)
        data = Json::Value();

    if(data[this->_userName] == Json::nullValue)
        data[this->_userName] = Json::Value();

	data[this->_userName]["id"]  = this->_id;
	data[this->_userName]["password"] = this->_password;
	data[this->_userName]["name"]  = this->_name;
	data[this->_userName]["phone_number"]  = this->_phoneNumber;
	data[this->_userName]["email"] = this->_email;
	data[this->_userName]["date_of_birth"]  = this->_dayOfBirth.toString();
	data[this->_userName]["gender"] = this->_gender;
	data[this->_userName]["role"] = this->_role;
	data[this->_userName]["courses"] = Json::Value(Json::arrayValue);

	for(int i = 0; i < this->_courses.size(); ++i)
		data[this->_userName]["courses"][i] = this->_courses[i];
	
	User::updateData(data);
}

User* User::getInstance(std::string username, std::string password) {
	Json::Value data = User::getData();
	password = md5(password);
    if(data == Json::nullValue
        || data[username] == Json::nullValue
		|| data[username]["password"] != password) 
		return nullptr;

	data = data[username];

	std::vector<std::string> courses;
	for(const auto& x: data["courses"])
		courses.push_back(x.asString());

	return new User(
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

Json::Value User::getData() {
	Json::Value value;
    std::ifstream fileIn = Connection::binFileReader(User::ks_database_path);
	fileIn >> value;
	fileIn.close();
	return value;
}

void User::updateData(const Json::Value& value) {
    std::ofstream  fileOut = Connection::binFileWriter(User::ks_database_path);
	fileOut << value;
	fileOut.close();
}
