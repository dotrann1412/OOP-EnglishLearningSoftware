#include "Date.h"

#include <ctime>
#include <sstream>

#include "../BUS/StringTokenizer.h"
#include "../BUS/Helper.h"

std::string Date::_monthStr[12] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};

int Date::getMonth(const std::string& str) {
	for(int i = 0; i < 12; ++i) 
		if(Date::_monthStr[i] == str) 
			return i + 1;
	return -1;
}

std::string Date::getMonthStr(const int &month) {
	if(month < 1 || month > 12) return "none";
	return Date::_monthStr[month - 1];
}

void Date::initialize() {
	this->_month = new int(1);
	this->_year = new int(2020);
	this->_day = new int(1);
}

Date::Date() {
	this->initialize();

	std::time_t current_time = std::time(nullptr);
	std::stringstream ss;
	ss << std::ctime(&current_time);
	//[Mon Oct  2 00:59:08 2017]
	std::string cur;
	ss >> cur >> cur;
	*this->_month = Date::getMonth(Helper::toLower(cur));
	ss >> *this->_day >> cur >> *this->_year;
}

Date::Date(const std::string& dateStr) {
	this->initialize();
	Date* tmp = Date::tryParse(dateStr);
	if(tmp) {
		*this = *tmp;
	}
    delete tmp;
}

Date::Date(int year, int month, int day) {
	this->initialize();
	if(validate(year, month, day))
		*this->_year = year,
		*this->_month= month;
		*this->_day = day;
}

Date::Date(const Date& other) {
	this->initialize();
	*this->_year = *other._year,
	*this->_month= *other._month;
	*this->_day = *other._day;
}

int Date::getDay() {
	return *this->_day;
}

int Date::getMonth() {
	return *this->_month;
}

int Date::getYear() {
	return *this->_year;
}

void Date::setDay(int day) {
	if(validate(*this->_year, *this->_month, day))
		*this->_day = day;
}

void Date::setMonth(int month) {
	if(validate(*this->_year, month, *this->_day))
		*this->_month = month;
}

void Date::setYear(int year) {
	if(validate(year, *this->_month, *this->_year))
		*this->_year = year;
}

bool Date::validate(int year, int month, int day) {
	if(year < 0) return false;

	switch (month) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return day > 0 && day <= 31;
		case 4: case 6: case 9: case 11:
            return day > 0 && day <= 30;
		case 2:
            return day > 0 && day <= 28 + Date::isLeapYear(year);
		default:
			return false;
	}
	return true;
}

bool Date::validate(string s) {
    auto obj = StringTokenizer::parse(StringTokenizer::strip(s), "/");
    int yy, mm, dd;
    try {
        if(obj.size() != 3)
            throw "??";

        yy = stoi(obj[0]), mm = stoi(obj[1]), dd = stoi(obj[2]);

        if(!validate(yy, mm, dd))
            throw "??";

    } catch (const void*) {
        return false;
    }

    return true;
}

bool Date::isLeapYear(int year) {
	return !(year % 4) && (year % 100);
}

std::string Date::toString() const {
	char buf[11];
	sprintf(buf, "%.4d/%.2d/%.2d", 
		*this->_year, 
		*this->_month, 
		*this->_day);

	buf[10] = '\0';
	return std::string(buf);
}

Date::~Date() {
	delete this->_year, this->_day, this->_month;
}

Date Date::now() {
	Date date;
	return date;
}

Date& Date::operator = (const Date& another) {
	
	*this->_year = *another._year;
	*this->_month = *another._month;
	*this->_day = *another._day;

	return *this;
}

std::istream& operator >> (std::istream& s, Date& a) {
	int day, month, year;
	s >> day >> month >> year;
	if(Date::validate(day, month, year));
		*a._day = day, *a._month = month, *a._year = year;
	return s;
}

std::ostream& operator << (std::ostream& s, const Date& a){
	return s << a.toString();
}

Date* Date::parse(string s) {
	auto obj = StringTokenizer::parse(s, "/");
	return new Date(stoi(obj[2]), stoi(obj[1]), stoi(obj[0]));
}

Date* Date::tryParse(string s) {
	auto obj = StringTokenizer::parse(StringTokenizer::strip(s), "/");
	int yy, mm, dd;
	try {
		if(obj.size() != 3) 
			throw "??";
		
        yy = stoi(obj[0]), mm = stoi(obj[1]), dd = stoi(obj[2]);
		
		if(!validate(yy, mm, dd))
			throw "??";
		
	} catch (const void*) {
		return nullptr;
	}

	return new Date(yy, mm , dd);
}
