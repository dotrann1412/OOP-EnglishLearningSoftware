#include "Course.h"

#include <../BUS/Connection.h>

void Course::setModify(string _Modifier, Date _dayModify)
{
	Modifier = _Modifier;
	DayModify = _dayModify;
}

void Course::setName(string _name)
{
	name = _name;
}

void Course::setIntro(string _intro)
{
	intro = _intro;
}

void Course::setDifficulty(int dif)
{
	difficulty = dif;
}

void Course::addTest(string path)
{
	nTest.push_back(path);
}

void Course::Load(string path)
{
    ifstream fi = Connection::fileReader(path);
	
	getline(fi, Modifier);

    string date;
    getline(fi, date);
    DayModify = Date(date);

	getline(fi, name);
	getline(fi, intro);
	fi >> difficulty;
	
	int n = 0;
	fi >> n;
	fi.ignore();
	while (n--)
	{
		string tmp;
		getline(fi, tmp);
		nTest.push_back(tmp);
	}

	fi.close();
}

Date Course::getDayModify() {
	return DayModify;
}

string Course::getModifier() {
	return Modifier;
}

string Course::getName() {
	return name;
}

string Course::getIntro() {
	return intro;
}

int Course::getDifficulty() {
	return difficulty;
}

vector<string> Course::getTest() {
	return nTest;
}

int Course::numOfTest()
{
	return nTest.size();
}

string Course::Show()
{
	stringstream writer;
	
	writer << "Modifier: " << Modifier << '\n';
	writer << "Day Modify: " << DayModify << '\n';
	writer << "Course: " << name << '\n';
	writer << intro << '\n';

	if (nTest.size() > 1)
		writer << "There're " << nTest.size() << " Tests\n";
	else
		writer << "There's " << nTest.size() << " Test\n";
	return writer.str();
}

// load test by id
void Course::LoadTest(Test& test, int id)
{
    if (id < 0 ||  id > nTest.size())
	    return;

	ifstream fi;
    fi.open(nTest[id]);
	test.Load(fi);
	fi.close();
}

vector<Test*> Course::LoadTestList() {
    vector<Test*> result;

    for(int i = 0, n = nTest.size(); i < n; ++i) {
        Test* test = new Test;
        Course::LoadTest(*test, i + 1);
        result.push_back(test);
    }

    return result;
}

string Course::CreateCourseDirectory(string CourseName)
{
    string path ="..\\Data\\Courses\\"+CourseName;
    _mkdir(path.c_str());
    path.push_back('\\');
    return path;
}

string Course::Write()
{
    string tmpPath = this->CreateCourseDirectory(this->name) + "course.txt";
	ofstream fo;
	fo.open(tmpPath);

	fo << Modifier << '\n';
	fo << DayModify.toString() << '\n';
	fo << name << '\n';
	fo << intro << '\n';
	fo << difficulty << '\n';
	fo << nTest.size() << '\n';
	
    for (auto t : nTest) {
        fo << t << '\n';
    }
	
	fo.close();
    return tmpPath;
}

string Course::getTest(int index){
	return nTest[index];
}

void Course::clearTest()
{
    nTest.clear();
}

void Course::InitTestResult()
{
    TestResult.resize(nTest.size());
    for (int i = 0; i < TestResult.size(); ++i)
        TestResult[i] = make_pair(0, 0);
}

void Course::updateTestResult(pair<int,int> inpResult, int testID)
{
    if (TestResult.empty())
        InitTestResult();

    if (testID >= TestResult.size())
        return;
    TestResult[testID] = inpResult;

}

vector<pair<int, int> > Course::getTestResult()
{
    if (TestResult.empty())
        InitTestResult();
    return TestResult;
}

pair<int, int> Course::getTestResult(int testID)
{
    if (TestResult.empty())
        InitTestResult();
    if (testID >= TestResult.size())
        return make_pair(0, 0);
    return TestResult[testID];
}
