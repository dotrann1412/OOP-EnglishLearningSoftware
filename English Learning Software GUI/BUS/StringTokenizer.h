#ifndef STRING_TOKENIZER_H
#define STRING_TOKENIZER_H

#include <string>
#include <vector>

using namespace std;

class StringTokenizer
{
public:
	static string remove(string s, char dest);
	static string strip(string src);
	static std::vector<string> parse(string src, string separator);
};

#endif