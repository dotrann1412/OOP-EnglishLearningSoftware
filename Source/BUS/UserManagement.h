#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include "../DTO/User.h"
#include "../External/md5/md5.h"

#include <string>
#include <vector>

class UserManagement
{
public:
	static const std::string ks_database_path;

private:
	UserManagement();
	~UserManagement();

public:
    static bool verify(const std::string& username,
                       const std::string& password);

public:
    static User* login(const std::string& username,
                       const std::string& password);

    static bool signUp(const std::string& username,
                       const std::string& password);

	// just get the basic information about the returned user
	static std::vector<User> userList();

public:
	// change role of an user != admin
	// because of security reason, we need to verify the administrator 
	// information before
	// level up the role for an user or kick them out the system. 
	static bool removeAccount(User* admin, const std::string adminPassword,
							  const std::string& who);

	static bool changeRole(User* admin, const std::string adminPassword,
						   const std::string& who, int newRole);

    static bool saveChange(User* user);

private:
	static Json::Value accessDatabase();
	static void saveDatabase(Json::Value);

};

#endif
