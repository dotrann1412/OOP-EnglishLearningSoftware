#include "StringTokenizer.h"

using std::string;
using std::vector;

bool validCharacter(char x) {
	return (x >= 'A' && x <= 'Z')
	|| (x >= 'a' && x <= 'z') 
	|| (x >= '0' && x <= '9'); 
}

string StringTokenizer::strip(string s) {
	std::string result = "";

	int n  = s.size();
	
	//repace all 'tab' -> 'space'
	for(int i = 0; i < n; ++i) 
		if(s[i] == '\t') s[i] = ' ';

	int left = 0, right = n - 1;
	
	//let left is the first position with s[left] != ' ';
	while(s[left] == ' ' && left < n) left++;

	//let right is the last position with s[right] != ' ';
	while(s[right] == ' ' && right >= 0) right--;

	//then s[left..right] is not contains 'space' at begin and end
	//strip space between left and right, then assign s by the result
	//result is the string that contains words separate by only one 'space' character;
	while(left <= right) {
		if(validCharacter(s[left])) {
			if(left > 0 && s[left - 1] == ' ' 
				&& validCharacter(result.back())) 
				result += ' ';
			result += s[left];
		} else {
			if(s[left] == ' ');
			else {
				//if(validCharacter(result.back())) result += ' ';
				result += s[left];
			}
		}
		++left;
	}

	return result;
}

//split the string by separator
vector<string> StringTokenizer::parse(string s, string separator) {
	int offset = 0;
	size_t f = s.find(separator, offset);
	vector<string> result;
	while(f != string::npos) {
		result.push_back(s.substr(offset, f - offset));
		offset = f + separator.size();
		f = s.find(separator, offset);
	}
	result.push_back(s.substr(offset));
	return result;
}

string StringTokenizer::remove(string s, char dest) {
	string res = "";
	for(auto x: s) if(x != dest) res += x;
	return res;
}
