#include "Figures.hpp"
int main() try {
	VisibleFigure** figure = new VisibleFigure*[6];
	figure[0] = new Point(1, 2);
	figure[1] = new Line();
	figure[2] = new Triangle();
	figure[3] = new Circle();
	figure[4] = new Rectangle();
	figure[5] = new Square();
	for (size_t i = 0; i < 6; i++)
	{
		figure[i]->show();
		std::cout << "Area: " << figure[i]->area() << std::endl;
		std::cout << "Perimetr: " << figure[i]->perimetr() << std::endl;
		std::cout << std::endl << "Move (1, 2)" << std::endl;
		figure[i]->move(1, 2);
		figure[i]->show();
		std::cout << std::endl;
		delete figure[i];
	}
	delete[] figure;
	std::cout << std::endl << std::endl;
	Image image(6);
	image.push(Point(1, 2), 0);
	image.push(Line(), 1);
	image.push(Triangle(), 2);
	image.push(Circle(), 3);
	image.push(Rectangle(), 4);
	image.push(Square(), 5);
	image.show();
	return 0;
}
catch (Exception exception) {
	std::cout << exception;
}