#pragma once
#include "Question.h"

class TFQuestion : public Question {
private:
	vector<string> questionInfo;
	string ans;
public:
	void setQuestionInfo(vector<string>& inpQuestion);
	vector<string> getQuestionInfo();
	void Load(ifstream& fi);
	string Show();
	int Check(vector<string>&);

	void Write(ofstream& fo);
	//void getUserAns(vector<string>&);
};