#include "Course.h"



void Course::setModify(string _Modifier, string _dayModify)
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
	ifstream fi;
	fi.open(path);
	if (!fi)
		cout << -1;
	getline(fi, Modifier);
	fi >> DayModify;
	fi.ignore();
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
		writer << "There're " << nTest.size() << "T ests\n";
	else
		writer << "There's " << nTest.size() << " Test\n";
	return writer.str();
}

void Course::LoadTest(Test& test, int id)
{
	if(id < 1 ||  id > nTest.size())
		return;
	ifstream fi;
	fi.open(nTest[id - 1]);
	test.Load(fi);
	fi.close();
}

void Course::Write(string path)
{
	string tmpPath =path + "\\" + name + ".txt";
	ofstream fo;
	fo.open(tmpPath);
	fo << Modifier << '\n';
	fo << DayModify << '\n';
	fo << name << '\n';
	fo << intro << '\n';
	fo << difficulty << '\n';
	fo << nTest.size() << '\n';
	for (auto t : nTest)
		fo << t << '\n';
	fo.close();
}