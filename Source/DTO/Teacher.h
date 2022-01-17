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
	Teacher(std::string username, Json::Value data);
	~Teacher();

public:
	std::vector<std::string> getCoursesAddedList();
    std::string toString() const;
    Json::Value toJsonValue() const;

public:
	void addCourseAdded(std::string id);

public:
	friend std::ostream& operator << (std::ostream&, const User&);
};

#endif
