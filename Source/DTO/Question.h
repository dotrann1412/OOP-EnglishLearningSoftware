#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::cin;
using std::cout;

class Question {
public:
	static const string TF_QUESTION;
	static const string ABC_QUESTION;
	static const string BLANK_QUESTION;

private:
	//Media file;
	string questionType;
	string mediaPath;
	string intro;
	string paragraph;
	
public:
	bool CheckMedia; 
	bool imgParagraph;
	
	int countLine(const string source);

	void LoadParagraph(ifstream& fi);
	void setParagraph(string inpParagraph,bool isImg);
	string getParagraph();
	
	string getQuestionType();
	void setQuestionType(string& inpType);

    void setMediaPath(string path);
    string getMediaPath();

	void setIntro(string inpIntro);
	string getIntro();
	
	void WriteSharedInfo(ofstream& fo);

	virtual void setQuestionInfo(vector<string>&) = 0;
	virtual vector<string> getQuestionInfo() = 0;
	virtual vector<string> getAns() = 0;

    virtual void Load(ifstream& fi) = 0;
    virtual string Show() = 0; // for debugging

    virtual int Check(vector<string>&) = 0;
	virtual void Write(ofstream& fo) = 0;

	virtual string getType() = 0;
};

#endif




