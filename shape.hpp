#ifndef SHAPES_HPP
#define SHAPES_HPP

class shape
{
public:
	virtual double get_area() const = 0;

	virtual ~shape(){}
};
#endif // !SHAPES_HPP
