#ifndef SESSION_H
#define SESSION_H

#include "../DTO/User.h"
#include "../DTO/Course.h"
#include "CoursesManagement.h"

#include <string>
#include <vector>

class Session
{
private:
    std::vector<Course>* _allCourse;
    std::vector<Course>* _userCourse;
    std::vector<Course>* _recommend;
    User* _userAttempt;

private:
	static Session* _instance;

private:
	Session();
	~Session();

public:
	static Session* getInstance();
	static void invalidate();

public:
	User* getUserAttempt();
	std::vector<Course> getAllcourse();

public:
    std::vector<Course> getUsercourse();
    std::vector<Course> getRecommend();
    bool addUserCourse(Course);

public:
	bool login(std::string username, std::string password);
	void logout();
};

#endif // SESSION_H
