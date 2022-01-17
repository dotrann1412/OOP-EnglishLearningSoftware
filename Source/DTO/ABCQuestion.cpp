#include "ABCQuestion.h"

void ABCQuestion::setQuestionInfo(vector<string>& inpQuestion)
{
	questionInfo = inpQuestion;
}

void ABCQuestion::setSelection(vector<string> inpSelection[])
{
	for (int i = 0; i < 4; ++i)
		selection[i] = inpSelection[i];
}

vector<string> ABCQuestion::getQuestionInfo()
{
	return questionInfo;
}

void ABCQuestion::getSelection(vector<string> buffer[])
{
	for (int i = 0; i < 4; ++i)
		buffer[i] = selection[i];
}

void ABCQuestion::Load(ifstream& fi)
{

	string tmp;

	this->questionInfo.clear();

	for (int i = 0; i < 4; ++i)
		this->selection[i].clear();

	if (!CheckMedia)
		fi.ignore();
	getline(fi, tmp);
	setIntro(tmp);

	LoadParagraph(fi);

	int nQuestion;
	fi >> nQuestion;
	while (nQuestion--) {
		int nLine;
		fi >> nLine;
		fi.ignore();
		questionInfo.push_back("");
		while (nLine--)
		{
			getline(fi, tmp);
			if (questionInfo.back() != "")
				questionInfo.back().push_back('\n');
			questionInfo.back() += tmp;
		}
		for (int i = 0; i < 4; ++i)
			getline(fi, tmp), selection[i].push_back(tmp);
		int intTmp;
		fi >> intTmp;
		ans.push_back(intTmp);
	}
}

string ABCQuestion::Show()
{
	stringstream writer;
	writer << getIntro() << '\n';
	writer << getParagraph() << '\n';
	for (int i = 0; i < questionInfo.size(); ++i)
	{	
		writer << i+1 << ": " <<  questionInfo[i] << '\n';
		for (int j = 0; j < 4; ++j)
		{
			writer << selection[j][i] << '\n';
		}
		writer << '\n';
	}
	return writer.str();
}

int ABCQuestion::Check(vector<string>& userAns)
{
	int nCorrect = 0;
	for (int i = 0; i < ans.size(); ++i)
	{
		if (i >= userAns.size())
			break;
		if (userAns[i].empty())
			continue;
		if (userAns[i][0] - 'A' == ans[i])
			++nCorrect;
	}
	return nCorrect;
}

void ABCQuestion::Write(ofstream& fo)
{
	fo << "ABC" << '\n';
	WriteSharedInfo(fo);
	fo << questionInfo.size() << '\n';
	for (int i = 0; i < questionInfo.size(); ++i)
	{
		fo << countLine(questionInfo[i]) << '\n';
		fo << questionInfo[i] << '\n';
		for (int j = 0; j < 4; ++j)
			fo << selection[j][i] << '\n';
		fo << ans[i] - '0' << '\n';
	}
}

int ABCQuestion::getSubQuestionCount() {
	return questionInfo.size();
}

string ABCQuestion::getType() {
	return Question::ABC_QUESTION;
}

vector<string> ABCQuestion::getAns() {
    vector<string> result(ans.size(), "");
	for(int i = 0, n = ans.size(); i < n; ++i)
        result[i] += ans[i] + 'A';
	return result;
}
