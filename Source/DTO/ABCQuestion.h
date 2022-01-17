//#ifndef ABC_QUESTION_H
//#define ABC_QUESTION_H

#pragma once

#include"Question.h"

class ABCQuestion :public Question {

private:
	vector<string> questionInfo;
	vector<string> selection[4];
	vector<int> ans;

public:
	void setQuestionInfo(vector<string>& inpQuestion);
	void setSelection(vector<string> inpSelection[]);
	
	void getSelection(vector<string> buffer[]);

	vector<string> getQuestionInfo();
	void Load(ifstream& fi);
	string Show();
	int Check(vector<string>&);

	void Write(ofstream& fo);

	int getSubQuestionCount();
	vector<string> getAns();

	string getType();
};

//#endif
