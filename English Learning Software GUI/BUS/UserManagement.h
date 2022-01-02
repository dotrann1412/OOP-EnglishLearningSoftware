#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include "../DTO/User.h"
#include "../External/md5/md5.h"

class UserManagement
{
public:
	//save the path from the main position of the project

private:
	UserManagement();
	~UserManagement();

public:
	static bool verify(const std::string& username, const std::string& password);
	static User* login(const std::string& username, const std::string& password);
	static bool signUp(const std::string& username, const std::string& password);
    static std::vector<User*> userList();
};

#endif
