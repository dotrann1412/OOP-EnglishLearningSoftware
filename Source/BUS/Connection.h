#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <fstream>
#include <string>

class Connection
{
private:
	Connection();
	~Connection();

public:
	static std::ifstream fileReader(const std::string& filename);
	static std::ofstream fileWriter(const std::string& filename);

public:
	static std::ifstream binFileReader(const std::string& filename);
	static std::ofstream binFileWriter(const std::string& filename);
};

#endif