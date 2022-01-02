#include "Helper.h"

#include <cstdlib>

int Helper::parseInt(const std::string& num) {
	int res = 0;
	for(auto x: num) (res *= 10) += x - '0';
	return res;
}

std::string Helper::randomStr(int len, std::string prefix) {
    while(len--)
        prefix += rand() % 26 + 'A';
    return prefix;
}

std::string Helper::removeSpace(const std::string& s) {
	std::string result = "";
	for(int i = 0; i < s.size(); ++i)
		if(s[i] != ' ' && s[i] != '\t') result += s[i]; 
	return result;
}

std::string Helper::toLower(const std::string& s) {
	std::string t = s;
	for(char& x: t) if(x >= 'A' && x <= 'Z') x += 32;
	return t;
}

std::string Helper::toUpper(const std::string& s) {
	std::string res(s);
	for(auto& x: res) 
		if(x <= 'z' && x >= 'a') x -= 32;
	return res;
}
