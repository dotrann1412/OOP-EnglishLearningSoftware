#pragma once
#include "BlankQuestion.h"
#include "ABCQuestion.h"
#include "TFQuestion.h"
#include<ctime>
class Test{
private:
	string name;
	clock_t timeStart;
	clock_t timeEnd;
	vector<Question*> order;
	int Result;

	void subLoad(ifstream& fi,Question*,string,bool);
public:
	void startTime();
	void endTime();
	string getTime();
	double getTimeMinute();

	void Load(ifstream& fi);
	void Start();
	void OutputResult();

	void WriteTest(string path);

	~Test();
};