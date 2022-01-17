#ifndef DATE_H
#define DATE_H

#include <string>

using namespace std;

class Date
{
private:
	int *_day, *_month, *_year;
	static std::string _monthStr[12];

private:
	void initialize();

public:
	Date();
	Date(int, int, int);
	Date(const std::string&);
	Date(const Date&);

public:
	//manipulation
	static bool isLeapYear(int year);
	static bool validate(int, int, int);
    static bool validate(string);

public:
	static int getMonth(const std::string& str);
	static std::string getMonthStr(const int& );
	static Date now();

public:
	int getDay();
	int getMonth();
	int getYear();
	std::string toString() const;

public:
	void setDay(int);
	void setMonth(int);
	void setYear(int);

public:
	~Date();

public:
	Date& operator = (const Date& another);

public:
	friend std::istream& operator >> (std::istream& s, Date&);
	friend std::ostream& operator << (std::ostream& s, const Date&);

public:
	static Date* parse(string s);
	static Date* tryParse(string s);
};

#endif
