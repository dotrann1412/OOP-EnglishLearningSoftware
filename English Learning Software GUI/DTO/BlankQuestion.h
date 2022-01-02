#pragma once
#include "Question.h"

class BlankQuestion : public Question {
private:
	vector<string> ans;
public:
	void setQuestionInfo(vector<string>&);
	vector<string> getQuestionInfo();
	void Load(ifstream& fi);
	string Show();
	int Check(vector<string>&);
	static void Fix(string&);

	void Write(ofstream& fo);
};