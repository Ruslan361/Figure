#pragma once
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "Exception.hpp"

#define IS_VISIBLE_BY_DEFAULT true


//интерфейс
class Figure {
public:
	virtual double perimetr() = 0;
	virtual double area() = 0;
	virtual void move(double X, double Y) = 0;
	Figure(){}
};

class VisibleFigure : public Figure {
public:
	bool visible;

	//конструкторы
	VisibleFigure(bool _visible) : Figure(), visible(_visible) {}
	VisibleFigure() : VisibleFigure(IS_VISIBLE_BY_DEFAULT) {}
	
	//методы
	virtual void show() = 0;
};

class UnvisiblePoint : public Figure {
public:
	double x, y; //координаты

	//конструкторы
	UnvisiblePoint(double _x, double _y) : Figure(), x(_x), y(_y) {}
	UnvisiblePoint() : UnvisiblePoint(0, 0) {}
	UnvisiblePoint(const UnvisiblePoint& point) : UnvisiblePoint(point.x, point.y) {}

	//методы
	void move(double X, double Y) override {
		x += X;
		y += Y;
	}
	double perimetr() override {
		return 0;
	}
	double area() override {
		return 0;
	}
	double abs() const { //радиус вектор
		return sqrt(x * x + y * y);
	}

	//перегрузки
	const bool operator== (const UnvisiblePoint& point) const {
		return ((x == point.x) && (y == point.y));
	}
	const UnvisiblePoint operator-(const UnvisiblePoint& point) {
		double X = x - point.x;
		double Y = y - point.y;
		return UnvisiblePoint(X, Y);
	}
	UnvisiblePoint& operator= (const UnvisiblePoint& point) {
		x = point.x;
		y = point.y;
		return *this;
	}
};

class Point : public VisibleFigure {
public:
	UnvisiblePoint point;
	Point(const Point& point) : VisibleFigure(point.visible), point(point.point) {}
	Point(bool _visible) : VisibleFigure(_visible), point() {}
	Point() : Point(IS_VISIBLE_BY_DEFAULT) {}
	Point(double _x, double _y, bool _visible) : VisibleFigure(_visible), point(_x, _y) {}
	Point(double _x, double _y) : VisibleFigure(IS_VISIBLE_BY_DEFAULT), point(_x, _y) {}
	void show() override {
		if (visible) {
			std::cout << "Point:"<< std::endl
				<< "X " << point.x << std::endl
				<< "Y " << point.y << std::endl;
		}
	}
	double perimetr() override {
		return 0;
	}
	double area() override {
		return 0;
	}
	void move(double X, double Y) override {
		point.x += X;
		point.y += Y;
	}
	Point& operator= (const Point& point) {
		this->point = point.point;
		this->visible = point.visible;
		return *this;
	}
};

class Line : public VisibleFigure {
private:
	UnvisiblePoint first, second;
public:
	Line(const Line& line) {
		first = line.first;
		second = line.second;
	}
	Line(bool _visible) : VisibleFigure(_visible), first(), second(1, 0) {}
	Line() : Line(IS_VISIBLE_BY_DEFAULT) {}
	Line(const UnvisiblePoint& _first, const UnvisiblePoint& _second, bool _visible) : VisibleFigure(_visible) {
		if (_first == _second)
			throw LineException(__LINE__);
		first = _first;
		second = _second;

	}
	Line(const UnvisiblePoint& _first, const UnvisiblePoint& _second) : Line(_first, _second, IS_VISIBLE_BY_DEFAULT) {}
	void show() override {
		if (visible) {
			std::cout<< "Line:"<< std::endl
				<< "X1 " << first.x<< std::endl
				<< "Y1 " << first.y << std::endl
				<< "X2 " << second.x<< std::endl
				<< "Y2 " << second.y << std::endl;
		}
	}

	double perimetr() override {
		return (second - first).abs();
	}
	double area() override {
		return 0;
	}
	void move(double X, double Y) override {
		first.move(X, Y);
		second.move(X, Y);
	}
	Line& operator= (const Line& line) {
		this->first = line.first;
		this->second = line.second;
		this->visible = line.visible;
		return *this;
	}
};

class Triangle : public VisibleFigure {
private:
	UnvisiblePoint point_1, point_2, point_3;
public:
	//Конструкторы
	Triangle(const UnvisiblePoint& _point_1, const UnvisiblePoint& _point_2, const UnvisiblePoint& _point_3, bool visible = IS_VISIBLE_BY_DEFAULT) : VisibleFigure(visible), point_1(_point_1), point_2(_point_2), point_3(_point_3) {
		if (area() <= 0)
			throw TriangleException(__LINE__);
	}
	Triangle() : Triangle(UnvisiblePoint(0, 0), UnvisiblePoint(1, 1), UnvisiblePoint(0, 2)) {}
	Triangle(const Triangle& triangle) : Triangle(triangle.point_1, triangle.point_2, triangle.point_3, triangle.visible) {}
	//методы
	void setPoint_1(const UnvisiblePoint& point) {
		point_1 = point;
		if (area() <= 0) throw TriangleException(__LINE__);
	}
	void setPoint_2(const UnvisiblePoint& point) {
		point_2 = point;
		if (area() <= 0) throw TriangleException(__LINE__);
	}
	void setPoint_3(const UnvisiblePoint& point) {
		point_3 = point;
		if (area() <= 0) throw TriangleException(__LINE__);
	}
	UnvisiblePoint getPoint_1(){ return point_1; }
	UnvisiblePoint getPoint_2() { return point_2; }
	UnvisiblePoint getPoint_3() { return point_3; }
	void move(double X, double Y) override {
		point_1.move(X, Y);
		point_2.move(X, Y);
		point_3.move(X, Y);
	}
	double perimetr() override {
		return (point_2 - point_1).abs() + (point_3 - point_2).abs() + (point_3 - point_1).abs();
	}
	double area() override {
		//double a = (point_2 - point_1).abs();
		//double b = (point_3 - point_2).abs();
		//double c = (point_3 - point_1).abs();
		//double p = (a + b + c) / 2;
		//return sqrt(p * (p - a) * (p - b) * (p - c));
		return abs(0.5*((point_1.x - point_3.x) * (point_2.y - point_3.y) - (point_1.y - point_3.y) * (point_2.x - point_3.x)));
	}
	void show() override {
		if (visible) {
			std::cout << "Triangle" << std::endl
				<< "Point_1 " << std::endl
				<< "X " << point_1.x << std::endl
				<< "Y " << point_1.y << std::endl
				<< "Point_2 " << std::endl
				<< "X " << point_2.x << std::endl
				<< "Y " << point_2.y << std::endl
				<< "Point_3 " << std::endl
				<< "X " << point_3.x << std::endl
				<< "Y " << point_3.y << std::endl;
		}
	}
	Triangle& operator= (const Triangle& triangle) {
		this->point_1 = triangle.point_1;
		this->point_2 = triangle.point_2;
		this->point_3 = triangle.point_3;
		this->visible = triangle.visible;
		return *this;
	}
};

class Circle : public VisibleFigure {
private:
	double radius;
public:
	UnvisiblePoint center;

	//конструкторы
	Circle(bool visible = IS_VISIBLE_BY_DEFAULT) : VisibleFigure(visible), center(), radius(1.0) {}
	Circle(double x, double y, double _radius, bool visible = IS_VISIBLE_BY_DEFAULT) : VisibleFigure(visible) {
		if (_radius <= 0) throw CircleException(__LINE__);
		radius = _radius;
	}
	Circle(const UnvisiblePoint& point, double _radius, bool visible = IS_VISIBLE_BY_DEFAULT) : VisibleFigure(visible) {
		if (_radius <= 0) throw CircleException(__LINE__);
		radius = _radius;
	}
	Circle(const Circle& circle) : Circle(circle.center, circle.radius, circle.visible) {}

	//методы
	void setRadius(double radius) {
		if (radius <= 0) throw CircleException(__LINE__);
		this->radius = radius;
	}
	double getRadius() { return radius; }
	double perimetr() override {
		return 2 * M_PI * radius;
	}
	double area() override {
		return M_PI * radius * radius;
	}
	void show() override {
		if (visible) {
			std::cout << "Circle" << std::endl
				<< "X " << center.x << std::endl
				<< "Y " << center.y << std::endl
				<< "radius " << radius << std::endl;
		}
	}
	void move(double X, double Y) override {
		center.move(X, Y);
	}
	Circle& operator= (const Circle& circle) {
		this->center = circle.center;
		this->radius = circle.radius;
		this->visible = circle.visible;
		return *this;
	}
};
class Rectangle : public VisibleFigure {
public:
	UnvisiblePoint point;
	double width;
	double length;
	//конструкторы
	Rectangle(const UnvisiblePoint& point, double width, double length, bool visible = IS_VISIBLE_BY_DEFAULT) : VisibleFigure(visible)  {
		if (width <= 0) throw RectangleException(__LINE__);
		if (length <= 0) throw RectangleException(__LINE__);
		this->width = width;
		this->length = length;
	}
	Rectangle() : Rectangle(UnvisiblePoint(), 1, 1) {}
	Rectangle(const Rectangle& rectangle) : Rectangle(rectangle.point, rectangle.width, rectangle.length, rectangle.visible) {}
	double perimetr() override {
		return 2 * (width + length);
	}
	double area() override {
		return width * length;
	}
	void show() override {
		if (visible) {
			std::cout << "Rectangle" << std::endl
				<< "X " << point.x << std::endl
				<< "Y " << point.y << std::endl
				<< "width " << width << std::endl
				<< "length " << length << std::endl;
		}
	}
	void move(double X, double Y) override {
		point.move(X, Y);
	}
	Rectangle& operator= (const Rectangle& rectangle) {
		this->point = rectangle.point;
		this->width = rectangle.width;
		this->length = rectangle.length;
		this->visible = rectangle.visible;
		return *this;
	}
};

class Square : public VisibleFigure {
public:
	UnvisiblePoint point;
	double length;
	//конструкторы
	Square(const UnvisiblePoint& point, double length, bool visible = IS_VISIBLE_BY_DEFAULT) : VisibleFigure(visible) {
		if (length <= 0) throw RectangleException(__LINE__);
		this->length = length;
	}
	Square() : Square(UnvisiblePoint(), 1) {}
	Square(const Square& square) : Square(square.point, square.length, square.visible) {}
	double perimetr() override {
		return 4 * length;
	}
	double area() override {
		return length * length;
	}
	void show() override {
		if (visible) {
			std::cout << "Square" << std::endl
				<< "X " << point.x << std::endl
				<< "Y " << point.y << std::endl
				<< "length " << length << std::endl;
		}
	}
	void move(double X, double Y) override {
		point.move(X, Y);
	}
	Square& operator= (const Square& square) {
		this->point = square.point;
		this->length = square.length;
		this->visible = square.visible;
		return *this;
	}
};


class Image {
private:
	size_t size;
	VisibleFigure** image;
public:
	template <class T>
	void push(const T& figure, size_t index) {
		if (index >= size) throw ImageException(__LINE__);
		if (image[index] != nullptr)delete image[index];
		image[index] = new T(figure);
	}
	void show() {
		for (size_t i = 0; i < size; i++)
		{
			image[i]->show();
		}
	}
	Image(size_t size) {
		this->size = size;
		image = new VisibleFigure * [size];
		for (size_t i = 0; i < size; i++)
		{
			image[i] = nullptr;
		}
	}
	Image(const Image& _shape) {
		this->image = new VisibleFigure * [_shape.size];
		size = _shape.size;
		for (size_t i = 0; i < size; i++)
		{
			//push((*_shape.shape[i]), i);
		}
	}
	~Image() {
		for (size_t i = 0; i < size; i++)
		{
			delete image[i];
		}
		delete[] image;
	}
};