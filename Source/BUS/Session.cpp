#include "Session.h"
#include "UserManagement.h"
#include "CoursesManagement.h"

using std::string;
using std::vector;

Session *Session::_instance = nullptr;

Session::Session()
{
    CoursesManagement::LoadData();

	_userAttempt = nullptr;
    _allCourse = new vector<Course>();
    auto infoList = CoursesManagement::GetCourseList();

    for(auto x: infoList) {
        Course course;
        course.Load(x.path);
        _allCourse->push_back(course);
    }

	_userCourse = nullptr;
	_recommend = nullptr;
}

Session::~Session()
{
    this->logout();

	delete _allCourse;
	_allCourse = nullptr;
	_userAttempt = nullptr;
}

bool Session::addUserCourse(Course course) {
    this->_userCourse->push_back(course);
    return this->_userAttempt->addCourses(course.getName());
}

Session *Session::getInstance()
{
    if (!_instance)
        _instance = new Session();
    return _instance;
}

void Session::invalidate() 
{
    delete Session::_instance;
    Session::_instance = nullptr;
}

std::vector<Course> Session::getAllcourse()
{
	return *_allCourse;
}

std::vector<Course> Session::getUsercourse()
{
    if(_userCourse)
        return *_userCourse;
    return std::vector<Course>();
}

std::vector<Course> Session::getRecommend()
{
    if(_recommend)
        return *_recommend;
    return std::vector<Course>();
}

User* Session::getUserAttempt() {
    return _userAttempt;
}

bool Session::login(string username, string password)
{
    if(_userAttempt)
        return false;

    _userAttempt = UserManagement::login(username, password);

    if(!_userAttempt)
        return false;

    _userCourse = new vector<Course>();
    _recommend = new vector<Course>();

    vector<CourseInfo> suggest = CoursesManagement::GetSuggestionCourse(*_userAttempt, 4);
    for(const auto& x: suggest) {
        Course course;
        course.Load(x.path);
        _recommend->push_back(course);
    }

    auto uid = _userAttempt->getCourses();

    for(const auto& x: uid) {
        Course course;
        course.Load("../Data/Courses/" + x + "/course.txt");
        this->_userCourse->push_back(course);
    }

    return true;
}

void Session::logout()
{
	if (_userAttempt)
	{
        UserManagement::saveChange(_userAttempt);

		delete _userAttempt;
		delete _recommend;
		delete _userCourse;

		_userCourse = _recommend = nullptr;
		_userAttempt = nullptr;
    }
}
