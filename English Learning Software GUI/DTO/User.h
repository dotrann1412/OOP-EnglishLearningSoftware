#ifndef USER_H
#define USER_H

// gender:
//		0: male
//		1: female

// Role:
//		0: normie
//		1: admin
//		2: teacher
//		3: owner (only one owner)

#include <string>
#include <iostream>
#include <vector>

#include "Date.h"
#include <json/json.h>

class User
{

friend class UserManagement;

protected: 
	static const std::string 	ks_default_str;
	static const bool 			ks_default_gender;
	static const int 			ks_default_role;
    static const int            ks_default_id_len;

    static const std::string ks_database_path;

public:
	static const int STUDENT = 0;
	static const int ADMIN = 1;
	static const int TEACHER = 2;

protected:
	std::string 	_id;
	std::string 	_userName;
	std::string 	_password;
	
protected:
	std::string 	_name;
	std::string 	_phoneNumber;
	std::string 	_email;
	Date 			_dayOfBirth;
	bool 			_gender;
	int 			_role;

protected:
	std::vector<std::string> _courses;

protected:
	static bool isValidPassword(std::string password);
	static Json::Value getData();
	static void updateData(const Json::Value&);

protected:
	User(std::string, std::string);
	User(std::string _id, std::string _userName, std::string _password, 
		std::string _name, std::string _phoneNumber, std::string _email, 
		Date date, bool gender, int role, std::vector<std::string> _courses);

public:
	virtual ~User();

public:
	std::string getId();
	std::string getUserName();
	std::string getName();
	std::string getPhoneNumber();
	std::string getEmail();
	Date getDayOfBirth();
	bool getGender();
	int getRole();

	std::vector<std::string> getCourses();

public:
	virtual std::string toString() const;

public:
	void setId(std::string _id);
	void setName(std::string _name);
	void setPhoneNumber(std::string);
	void setEmail(std::string);
	void setDayOfBirth(Date);
	void setGender(bool _gender);
	void setRole(int _role);
	bool addCourses(std::string id);
	bool removeCourses(std::string id);

public: //for development
	void setUserName(std::string name) {
		this->_userName = name;
	}

public:
	// check current password with data on database
	// if successfuly validation -> update password
	bool changePassword(std::string, std::string);

public:
	virtual void save();
	virtual void report(std::string);

public:
	static User* getInstance(std::string name, std::string password);

public:
	friend std::ostream& operator << (std::ostream&, const User&);
};

#endif // USER_H
