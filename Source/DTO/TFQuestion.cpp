#include "TFQuestion.h"

void TFQuestion::setQuestionInfo(vector<string>& inpQuestion)
{
	questionInfo = inpQuestion;
}
vector<string> TFQuestion::getQuestionInfo()
{
	return questionInfo;
}


void TFQuestion::Load(ifstream& fi)
{
	int nLine;
	string tmp;

	setParagraph("",0);
	ans.clear();
	questionInfo.clear();

	if (!CheckMedia)
		fi.ignore();
	getline(fi, tmp);
	setIntro(tmp);
	LoadParagraph(fi);

	
	fi >> nLine;
	getline(fi, tmp);
	while (nLine--)
	{
		getline(fi, tmp);
		this->questionInfo.push_back(tmp);
	}
	getline(fi, this->ans);
}

string TFQuestion::Show()
{
	stringstream writer;
	writer << getIntro() << '\n';
	writer << getParagraph() << '\n';
	for (int i = 0; i < questionInfo.size(); ++i)
	{
		writer << questionInfo[i] << ' ' << ans[i] << '\n';
	}
	return writer.str();
}

int TFQuestion::Check(vector<string>& userAns)
{
	if (userAns.empty())
		return 0;
	int Correct = 0;
    std::cerr << "user answer: ";
    for(auto x:userAns)
        std::cerr << x << ' ';
    std:: cerr << '\n';
    std:: cerr << this->ans << '\n';
	for (int i = 0; i < this->ans.size(); ++i)
	{
        if (i >= userAns.size())
			break;
        string tmp = "";
        tmp.push_back(ans[i]);
        std:: cerr << tmp << '//' << userAns[i] << '\n';
        if (tmp == userAns[i])
			++Correct;
	}
    std::cerr << "correct: " << Correct << '\n';
	return Correct;
}

void TFQuestion::Write(ofstream& fo)
{
	fo << "TF" << '\n';
	WriteSharedInfo(fo);
	fo << questionInfo.size() << '\n';
	for (auto q : questionInfo)
		fo << q << '\n';
	fo << ans << '\n';
}

int TFQuestion::getSubQuestionCount() {
    return questionInfo.size();
}
/*
void TFQuestion::getUserAns(vector<string>& userAns)
{
	//cin.ignore();
	userAns.push_back("");
	for (int i = 0; i < this->questionInfo.size(); ++i)
	{
		cout << i + 1 << ". " << this->questionInfo[i] << "(T/F): ";
		char x;
		cin >> x;
		userAns[0].push_back(x);
	}
	getchar();
}*/

string TFQuestion::getType() {
	return Question::TF_QUESTION;
}

vector<string> TFQuestion::getAns() {
    vector<string> result(ans.size());
	for(int i = 0, n = ans.size(); i < n; ++i)
        result[i] += ans[i];
	return result;
}
