#include "UserManagement.h"

#include <../External/json/json.h>
#include "../DTO/Admin.h"
#include "../DTO/Teacher.h"
#include "../DTO/Date.h"

#include "Connection.h"

using std::string;
using std::vector;

const std::string UserManagement::ks_database_path = "../Data/UserData/UserData.json";

bool UserManagement::verify(const string& username,
                            const string& password) {

	Json::Value data = UserManagement::accessDatabase();

    if(data == Json::nullValue || data[username] == Json::nullValue
        || data[username]["password"].asString() != md5(password)) {
         return false;
    }

	return true;
}

User* UserManagement::login(const string& username,
                            const string& password) {

    Json::Value data = UserManagement::accessDatabase();

    if(data == Json::nullValue || data[username] == Json::nullValue)
		return nullptr;

	if(md5(password) == data[username]["password"].asString()) {
        switch (data[username]["role"].asInt()) {
            case User::ADMIN:
                return new Admin(username, data[username]);
            case User::TEACHER:
                return new Teacher(username, data[username]);
            case User::STUDENT:
                return new User(username, data[username]);
        };
	}

	return nullptr;
}

bool UserManagement::signUp(const string& username,
                            const string& password) {
    Json::Value data = UserManagement::accessDatabase();

    if(data == Json::nullValue || data[username] == Json::nullValue) {

        Json::Value newUser;
        newUser["password"] = md5(password);
        newUser["role"] = User::STUDENT;

        if(data == Json::nullValue) {
            data = Json::Value();
        }

        data[username] = newUser;

        UserManagement::saveDatabase(data);
		return true;
	}

	return false;
}

vector<User> UserManagement::userList() {
    Json::Value data = UserManagement::accessDatabase();
	vector<User> list;

    for(const auto& key: data.getMemberNames()) {
        list.push_back(User(key, data[key]));
	}

	return list;
}

bool UserManagement::removeAccount(User* admin, const std::string adminPassword,
						  const std::string& who) {
    if(admin->getRole() != User::ADMIN) {
		return false;
	}

	Json::Value data = UserManagement::accessDatabase();

    if(data[who] != Json::nullValue) {
        data.removeMember(who);
        UserManagement::saveDatabase(data);
        return true;
    }

	return false;
}

bool UserManagement::changeRole(User* admin, const std::string adminPassword,
					   const std::string& who, int role) {
    if(!UserManagement::verify(admin->getUserName(), adminPassword))
		return false;

	Json::Value data = UserManagement::accessDatabase();

    if(data[who] != Json::nullValue) {
        if(data[who]["role"].asInt() == role)
            return false;

        if(role == User::STUDENT || role == User::ADMIN) {
           if(data[who]["courses"] != Json::arrayValue)
               data[who].removeMember("courses");
        } else if(role == User::TEACHER)
            data[who]["courses_added"] = Json::arrayValue;

        data[who]["role"] = role;

        UserManagement::saveDatabase(data);

        return true;
    }
	return false;
}

Json::Value UserManagement::accessDatabase() {
    Json::Value data;

    ifstream fileIn = Connection::binFileReader(UserManagement::ks_database_path);
	fileIn >> data;
	fileIn.close();

	return data;
}

void UserManagement::saveDatabase(Json::Value data) {
    ofstream fileOut = Connection::binFileWriter(UserManagement::ks_database_path);
	fileOut << data;
	fileOut.close();
}

bool UserManagement::saveChange(User* user) {
	Json::Value data = UserManagement::accessDatabase();
    if(data == Json::nullValue
            || data[user->getUserName()] == Json::nullValue)
		return false;

    data[user->getUserName()] = user->toJsonValue();
	UserManagement::saveDatabase(data);
	return true;
}
