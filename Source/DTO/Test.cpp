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
    x->setMediaPath(inpPath);
	order.push_back(x);
}

string Test::getName() {
	return this->name;
}

int Test::questionCount() {
	return this->order.size();
}


void Test::setRating(int val)
{
    this->rating = val;
}
int Test::getRating()
{
    return this->rating;
}

vector<Question*> Test::getQuestionList() {
	return this->order;
}

void Test::Load(ifstream& fi)
{
	getline(fi, name);
	int nQ;
	fi >> nQ;
	while (nQ--) {
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

		if (AvailableMedia) {
			fi.ignore();
			getline(fi, tmpFilePath);
		} else
			tmpFilePath = "";

        if (type == Question::ABC_QUESTION) {
			x = new ABCQuestion;
			subLoad(fi, x, tmpFilePath, AvailableMedia);
        } else if(type == Question::BLANK_QUESTION) {
			xx = new BlankQuestion;
			subLoad(fi, xx, tmpFilePath, AvailableMedia);
        } else if(type == Question::TF_QUESTION) {
			xxx = new TFQuestion;
			subLoad(fi, xxx, tmpFilePath, AvailableMedia);
		}
	}
}

// for console application
void Test::Start()
{
	cout << "Start excercising !\n";
	cout << "Thers's " << this->order.size() << " Question !\n";
	system("pause");
	vector<string> userAns;
	int i = 0;
	for (auto x : order) {
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
    for (auto exercise : order) {
		exercise->Write(fo);
	}

	fo.close();
}

std::pair<int, int> Test::CalResult(vector< vector<string> > UserAnswer)
{
    std::pair<int, int> ans = std::make_pair(0, 0);
    for (int i = 0; i < this->order.size(); ++i)
    {
        ans.first += order[i]->Check(UserAnswer[i]);
        ans.second += UserAnswer[i].size();
    }
    return ans;
}

int Test::RatingChange(int UserRating, std::pair<int,int> Result)
{
    int distance =  this->rating - UserRating;
    double Percent = 1.0 * Result.first/ Result.second * 100;
    if(Percent < 60)
    {
        if(distance > 0 && Percent > 30)
            return 0;
        if(distance > 0)
            distance = - distance;
        return distance/2;
    }
    if(Percent < 70)
    {
        if(distance > 0)
            return distance/10; // +10% rating distance
        return distance / 2;  // -50% rating distance
    }
    if(Percent < 80)
    {
        if(distance > 0)
            return distance/5; // +20% rating distance
        return distance / 100 * 40;  // -40% rating distance
    }
    if(Percent < 90)
    {
        if(distance > 0)
            return distance/ 100 * 40; // +40% rating distance
        return distance / 100 * 30;  // -30% rating distance
    }
    if(distance > 0)
        return distance/ 100 * 50; // +50% rating distance
    return distance / 100 * 20;  // -20% rating distance
}



Test::~Test()
{
	for (auto exc : order) {
		if (exc != nullptr)
		{
			delete exc;
			exc = nullptr;
		}
	}
}

vector<vector<string>> Test::getResult() {
	vector<vector<string>> result;
	for(const auto& x: order) {
		result.push_back(x->getAns());
	}
	return result;
}
