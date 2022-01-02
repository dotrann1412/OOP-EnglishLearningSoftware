#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <cstdlib>
#include <vector>

class Helper
{
public:
	static int parseInt(const std::string&);
	static std::string removeSpace(const std::string&);
	static std::string toLower(const std::string&);
	static std::string toUpper(const std::string&);

    static std::string randomStr(int len, std::string prefix = "");

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

template <class T> std::istream &operator >> (std::istream &s, std::vector<T> &a){
	for(T &x: a) s >> x;
	return s;
}

template <class T> std::ostream &operator << (std::ostream &s, std::vector<T> &a){
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

		sort(begin, pivot, criteria);
		sort(pivot + 1, end, criteria);
	}
}

template<class T>
T Helper::min(const T& a, const T& b) {
	return a < b ? a : b;
}

#endif
