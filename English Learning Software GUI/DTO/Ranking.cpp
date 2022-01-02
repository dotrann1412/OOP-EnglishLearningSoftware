#include "Ranking.h"

#include <algorithm>
#include <sstream>

#include "../BUS/Helper.h"

Ranking::Ranking(int column, int key, 
	std::function<bool(std::string, std::string)> _compare) {
	
	if(key < 0) 
		key = 0;
	
	if(column < 1)
		column = 1;

	this->_column = column;
	this->_key = std::min(key, column - 1);
	this->_compare = _compare;
}

Ranking::Ranking(std::vector<std::vector<std::string>> table, int key, 
	std::function<bool(std::string, std::string)> _compare) {

	if(key < 0)
		key = 0;

	if(table.size() == 0)
		table = std::vector<std::vector<std::string>>(1, std::vector<std::string>(3, "##"));

	this->_table = table;
	this->_column = table[0].size();
	this->_key = std::min(this->_column - 1, key);

	this->_compare = _compare;

	this->reOrder();
}

Ranking::Ranking(const Ranking& another) {
	_key = another._key;
	_column = another._column;
	_table = another._table;
}

Ranking::~Ranking() {

}

void Ranking::reOrder() {
	std::sort(this->_table.begin(), this->_table.end(), 
		[&](const std::vector<std::string>& a, const std::vector<std::string>& b) -> bool {
			return this->_compare(a[this->_key], b[this->_key]);
		}
	);
}

void Ranking::setKey(int key) {
	if(key > this->_column) return;
	this->_key = key;
	this->reOrder();
}

void Ranking::addRow(std::vector<std::string> row) {
	if(row.size() != this->_column) return;

	this->_table.push_back(row);

	for(int i = this->_table.size() - 1; 
		i && !this->_compare(this->_table[i][this->_key], this->_table[i - 1][this->_key]); 
		--i) {
		std::swap(this->_table[i], this->_table[i - 1]);
	}

}

void Ranking::removeRow(std::string id) {
	for(int i = 0; i < this->_table.size(); ++i) {
		if(this->_table[i][this->_key] == id) {
			this->_table.erase(this->_table.begin() + i);
			return;
		}
	}
} // find on column 'key'

void Ranking::removeRow(int num) {
	this->_table.erase(this->_table.begin() + num);
}

void Ranking::setOrderPolicy(std::function<bool(std::string, std::string)> _compare) {
	this->_compare = _compare;
	this->reOrder();
}

int Ranking::getKey() {
	return this->_key;
}

int Ranking::getColumn() {
	return this->_column;
}

int Ranking::rowCount() {
	return this->_table.size();
}

std::string Ranking::toString() const {
	std::stringstream ss;
	for(auto x: this->_table)
		ss << x << '\n';
	return ss.str();
}

std::ostream& operator << (std::ostream& s, const Ranking& a) {
	return s << a.toString();
}
