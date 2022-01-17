#ifndef COURSES_MANAGEMENT_H
#define COURSES_MANAGEMENT_H

#include <string>
#include <vector>
#include <fstream>
#include <../DTO/Course.h>
#include <../DTO/User.h>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;


// for the advertise
struct CourseInfo
{
	string Modifier;
	string name;
	int difficulty;

    // path to load full course information from database
	string path;
    CourseInfo();
};

class CoursesManagement 
{
private:
    static const string ks_course_database;
    static const string ks_saved_progress;

private:
    static vector<CourseInfo>* CourseList;
    static vector<int> curScore;

public:
    static void LoadData(string path = ks_course_database);
    static void SaveData(string path = ks_course_database);

    static void AddCourse(CourseInfo _Course);
    static void DeleteCourse(string courseName);
    static void SetNewList(vector<CourseInfo>& newList);
    static vector<CourseInfo> GetCourseList();
    static vector<CourseInfo> GetSuggestionCourse(User& u, int nCourse);

    static void updateCurrenScore(int val,int index);
    static vector<int> getCurrenScore();
    static void resizeCurrenScore(int size);
    // the progress just save score > 0 if done or -1 undone
    static bool SaveProgress(User* user, Course* course, const vector<int>& score);
    
    // return the infomation of course progress of the given user
    static vector<int> LoadProgress(User* user, Course* course);
private:
    CoursesManagement();
    ~CoursesManagement();
};

#endif // COURSES_MANAGEMENT_H
