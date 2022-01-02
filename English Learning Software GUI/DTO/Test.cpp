#include "Test.h"

void Test::startTime()
{
	timeStart = clock();
}

void Test::endTime()
{
	timeEnd = clock();
}

string Test::getTime()
{
	stringstream writer;
	int tmp = (timeStart - timeEnd) / CLOCKS_PER_SEC;
	if (tmp < 0)
		tmp = 0;
	writer << tmp / 60 / 60 << ":" << tmp / 60 - (tmp / 60 / 60) * 60 << tmp % 60;
	return writer.str();
}
double Test::getTimeMinute()
{
	return (double)(1.0)*(timeStart - timeEnd) / CLOCKS_PER_SEC / 60;
}
void Test::subLoad(ifstream& fi,Question* x,string inpPath,bool AvailavleMedia)
{
	x->CheckMedia = AvailavleMedia;
	x->Load(fi);
	x->setMedia(inpPath);
	order.push_back(x);
}
void Test::Load(ifstream& fi)
{
	getline(fi, name);
	int nQ;
	fi >> nQ;
	while (nQ--)
	{
		string type;
		fi >> type;
		Question* tmp;
		ABCQuestion* x;
		BlankQuestion* xx;
		TFQuestion* xxx;
		bool AvailableMedia = false;
		string tmpFilePath;
		string tmpIntro;
		string tmpParagraph;
		bool isImgParagraph;

		fi >> AvailableMedia;

		if (AvailableMedia)
		{
			fi.ignore();
			getline(fi, tmpFilePath);
		}
		else
			tmpFilePath = "";

		if (type == "ABC")
		{
			x = new ABCQuestion;
			subLoad(fi, x, tmpFilePath, AvailableMedia);
		}else
		if(type == "BLANK")
		{
			xx = new BlankQuestion;
			subLoad(fi, xx, tmpFilePath, AvailableMedia);
		}else
		if(type == "TF")
		{
			xxx = new TFQuestion;
			subLoad(fi, xxx, tmpFilePath, AvailableMedia);
		}
	}
}
void Test::Start()
{
	cout << "Start excercising !\n";
	cout << "Thers's " << this->order.size() << " Question !\n";
	system("pause");
	vector<string> userAns;
	int i = 0;
	for (auto x : order)
	{
		++i;
		cout << "Question " << i << ": ";
		userAns.clear();
		cout << x->Show();
		//this->Result += x->Check(userAns);
	}
}
void Test::OutputResult()
{
	cout << "your score is: " << this->Result << std::endl;
}

void Test::WriteTest(string path)
{
	path += "\\" + name + ".txt";
	ofstream fo;
	fo.open(path);
	fo << order.size() << '\n';
	for (auto exercise : order)
	{
		exercise->Write(fo);
	}
	fo.close();
}

Test::~Test()
{
	for (auto exc : order)
		if (exc != nullptr)
		{
			delete exc;
			exc = nullptr;
		}
}