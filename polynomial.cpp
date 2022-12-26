#include<my_math>

Polynomial::Polynomial() : coefficients(0) {}

Polynomial::Polynomial(int degree) : coefficients(degree + 1) {}

Polynomial::Polynomial(const std::vector<double>& coefficients) : coefficients(coefficients) {
	this->removeEmptyCoefficients();
}

Polynomial::Polynomial(const Polynomial& other) : coefficients(other.coefficients) {
	this->removeEmptyCoefficients();
}

void Polynomial::setCoefficient(int degree, double coefficient) {
	this->coefficients[degree] = coefficient;
}

double Polynomial::getCoefficient(int degree) const {
	return this->coefficients[degree];
}

int Polynomial::getDegree() const {
	return this->coefficients.size() - 1;
}

double Polynomial::evaluate(int value) const {
	double result = 0;
	for (int i = this->getDegree(); i >= 0; i--) {
		result = result * value + this->coefficients[i];
	}
	return result;
}

double Polynomial::evaluate(double value) const {
	double result = 0;
	for (int i = this->getDegree(); i >= 0; i--) {
		result = result * value + this->coefficients[i];
	}
	return result;
}

Polynomial Polynomial::compose(const Polynomial& other) const {
	Polynomial result();
	for(int i = this->getDegree();i >= 0;i--){
		result = result.multiply(other) + this->coefficients[i];
	}
	return result;
}

bool Polynomial::equals(const Polynomial& other) const {
	if (coefficients.size() != other.coefficients.size()) {
		return false;
	}
	for (size_t i = 0; i < coefficients.size(); i++) {
		if (coefficients[i] != other.coefficients[i]) {
			return false;
		}
	}
	return true;
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
	result.setCoefficient(0, this->getCoefficient(0) - value);
	return result;
}

Polynomial Polynomial::substract(double value) const {
	Polynomial result(*this);
	result.setCoefficient(0, this->getCoefficient(0) - value);
	return result;
}

Polynomial Polynomial::substract(const Polynomial& other) const {
	int resultDegree = std::max(this->getDegree(), other.getDegree());
	std::vector<double> resultCoefficients(resultDegree + 1, 0.0);
	for (int i = 0; i <= resultDegree; i++) {
		resultCoefficients[i] = this->getCoefficient(i) - other.getCoefficient(i);
	}
	return Polynomial(resultCoefficients);
}

Polynomial Polynomial::multiply(int value) const {
	int resultDegree = this->getDegree();
	std::vector<double> resultCoefficients(resultDegree + 1, 0.0);
	for (int i = 0; i <= resultDegree; i++) {
		resultCoefficients[i] = this->coefficients[i] * value;
	}
	return Polynomial(resultCoefficients);
}

Polynomial Polynomial::multiply(double value) const {
	int resultDegree = this->getDegree();
	std::vector<double> resultCoefficients(resultDegree + 1, 0.0);
	for (int i = 0; i <= resultDegree; i++) {
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

Polynomial Polynomial::divide(int value) const {
	int resultDegree = this->getDegree();
	std::vector<double> resultCoefficients(resultDegree + 1, 0.0);
	for (int i = 0; i <= resultDegree; i++) {
		resultCoefficients[i] = this->coefficients[i] / value;
	}
	return Polynomial(resultCoefficients);
}

Polynomial Polynomial::divide(double value) const {
	int resultDegree = this->getDegree();
	std::vector<double> resultCoefficients(resultDegree + 1, 0.0);
	for (int i = 0; i <= resultDegree; i++) {
		resultCoefficients[i] = this->coefficients[i] / value;
	}
	return Polynomial(resultCoefficients);
}

Polynomial Polynomial::divide(const Polynomial& divisor) const {
	Polynomial dividend = *this;
	if (divisor.getCoefficient(divisor.getDegree()) == 0) {
		throw std::invalid_argument("Divisor must have a non-zero coefficient for its highest degree term.");
	}
	int quotientDegree = dividend.getDegree() - divisor.getDegree();
	Polynomial quotient(quotientDegree);
	while (dividend.getDegree() >= divisor.getDegree()) {
		double coefficient = dividend.getCoefficient(dividend.getDegree()) / divisor.getCoefficient(divisor.getDegree());
		int degree = dividend.getDegree() - divisor.getDegree();
		quotient.setCoefficient(degree, coefficient);
		Polynomial term(degree);
		term.setCoefficient(degree, coefficient);
		dividend = dividend.substract(divisor.multiply(term));
	}
	return quotient;
}

Polynomial Polynomial::remainder(const Polynomial& divisor) const {
	Polynomial dividend = *this;
	if (divisor.getCoefficient(divisor.getDegree()) == 0) {
		throw std::invalid_argument("Divisor must have a non-zero coefficient for its highest degree term.");
	}
	while (dividend.getDegree() >= divisor.getDegree()) {
		double coefficient = dividend.getCoefficient(dividend.getDegree()) / divisor.getCoefficient(divisor.getDegree());
		int degree = dividend.getDegree() - divisor.getDegree();
		Polynomial term(degree);
		term.setCoefficient(degree, coefficient);
		dividend = dividend.substract(divisor.multiply(term));
	}
	return dividend;
}

Polynomial Polynomial::derivative() const {
	int resultDegree = coefficients.size();
	std::vector<double> resultCoefficients(resultDegree - 1);
	for (int i = 1; i < resultDegree; i++) {
		resultCoefficients[i - 1] = coefficients[i] * i;
	}
	return Polynomial(resultCoefficients);
}

Polynomial Polynomial::tangent(double value) const {
	Polynomial derivative = this->derivative();
	double slope = derivative.evaluate(value);
	double y = this->evaluate(value);
	Polynomial tangent({-slope * value + y, slope});
	return tangent;
}

Polynomial Polynomial::primitive(double value = 0) const {
	int resultDegree = coefficients.size();
	std::vector<double> resultCoefficients(resultDegree + 1);
	for (int i = 0; i < resultDegree; ++i) {
		resultCoefficients[i + 1] = coefficients[i] / (i + 1);
	}
	resultCoefficients[0] = value;
	return Polynomial(resultCoefficients);
}

double Polynomial::integral(double lowerBound, double upperBound) const {
	Polynomial primitive = this->primitive();
	return primitive.evaluate(upperBound) - primitive.evaluate(lowerBound);
}

double Polynomial::limitAsXApproachesPossitiveInfinity() const {
	int degree = this->getDegree();
	while (degree >= 0 && this->getCoefficient(degree) == 0) {
		degree--;
	}
	if (degree < 0) {
		return 0;
	} else if (degree == 0) {
		return this->getCoefficient(degree);
	} else if (this->getCoefficient(degree) > 0) {
		return std::numeric_limits<double>::infinity();
	}
	return -std::numeric_limits<double>::infinity();
}

double Polynomial::limitAsXApproachesNegativeInfinity() const {
	int degree = this->getDegree();
	while (degree >= 0 && this->getCoefficient(degree) == 0) {
		degree--;
	}
	if (degree < 0) {
		return 0;
	} else if (degree == 0) {
		return this->getCoefficient(degree);
	} else if (degree % 2 = 0) {
		if (this->getCoefficient(degree) > 0) {
			return std::numeric_limits<double>::infinity();
		}
		return -std::numeric_limits<double>::infinity();
	} else if (this->getCoefficient(degree) > 0) {
		return -std::numeric_limits<double>::infinity();
	}
	return std::numeric_limits<double>::infinity();
}

bool Polynomial::isOdd() const {
	for (int i = 0;i <= this->getDegree();i += 2) {
		if (this->getCoefficient(i))
			return false;
	}
	return true;
}

bool Polynomial::isOdd() const {
	for (int i = 1;i <= this->getDegree();i += 2) {
		if (this->getCoefficient(i))
			return false;
	}
	return true;
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
			} else if (coefficient != 1.0 || i == 0) {
				oss << coefficient;
			}
			if (i > 1) {
				oss << "x^" << i;
			} else if (i == 1) {
				oss << "x";
			}
		}
	}
	if (oss.str() == "")
		oss << "0";
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

bool operator==(const Polynomial& p1, const Polynomial& p2) {
	return p1.equals(p2);
}

bool operator!=(const Polynomial& p1, const Polynomial& p2) {
	return !p1.equals(p2);
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
	return p1.substract(p2);
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

Polynomial operator/(const Polynomial& p, int value) {
	return p.divide(value);
}

Polynomial operator/(const Polynomial& p, double value) {
	return p.divide(value);
}

Polynomial operator/(const Polynomial& p1, const Polynomial& p2) {
	return p1.divide(p2);
}

Polynomial operator%(const Polynomial& p1, const Polynomial& p2) {
	return p1.remainder(p2);
}
