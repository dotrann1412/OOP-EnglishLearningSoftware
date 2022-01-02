#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<sstream>
#include<windows.h>
#include<mmsystem.h>

#pragma comment(lib, "Winmm.lib")

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::cin;
using std::cout;

class Media {
private:
	string path;
public:
	void Play();
	void setPath(string path);
};

class Question {
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
	void setMedia(string path);
	string getMedia();
	void setIntro(string inpIntro);
	string getIntro();
	
	void WriteSharedInfo(ofstream& fo);


	virtual void setQuestionInfo(vector<string>&) = 0;
	virtual vector<string> getQuestionInfo() = 0;
	virtual void Load(ifstream& fi) = 0;
	virtual string Show() = 0;
	virtual int Check(vector<string>&) = 0;
	virtual void Write(ofstream& fo) = 0;
};




