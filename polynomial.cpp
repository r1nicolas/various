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
	double result = 0.0;
	for (int i = 0; i < coefficients.size(); i++) {
		result += coefficients[i] * pow(x, i);
	}
	return result;
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

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
	return os << p.toString();
}
