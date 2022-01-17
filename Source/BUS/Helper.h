#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <cstdlib>
#include <vector>

using std::vector;
using std::string;
using std::istream;
using std::ostream;

class Helper
{
public:
	static int parseInt(const std::string&);
	static std::string removeSpace(const std::string&);
	static std::string toLower(const std::string&);
	static std::string toUpper(const std::string&);

    static std::string randomStr(int len, std::string prefix = "");

    bool isPhoneNumber(std::string s);
    bool isEmailAddress(std::string s);

	template <class T>
    static void _swap(T& a, T& b);

	template<class T>
    static bool greater(T a, T b);

	template<class T>
    static T* partition(T* begin, T* end, bool (*criteria)(T, T));

	template<class T>
    static void sort(T* begin, T* end, bool (*criteria)(T, T) = greater);

	template<class T>
    static T min(const T& a, const T& b);
};

template <class T> istream &operator >> (istream &s, std::vector<T> &a){
	for(T &x: a) s >> x;
	return s;
}

template <class T> ostream &operator << (ostream &s, std::vector<T> &a){
	for(T &x: a) s << x << '\t';
	return s;
}

template <class T>
void Helper::_swap(T& a, T& b) {
	T c = a; a = b, b = c;
}

template<class T>
bool Helper::greater(T a, T b)
{
	return a > b;
}

template<class T>
T* Helper::partition(T* begin, T* end, bool (*criteria)(T, T))
{
	_swap(*(end - 1), *(begin + rand() % (end - begin - 1) + 1));
	T* pivot = end - 1, *iter = begin - 1;
	for(T* i = begin; i < end - 1; ++i) {
		if(criteria(*i, *pivot)) ++iter, swap(*iter, *i);
	}

	++iter, swap(*iter, *pivot);
	return iter;
}

template<class T>
void Helper::sort(T* begin, T* end, bool (*criteria)(T, T)){
	if(begin < end) {
		T* pivot = partition(begin, end, criteria);

        Helper::sort(begin, pivot, criteria);
        Helper::sort(pivot + 1, end, criteria);
	}
}

template<class T>
T Helper::min(const T& a, const T& b) {
	return a < b ? a : b;
}

#endif
