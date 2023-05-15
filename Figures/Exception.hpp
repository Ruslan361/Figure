#pragma once
#include <string>
#include <ostream>

class Exception {
	std::string name;
	std::string time;
	std::string date;
	size_t line;
public:
	Exception(std::string _name, size_t _line) :name(_name), line(_line), date(__DATE__), time(__TIME__) {}
	friend std::ostream& operator << (std::ostream& stream, const Exception& exception){
		stream << exception.name << std::endl << exception.time << std::endl << exception.date << std::endl << exception.line << std::endl;
		return stream;
	}
};
class LineException : public Exception {
public:
	LineException(size_t line) : Exception("Line Exception", line) {}
};
class TriangleException : public Exception {
public:
	TriangleException(size_t line) : Exception("Triangle Exception", line) {}
};
class CircleException : public Exception {
public:
	CircleException(size_t line) : Exception("Circle Exception", line) {}
};
class RectangleException : public Exception {
public:
	RectangleException(size_t line) : Exception("Rectangle Exception", line) {}
};
class ImageException : public Exception {
public:
	ImageException(size_t line) : Exception("Shape Exception", line) {}
};