#ifndef TF_QUESTION_H
#define TF_QUESTION_H

#include "Question.h"

// there we have a vector string of statements
// each statement, user have to choose true or false
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
    int getSubQuestionCount();
	//void getUserAns(vector<string>&);
	string getType();

	vector<string> getAns();
};

#endif
