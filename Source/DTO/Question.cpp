#include "Question.h"
#include <windows.h>

const string Question::TF_QUESTION = "TF";
const string Question::ABC_QUESTION = "ABC";
const string Question::BLANK_QUESTION = "BLANK";

// convert string to wide string
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

int Question::countLine(const string source)
{
	int cnt = 0;
	for (auto x : source)
		if (x == '\n')
			++cnt;
	return cnt + 1;
}

void Question:: setParagraph(string inpParagraph,bool isImg)
{
	imgParagraph = isImg;
	paragraph = inpParagraph;
}

string Question::getParagraph()
{
	return paragraph;
}

void Question::LoadParagraph(ifstream& fi)
{
	int nLine;
	bool isImg;
	fi >> isImg;
	fi >> nLine;
	string tmp;
	string tmpParagraph = "";
	fi.ignore();
	while (nLine--)
	{
		getline(fi, tmp);
		if (tmpParagraph != "")
			tmpParagraph.push_back('\n');
		tmpParagraph += tmp;
	}
	setParagraph(tmpParagraph,isImg);
}

string Question::getQuestionType()
{
	return questionType;
}

void Question::setQuestionType(string& inpType)
{
	questionType = inpType;
}

void Question::setMediaPath(string path)
{
	mediaPath = path;
}

string Question::getMediaPath()
{
    string absPath = std::filesystem::current_path().u8string();
    while(absPath.back()!='\\')
         absPath.pop_back();
    return absPath + mediaPath;
}

void Question::setIntro(string inpIntro)
{
	intro = inpIntro;
}

string Question::getIntro()
{
	return intro;
}

// for save all the data
void Question::WriteSharedInfo(ofstream& fo)
{
	if (CheckMedia)
	{
		fo << 1 << '\n';
        fo << getMediaPath() << '\n';
	}
	else
		fo << 0 << '\n';
	if (imgParagraph)
		fo << 1 << '\n';
	else
		fo << 0 << '\n';
	fo << countLine(getParagraph()) << '\n';
	fo << getParagraph() << '\n';
}
