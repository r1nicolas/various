#ifndef MY_MATH_H
#define MY_MATH_H

#include <vector>
#include <math.h>
#include <sstream>

int padovan(int n);
int fibonacci(int n);

class Polynomial {
public:
	Polynomial();
	Polynomial(int degree);
	Polynomial(const std::vector<double>& coefficients);
	Polynomial(const Polynomial& other);
	void setCoefficient(int degree, double coefficient);
	double getCoefficient(int degree) const;
	int getDegree() const;
	double evaluate(double x) const;
	std::string toString() const;

private:
	std::vector<double> coefficients;
};

std::ostream& operator<<(std::ostream& os, const Polynomial& p)

#endif // MY_MATH_H
