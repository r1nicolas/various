#ifndef MY_MATH_H
#define MY_MATH_H

#include <vector>
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
	Polynomial add(const Polynomial& other) const;
	Polynomial subtract(const Polynomial& other) const;
	std::string toString() const;

private:
	std::vector<double> coefficients;
	void removeEmptyCoefficients();
};

std::ostream& operator<<(std::ostream& os, const Polynomial& p);
Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
Polynomial operator-(const Polynomial& p1, const Polynomial& p2);

#endif // MY_MATH_H
