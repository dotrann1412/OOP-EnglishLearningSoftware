#ifndef COURSES_H
#define COURSES_H

#include <direct.h>

#include "Test.h"
#include "Date.h"

class Course {
private:
	string Modifier;
	Date DayModify;
	string name;
	string intro;
	int difficulty;
	vector<string> nTest;
    vector<std::pair<int, int> > TestResult;
	
public: //setter
	void setModify(string _Modifier, Date _dayModify);
	void setName(string _name);
	void setIntro(string _intro);
	void setDifficulty(int dif);
    void addTest(string path);;
    void clearTest();

public: //getter
    Date getDayModify();
    string getModifier();
    string getName();
    string getIntro();
    int getDifficulty();
    vector<string> getTest();
    string getTest(int index);

	void Load(string path);
    void LoadTest(Test&, int);
    vector<Test*> LoadTestList();
    
    void InitTestResult();
	void updateTestResult(pair<int, int> inpResult, int testID);
	pair<int, int> getTestResult(int testID);
	vector<pair<int, int> > getTestResult();

	int numOfTest();
	string Show();

    string CreateCourseDirectory(string CourseName);
    string Write();
};

#endif
