#ifndef RANKING_H
#define RANKING_H

#include <string>
#include <vector>
#include <functional>

// the idea is show the ranking table row by row
// data of table will be ordered with primary key

class Ranking
{
private:
	std::function<bool(std::string, std::string)> _compare;
	std::vector<std::vector<std::string>> _table;
	int _column;
	int _key;

private:
	void reOrder();

public:
	Ranking(int column, int key, std::function<bool(std::string, std::string)> _compare);
	Ranking(std::vector<std::vector<std::string>> table, int key, 
		std::function<bool(std::string, std::string)> _compare);
	Ranking(const Ranking&);

	~Ranking();

public:
	void setKey(int key);
	void addRow(std::vector<std::string> row);
	void removeRow(std::string id); // find on column 'key'
	void removeRow(int num);
	void setOrderPolicy(std::function<bool(std::string, std::string)> _compare);

public:
    std::vector<std::vector<std::string>> getTable() const;

public:
	std::string toString() const;

public:
	friend std::ostream& operator << (std::ostream& s, const Ranking&);

public:
	int getKey();
	int getColumn();
	int rowCount();
};

#endif
