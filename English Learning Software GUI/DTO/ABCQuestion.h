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
	vector<string> getQuestionInfo();
	void getSelection(vector<string> buffer[]);

	void Load(ifstream& fi);
	string Show();
	int Check(vector<string>&);

	void Write(ofstream& fo);
};