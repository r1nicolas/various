#include<my_math>

Polynomial::Polynomial() : coefficients(0) {}

Polynomial::Polynomial(int degree) : coefficients(degree + 1) {}

Polynomial::Polynomial(const std::vector<double>& coefficients) : coefficients(coefficients) {
	this->removeEmptyCoefficients()
}

Polynomial::Polynomial(const Polynomial& other) : coefficients(other.coefficients) {
	this->removeEmptyCoefficients()
}

void Polynomial::setCoefficient(int degree, double coefficient) {
	this->coefficients[degree] = coefficient;
}

double Polynomial::getCoefficient(int degree) const {
	return this->coefficients[degree];
}

int Polynomial::getDegree() const {
	this->removeEmptyCoefficients()
	return this->coefficients.size() - 1;
}

double Polynomial::evaluate(double x) const {
	double result = 0;
	for (int i = this->getDegree(); i >= 0; --i) {
		result = result * x + this->coefficients[i];
	}
	return result;
}

Polynomial Polynomial::add(int value) const {
	Polynomial result(*this);
	result.setCoefficient(0, this->getCoefficient(0) + value);
	return result;
}

Polynomial Polynomial::add(double value) const {
	Polynomial result(*this);
	result.setCoefficient(0, this->getCoefficient(0) + value);
	return result;
}

Polynomial Polynomial::add(const Polynomial& other) const {
	int resultDegree = std::max(this->getDegree(), other.getDegree());
	std::vector<double> resultCoefficients(resultDegree + 1, 0.0);
	for (int i = 0; i <= resultDegree; i++) {
		resultCoefficients[i] = this->getCoefficient(i) + other.getCoefficient(i);
	}
	return Polynomial(resultCoefficients);
}

Polynomial Polynomial::substract(int value) const {
	Polynomial result(*this);
	result.setCoefficient(0, this->getCoefficient(0) + value);
	return result;
}

Polynomial Polynomial::substract(double value) const {
	Polynomial result(*this);
	result.setCoefficient(0, this->getCoefficient(0) - value);
	return result;
}

Polynomial Polynomial::subtract(const Polynomial& other) const {
	int resultDegree = std::max(this->getDegree(), other.getDegree());
	std::vector<double> resultCoefficients(resultDegree + 1, 0.0);
	for (int i = 0; i <= resultDegree; i++) {
		resultCoefficients[i] = this->getCoefficient(i) - other.getCoefficient(i);
	}
	return Polynomial(resultCoefficients);
}

Polynomial Polynomial::multiply(int value) const {
	std::vector<double> resultCoefficients(this->getDegree() + 1, 0.0);
	for (int i = 0; i < this->coefficients.size(); i++) {
		resultCoefficients[i] = this->coefficients[i] * value;
	}
	return Polynomial(resultCoefficients);
}

Polynomial Polynomial::multiply(double value) const {
	std::vector<double> resultCoefficients(this->getDegree() + 1, 0.0);
	for (int i = 0; i < this->coefficients.size(); i++) {
		resultCoefficients[i] = this->coefficients[i] * value;
	}
	return Polynomial(resultCoefficients);
}

Polynomial Polynomial::multiply(const Polynomial& other) const {
	int resultDegree = this->getDegree() + other.getDegree();
	std::vector<double> resultCoefficients(resultDegree + 1, 0);
	for (int i = 0; i <= this->getDegree(); i++) {
		for (int j = 0; j <= other.getDegree(); j++) {
			resultCoefficients[i+j] += this->getCoefficient(i) * other.getCoefficient(j);
		}
	}
	return Polynomial(resultCoefficients);
}

std::string Polynomial::toString() const {
	int degree = this->getDegree();
	std::ostringstream oss;
	for (int i = degree; i >= 0; i--) {
		double coefficient = this->getCoefficient(i);
		if (coefficient != 0.0) {
			if (coefficient > 0 && i != degree) {
				oss << "+";
			}
			if (coefficient == -1.0 && i != 0) {
				oss << "-";
			}
			if (coefficient != 1.0 || i == 0) {
				oss << coefficient;
			}
			if (i > 1) {
				oss << "x^" << i;
			} else if (i == 1) {
				oss << "x";
			}
		}
	}
	return oss.str();
}

double Polynomial::operator[](int degree) const {
	return getCoefficient(degree);
}

void Polynomial::removeEmptyCoefficients() {
	int highestNonEmpty = this->getDegree();
	while (highestNonEmpty > 0 && this->coefficients[highestNonEmpty] == 0) {
		highestNonEmpty--;
	}
	this->coefficients.resize(highestNonEmpty + 1);
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
	return os << p.toString();
}

Polynomial operator+(const Polynomial& p, int value) {
	return p.add(value);
}

Polynomial operator+(int value, const Polynomial& p) {
	return p.add(value);
}

Polynomial operator+(const Polynomial& p, double value) {
	return p.add(value);
}

Polynomial operator+(double value, const Polynomial& p) {
	return p.add(value);
}

Polynomial operator+(const Polynomial& p1, const Polynomial& p2) {
	return p1.add(p2);
}

Polynomial operator-(const Polynomial& p) {
	return p.multiply(-1);
}

Polynomial operator-(const Polynomial& p, int value) {
	return p.substract(value);
}

Polynomial operator-(int value, const Polynomial& p) {
	return p.multiply(-1).add(value);
}

Polynomial operator-(const Polynomial& p, double value) {
	return p.substract(value);
}

Polynomial operator-(double value, const Polynomial& p) {
	return p.multiply(-1).add(value);
}

Polynomial operator-(const Polynomial& p1, const Polynomial& p2) {
	return p1.subtract(p2);
}

Polynomial operator*(int value, const Polynomial& p) {
	return p.multiply(value);
}

Polynomial operator*(const Polynomial& p, int value) {
	return p.multiply(value);
}

Polynomial operator*(double value, const Polynomial& p) {
	return p.multiply(value);
}

Polynomial operator*(const Polynomial& p, double value) {
	return p.multiply(value);
}

Polynomial operator*(const Polynomial& p1, const Polynomial& p2) {
	return p1.multiply(p2);
}
