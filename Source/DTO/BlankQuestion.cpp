#include "BlankQuestion.h"

void BlankQuestion::setQuestionInfo(vector<string>& tmp) {}
vector<string> BlankQuestion::getQuestionInfo()
{
	vector<string> tmp;
	return tmp;
}

void BlankQuestion::Load(ifstream& fi)
{
	int nLine;
	string tmp;

	ans.clear();


	if (!CheckMedia)
		fi.ignore();
	getline(fi, tmp);
	setIntro(tmp);
	LoadParagraph(fi);
	
	fi >> nLine;
	fi.ignore();
	while (nLine--)
	{
		getline(fi, tmp);
		ans.push_back(tmp);
	}
}
string BlankQuestion::Show()
{
	stringstream writer;
	writer << getIntro() << '\n';
	writer << getParagraph() << '\n';
	for (int i = 0; i < ans.size(); ++i)
	{	
		writer << i + 1 << ": " << ans[i] << '\n';
	}
	return writer.str();
}

void BlankQuestion::Fix(string& source)
{
	string tmp;
	for (auto x : source)
	{
		if (x >= 'A' && x <= 'Z')
			x = 'a' + (x - 'A');
		tmp.push_back(x);
	}
}

int BlankQuestion::Check(vector<string>& userAns)
{
	int Correct = 0;
	for (int i = 0; i < this->ans.size(); ++i)
	{
		if (i >= userAns.size())
			break;
		BlankQuestion::Fix(userAns[i]);
		if (ans[i] == userAns[i])
			++Correct;
	}
	return Correct;
}

void BlankQuestion::Write(ofstream& fo)
{
	fo << "BLANK\n";
	WriteSharedInfo(fo);
	fo << ans.size() << '\n';
	for (auto tmp : ans)
		fo << tmp << '\n';
}

string BlankQuestion::getType() {
	return Question::BLANK_QUESTION;
}

vector<string> BlankQuestion::getAns() {
	return ans;
}

int BlankQuestion::blankCount() {
    return ans.size();
}
