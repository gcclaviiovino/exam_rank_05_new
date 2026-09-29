#include "bigint.hpp"

bigint::bigint()
	: digits("0")
{}

bigint::bigint(const unsigned long n) {
	std::ostringstream	oss;
	oss << n;
	digits = oss.str();
}

bigint::bigint(const bigint& other)
	: digits(other.digits)
{}

bigint&	bigint::operator=(const bigint& other) {
	if (this != &other) {
		digits = other.digits;
	}
	return *this;
}

bigint::~bigint()
{}

const std::string	&bigint::getDigits() const {
	return digits;
}

bigint	bigint::operator+(const bigint& num) const {
	std::string	strRes = "";
	std::string	numDigits = num.getDigits();
	int	i = this->digits.length() - 1;
	int	j = numDigits.length() - 1;
	int	carry = 0;

	while (i >= 0 || j >= 0 || carry > 0) {
		int	d1 = (i >= 0) ? (this->digits[i]  - '0') : 0;
		int	d2 = (j >= 0) ? (numDigits[j] - '0') : 0 ;

		int	res = d1 + d2 + carry;
		strRes += (res % 10) + '0';
		carry = res / 10;

		i--;
		j--;
	}

	std::reverse(strRes.begin(), strRes.end());
	bigint bigRes;
	bigRes.digits = strRes;

	return bigRes;
}

bigint&	bigint::operator+=(const bigint& num) {
	*this = *this + num;
	return *this;
}

bigint&	bigint::operator++() {
	*this = *this + bigint(1);
	return *this;
}

bigint	bigint::operator++(int) {
	bigint	tmp = *this;
	operator++();
	return tmp;
}

bool	bigint::operator==(const bigint& num) {
	return this->digits == num.getDigits();
}

bool	bigint::operator!=(const bigint& num) {
	return !(*this == num);
}

bool	bigint::operator<(const bigint& num) {
	if (this->digits.length() != num.getDigits().length())
		return this->digits.length() < num.getDigits().length();
	else
		return this->digits < num.getDigits();
}

bool	bigint::operator>(const bigint& num) {
	if (this->digits.length() != num.getDigits().length())
		return this->digits.length() > num.getDigits().length();
	else
		return this->digits > num.getDigits();
}

bool	bigint::operator>=(const bigint& num) {
	return operator>(num) || operator==(num);
}

bool	bigint::operator<=(const bigint& num) {
	return operator<(num) || operator==(num);
}

bigint	&bigint::operator<<=(const bigint& amount ) {
	if (this->digits == "0")
		return *this;
	else if (amount.digits == "0")
		return *this;
	
	std::istringstream	iss(amount.getDigits());
	unsigned long	n;
	iss >> n;

	this->digits.append(n, '0');
	return *this;
}

bigint	&bigint::operator>>=(const bigint& amount) {
	if (this->digits == "0")
		return *this;
	else if (amount.getDigits() == "0")
		return *this;

	std::istringstream	iss(amount.getDigits());
	unsigned long	n;
	iss >> n;

	int	len = this->digits.length() - n;
	this->digits.resize(len);

	return *this;
}

bigint	bigint::operator<<(const bigint& amount) {
	bigint	res = *this;
	res<<=(amount);
	return res;
}

bigint	bigint::operator>>(const bigint& amount) {
	bigint	res = *this;
	res>>=(amount);
	return res;
}

std::ostream	&operator<<(std::ostream &oss, const bigint& num) {
	oss << num.getDigits();
	return oss;
}