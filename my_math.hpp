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
	Polynomial add(int value) const;
	Polynomial add(double value) const;
	Polynomial add(const Polynomial& other) const;
	Polynomial substract(int value) const;
	Polynomial substract(double value) const;
	Polynomial subtract(const Polynomial& other) const;
	Polynomial multiply(int value) const;
	Polynomial multiply(double value) const;
	Polynomial multiply(const Polynomial& other) const;
	Polynomial divide(int value) const;
	Polynomial divide(double value) const;
	Polynomial derivative() const;
	Polynomial primitive(double value = 0) const;
	double integral(double lowerBound, double upperBound) const;
	std::string toString() const;
	double operator[](int degree) const;
private:
	std::vector<double> coefficients;
	void removeEmptyCoefficients();
};

std::ostream& operator<<(std::ostream& os, const Polynomial& p);
Polynomial operator+(const Polynomial& p, int value);
Polynomial operator+(int value, const Polynomial& p);
Polynomial operator+(const Polynomial& p, double value);
Polynomial operator+(double value, const Polynomial& p);
Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
Polynomial operator-(const Polynomial& p);
Polynomial operator-(const Polynomial& p, int value);
Polynomial operator-(int value, const Polynomial& p);
Polynomial operator-(const Polynomial& p, double value);
Polynomial operator-(double value, const Polynomial& p);
Polynomial operator-(const Polynomial& p1, const Polynomial& p2);
Polynomial operator*(int value, const Polynomial& p); 
Polynomial operator*(const Polynomial& p, int value);
Polynomial operator*(double value, const Polynomial& p); 
Polynomial operator*(const Polynomial& p, double value);
Polynomial operator*(const Polynomial& p1, const Polynomial& p2);
Polynomial operator/(const Polynomial& p, int value);
Polynomial operator/(const Polynomial& p, double value);

#endif // MY_MATH_H
