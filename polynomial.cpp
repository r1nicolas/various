#include<my_math>

Polynomial::Polynomial() : coefficients(0) {}

Polynomial::Polynomial(int degree) : coefficients(degree + 1) {}

Polynomial::Polynomial(const std::vector<double>& coefficients) : coefficients(coefficients) {}

Polynomial::Polynomial(const Polynomial& other) : coefficients(other.coefficients) {}

void Polynomial::setCoefficient(int degree, double coefficient) {
	coefficients[degree] = coefficient;
}

double Polynomial::getCoefficient(int degree) const {
	return coefficients[degree];
}

int Polynomial::getDegree() const {
	return coefficients.size() - 1;
}

double Polynomial::evaluate(double x) const {
	double result = 0;
	for (int i = getDegree(); i >= 0; --i) {
		result = result * x + coefficients[i];
	}
	return result;
}

Polynomial Polynomial::add(const Polynomial& other) const {
	int resultDegree = std::max(getDegree(), other.getDegree());
	std::vector<double> resultCoefficients(resultDegree + 1, 0.0);
	for (int i = 0; i <= resultDegree; i++) {
		resultCoefficients[i] = getCoefficient(i) + other.getCoefficient(i);
	}
	return Polynomial(resultCoefficients);
}

Polynomial Polynomial::subtract(const Polynomial& other) const {
	int resultDegree = std::max(getDegree(), other.getDegree());
	std::vector<double> resultCoefficients(resultDegree + 1, 0.0);
	for (int i = 0; i <= resultDegree; i++) {
		resultCoefficients[i] = getCoefficient(i) - other.getCoefficient(i);
	}
	return Polynomial(resultCoefficients);
}

std::string Polynomial::toString() const {
	int degree = getDegree();
	std::ostringstream oss;
	for (int i = degree; i >= 0; i--) {
		double coefficient = getCoefficient(i);
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

void Polynomial::removeEmptyCoefficients() {
	int highestNonEmpty = getDegree();
	while (highestNonEmpty > 0 && coefficients[highestNonEmpty] == 0) {
		highestNonEmpty--;
	}
	coefficients.resize(highestNonEmpty + 1);
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
	return os << p.toString();
}

Polynomial operator+(const Polynomial& p1, const Polynomial& p2) {
	return p1.add(p2);
}

Polynomial operator-(const Polynomial& p1, const Polynomial& p2) {
	return p1.subtract(p2);
}
