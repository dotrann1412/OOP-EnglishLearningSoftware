#include "CoursesManagement.h"

#include <../BUS/Connection.h>
#include <../BUS/Helper.h>
#include <../DTO/User.h>

#include <../External/json/json.h>
#include <queue>

using std::priority_queue;
using std::pair;

const string CoursesManagement::ks_course_database = "../Data/Courses/information.txt";
const string CoursesManagement::ks_saved_progress = "../Data/Courses/Progress.json";

vector<CourseInfo>* CoursesManagement::CourseList = nullptr;

CourseInfo::CourseInfo() {

}

vector<CourseInfo> CoursesManagement::GetSuggestionCourse(User &u,int nCourse)
{
    priority_queue<pair<int,int>>  q;
    int id = 0;
    for(auto _course: *CoursesManagement::CourseList) {
        int distance = (_course.difficulty - u.getRating());
        if(distance<0)
            distance = -distance;
        q.push(make_pair(distance, id++));
        if(q.size() > nCourse)
            q.pop();
    }

    vector<CourseInfo> ans;
    while(!q.empty()) {
        ans.push_back((*CourseList)[q.top().second]);
        q.pop();
    }

    return ans;
}

void CoursesManagement::LoadData(string path)
{
    if(CoursesManagement::CourseList) return;

    CoursesManagement::CourseList = new vector<CourseInfo>;

    ifstream fi = Connection::fileReader(path);

	int nCourse;
    fi >> nCourse;

	fi.ignore();
	CourseInfo _Course;

	while (nCourse--)
	{
		getline(fi, _Course.Modifier);
		getline(fi, _Course.name);
		fi >> _Course.difficulty;
		fi.ignore();
		getline(fi, _Course.path);

        CourseList->push_back(_Course);
	}
	fi.close();
}

void CoursesManagement::SaveData(string path)
{
    ofstream fo = Connection::fileWriter(path);
    fo << CourseList->size() << '\n';

    for (auto _Course : *CourseList)
	{
		fo << _Course.Modifier << '\n';
		fo << _Course.name << '\n';
		fo << _Course.difficulty << '\n';
		fo << _Course.path << '\n';
	}

    fo.close();
}

void CoursesManagement::AddCourse(CourseInfo _Course)
{
    CourseList->push_back(_Course);
}

void CoursesManagement::DeleteCourse(string courseName)
{
    for (int i = 0, n = CourseList->size(); i < n; ++i)
	{
        if ((*CourseList)[i].name == courseName)
		{
            Helper::_swap((*CourseList)[i], (*CourseList)[ n - 1]);
            CourseList->pop_back();
            return;
		}
	}
}

void CoursesManagement::SetNewList(vector<CourseInfo>& newList)
{
    while(CoursesManagement::CourseList->size())
        CoursesManagement::CourseList->pop_back();

    for(auto x: newList) {
        CoursesManagement::CourseList->push_back(x);
    }
}

vector<CourseInfo> CoursesManagement::GetCourseList()
{
    if(!CoursesManagement::CourseList)
        return vector<CourseInfo>();
    return *CourseList;
}

void CoursesManagement::updateCurrenScore(int val,int index)
{
    if(index >= CoursesManagement::curScore.size())
        return;
    curScore[index] = val;
}
vector<int> CoursesManagement::getCurrenScore()
{
    return CoursesManagement::curScore;
}
void CoursesManagement::resizeCurrenScore(int size)
{
    CoursesManagement::curScore.clear();
    while(size--)
        CoursesManagement::curScore.push_back(0);
}



// the progress in linear time
// user must complete test i - 1 before join i'th test
bool CoursesManagement::SaveProgress(User* user, Course* course, const vector<int>& score)
{
	if(!user || !course || !user->isRegistered(course->getName()))
		return false;

	Json::Value data;

	ifstream fileIn = Connection::binFileReader(CoursesManagement::ks_saved_progress);
	fileIn >> data;
	fileIn.close();

	if(data == Json::nullValue) 
        data = Json::Value();
	
    if(data[user->getUserName()] == Json::nullValue)
        data[user->getUserName()] = Json::Value();

    data[user->getUserName()][course->getName()] = Json::arrayValue;

	for(int i = 0, n = score.size(); i < n; ++i) {
        data[user->getUserName()][course->getName()][i] = score[i];
	}

	ofstream fileOut = Connection::binFileWriter(CoursesManagement::ks_saved_progress);
	fileOut << data;
	fileOut.close();

	return true;
}

vector<int> CoursesManagement::LoadProgress(User* user, Course* course)
{
	if(!user || !course || !user->isRegistered(course->getName())) {
		throw "Exception occurs when load progress";
	}

	vector<int> score;
	Json::Value data;
	ifstream fileIn = Connection::binFileReader(CoursesManagement::ks_saved_progress);
	fileIn >> data;
	fileIn.close();

    for(const auto& x: data[user->getUserName()][course->getName()])
		score.push_back(x.asInt());

	return score;
}
