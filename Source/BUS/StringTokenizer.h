#ifndef STRING_TOKENIZER_H
#define STRING_TOKENIZER_H

#include <string>
#include <vector>

class StringTokenizer
{
public:
	static std::string remove(std::string s, char dest);
	static std::string strip(std::string src);
	static std::vector<std::string> parse(std::string src, std::string separator);
};

#endif