#ifndef TEACHER_H
#define TEACHER_H

#include "User.h"
#include <string>
#include <vector>

class Teacher : public User
{
private:
	std::vector<std::string> _coursesAdded;

public:
	Teacher(std::string _id, std::string _userName, std::string _password, 
		std::string _name, std::string _phoneNumber, std::string _email, 
		Date _date, bool _gender, int _role, std::vector<std::string> _courseslist,
		std::vector<std::string> _coursesAdded);

	~Teacher();

public:
	std::vector<std::string> getCoursesAddedList();
	std::string toString();

public:
	void add(std::string id);

public:
	void save(); //override
	void report(std::string); //override

public:
	friend std::ostream& operator << (std::ostream&, const User&);

public:
	static Teacher* getInstance(std::string username, std::string password);
};

#endif