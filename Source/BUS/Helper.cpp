#include "Helper.h"

#include <cstdlib>


int Helper::parseInt(const string& num) {
	int res = 0;
	for(auto x: num) (res *= 10) += x - '0';
	return res;
}

string Helper::randomStr(int len, string prefix) {
    while(len--)
        prefix += rand() % 26 + 'A';
    return prefix;
}

string Helper::removeSpace(const string& s) {
	string result = "";
	for(int i = 0; i < s.size(); ++i)
		if(s[i] != ' ' && s[i] != '\t') result += s[i]; 
	return result;
}

string Helper::toLower(const string& s) {
	string t = s;
    for(char& x: t)
        if(x >= 'A' && x <= 'Z')
            x += 32;
	return t;
}

string Helper::toUpper(const string& s) {
	string res(s);
	for(auto& x: res) 
		if(x <= 'z' && x >= 'a') x -= 32;
	return res;
}

bool Helper::isEmailAddress(string s) {
    for(auto x: s) {
        if(!(x == '@' || x == '.' ||
            (x >= 'a' && x <= 'z') ||
            (x >= 'A' && x <= 'Z') ||
            (x >= '0' && x <= '9')))
            return false;
    }

    //support for all of theses mail server
    vector<string> vec = {
        "@gmail.com",
        "@yahoo.com",
        "@student.hcmus.edu.vn",
        "@icloud.com",
        "@fit.hcmus.edu.vn"
    };

    for(auto x: vec)
        if(s.find(x) != string::npos)
            return true;

    return false;
}

bool Helper::isPhoneNumber(string s)
{
    for(auto x: s) {
        if(!(x >= '0' && x <= '9'))
            return false;
    }
    return s.size() == 10;
}
