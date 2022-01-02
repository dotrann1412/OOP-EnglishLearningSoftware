#include "Test.h"

class Course {
private:
	string Modifier;
	string DayModify;
	string name;
	string intro;
	int difficulty;
	vector<string> nTest;
	
public:
	void setModify(string _Modifier, string _dayModify);
	void setName(string _name);
	void setIntro(string _intro);
	void setDifficulty(int dif);
	void addTest(string path);
	void Load(string path);
	void LoadTest(Test&,int);
	int numOfTest();
	string Show();

	void Write(string path);
};