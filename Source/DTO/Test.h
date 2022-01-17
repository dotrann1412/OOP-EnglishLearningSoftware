#ifndef TEST_H
#define TEST_H

#pragma once

#include "BlankQuestion.h"
#include "ABCQuestion.h"
#include "TFQuestion.h"
#include <ctime>

class Test {
private:
	string name;

    // to calculate time duration
	clock_t timeStart;
	clock_t timeEnd;

    vector<Question*> order;
	int Result;
    int rating;

	void subLoad(ifstream& fi, Question*, string, bool);
public:
	void startTime();
	void endTime();
	string getTime();
	double getTimeMinute();

	string getName();
	int questionCount();

    void setRating(int val);
    int getRating();

	vector<Question*> getQuestionList();

	void Load(ifstream& fi);
	void Start();
	void OutputResult();

    int RatingChange(int UserRating, std::pair<int,int> Result);
	std::pair<int, int> CalResult(vector< vector<string> > UserAnswer);

	void WriteTest(string path);

	vector<vector<string>> getResult();

	~Test();
};
#endif // TEST_H
