#include "Connection.h"
#include <cstdlib>

using std::string;
using std::ofstream;
using std::ifstream;

std::ifstream Connection::fileReader(const std::string& filename) {
	std::ifstream file;
	file.open(filename);

	return file;
}

std::ofstream Connection::fileWriter(const std::string& filename) {
	std::ofstream file;
	file.open(filename);

	return file;
}

std::ifstream Connection::binFileReader(const std::string& filename) {
	std::ifstream file;
	file.open(filename, std::ios::binary);

	return file;
}

std::ofstream Connection::binFileWriter(const std::string& filename) {
	std::ofstream file;
    file.open(filename, std::ios::binary);
	return file;
}