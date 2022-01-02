#include "UserManagement.h"

#include <json/json.h>
#include "../DTO/Admin.h"
#include "../DTO/Teacher.h"

#include "Connection.h"

#include <iostream>

bool UserManagement::verify(const std::string& username, const std::string& password) {
	Json::Value value;
    std::ifstream fileIn = Connection::binFileReader(User::ks_database_path);
	fileIn >> value;
	fileIn.close();

    if(value == Json::nullValue || value[username] == Json::nullValue
		|| value[username]["password"].asString() != md5(password)) return false;

	return true;
}

User* UserManagement::login(const std::string& username, const std::string& password) {
	Json::Value value;
    std::ifstream fileIn = Connection::binFileReader(User::ks_database_path);
	fileIn >> value;
	fileIn.close();

    if(value == Json::nullValue || value[username] == Json::nullValue)
		return nullptr;

	if(md5(password) == value[username]["password"].asString()) {
		switch (value[username]["role"].asInt()) {
			case User::STUDENT:
				return User::getInstance(username, password);
			case User::TEACHER:
				return Teacher::getInstance(username, password);
			case User::ADMIN:
				return Admin::getInstance(username, password);
		}
	}

	return nullptr;
}

bool UserManagement::signUp(const std::string& username, const std::string& password) {
    Json::Value value = User::getData();

    if(value == Json::nullValue || value[username] == Json::nullValue) {
        User* newUser = new User(username, password);
        newUser->save();
        delete newUser;
		return true;
	}

	return false;
}
