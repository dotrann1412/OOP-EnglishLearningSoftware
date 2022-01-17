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
#include <../External/json/json.h>

class User
{

friend class UserManagement;

protected:
	static const std::string 	ks_default_str;
	static const bool 			ks_default_gender;
	static const int 			ks_default_role;
    static const int            ks_default_id_len;

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
    int             _rating;

protected:
	std::vector<std::string> _courses;

public:
    User(std::string username, std::string password);
    User(std::string username, Json::Value data);
    User();

public:
	virtual ~User();

public:
    std::string getId() const;
    std::string getUserName() const;
    std::string getName() const;
    std::string getPhoneNumber() const;
    std::string getEmail() const;
    std::string getPassword() const;

    Date getDayOfBirth() const;
    bool getGender() const;
    int getRole() const;
    int getRating() const;
    bool isRegistered(std::string id) const;

	std::vector<std::string> getCourses();

public:
	virtual std::string toString() const;
    virtual Json::Value toJsonValue() const;

public:
	void setId(std::string _id);
	void setName(std::string _name);
    void setPhoneNumber(std::string phonenumber);
    void setPassword(std::string password);
	void setEmail(std::string);
	void setDayOfBirth(Date);
	void setGender(bool _gender);
	void setRole(int _role);
    void setRating(int rating);
	bool addCourses(std::string id);
	bool removeCourses(std::string id);
public:
	// check current password with data on database
	// if successfuly validation -> update password
	bool changePassword(std::string, std::string);

public:
	friend std::ostream& operator << (std::ostream&, const User&);
};

#endif // USER_H
