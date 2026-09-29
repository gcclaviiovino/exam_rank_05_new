#ifndef bigint_HPP
# define bigint_HPP

# include <string>
# include <stdbool.h>
# include <iostream>
# include <sstream>
# include <algorithm>

class	bigint {
	private:
	std::string	digits;

	public:
	bigint();
	bigint( const unsigned long n );
	bigint( const bigint& other );
	bigint&	operator=( const bigint& other );
	~bigint();

	bigint	operator+( const bigint& num ) const ;
	bigint&	operator+=( const bigint& num );
	bigint&	operator++();
	bigint	operator++( const int );
	bool	operator==( const bigint& num );
	bool	operator!=( const bigint& num );
	bool	operator>=( const bigint& num );
	bool	operator<=( const bigint& num );
	bool	operator<( const bigint& num );
	bool	operator>( const bigint& num );
	bigint	&operator<<=( const bigint& amount );
	bigint	&operator>>=( const bigint& amount );
	bigint	operator<<( const bigint& amount );
	bigint	operator>>( const bigint& amount );

	const std::string&	getDigits() const;
};

std::ostream &operator<<( std::ostream &oss, const bigint& num );

#endif