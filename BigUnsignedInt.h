#ifndef BIGUNSIGNEDINT_H_
#define BIGUNSIGNEDINT_H_

#include <deque>
#include <string>
#include <climits>
#include <cmath>

class BigUnsignedInt
{
private:
	typedef unsigned long long UI_TYPE;
	const UI_TYPE UI_MAX = ULLONG_MAX;
	const int UI_BIT_SIZE = (int)log2(UI_MAX);
	typedef std::deque<UI_TYPE> UI_DEQUE;

	UI_DEQUE ui_deque;

	void addUnsignedInt(UI_DEQUE::iterator const &lhIter, UI_TYPE const &rhValue);
	void subtractUnsignedInt(UI_DEQUE::iterator const &lhIter, UI_TYPE const &rhValue);
	void multiplyUnsignedInt(UI_DEQUE::iterator const &lhIter, UI_TYPE const &rhValue);
	const UI_TYPE divideBigUnsignedInt(UI_DEQUE::reverse_iterator const &lhIter, UI_TYPE const &divisor, UI_TYPE remainder);
	const BigUnsignedInt divideBigUnsignedInt(BigUnsignedInt const &divisor);

	void elem_left_shift_by(UI_DEQUE::size_type const &);
	inline bool bit_in_location(UI_TYPE const &ui_elem, int const &location);
	inline bool is_zero() const;
	
public:
	
	BigUnsignedInt();
	BigUnsignedInt(const BigUnsignedInt &);
	BigUnsignedInt(const UI_TYPE &);

	BigUnsignedInt& operator=(const BigUnsignedInt &);
	
	BigUnsignedInt operator+=(UI_TYPE const &);
	BigUnsignedInt operator-=(UI_TYPE const &);
	BigUnsignedInt operator*=(UI_TYPE const &);
	BigUnsignedInt operator/=(UI_TYPE const &);
	BigUnsignedInt operator%=(UI_TYPE const &);

	const BigUnsignedInt operator+(UI_TYPE const &) const;
	const BigUnsignedInt operator-(UI_TYPE const &) const;
	const BigUnsignedInt operator*(UI_TYPE const &) const;
	const BigUnsignedInt operator/(UI_TYPE const &) const;
	const BigUnsignedInt operator%(UI_TYPE const &) const;

	BigUnsignedInt& operator+=(BigUnsignedInt const &);
	BigUnsignedInt& operator-=(BigUnsignedInt const &);
	BigUnsignedInt& operator*=(BigUnsignedInt const &);
	BigUnsignedInt& operator/=(BigUnsignedInt const &);
	BigUnsignedInt& operator%=(BigUnsignedInt const &);
	
	const BigUnsignedInt operator+(BigUnsignedInt const &) const;
	const BigUnsignedInt operator-(BigUnsignedInt const &) const;
	const BigUnsignedInt operator*(BigUnsignedInt const &) const;
	const BigUnsignedInt operator/(BigUnsignedInt const &) const;
	const BigUnsignedInt operator%(BigUnsignedInt const &) const;

	const bool operator==(UI_TYPE const &) const;
	const bool operator!=(UI_TYPE const &) const;
	const bool operator> (UI_TYPE const &) const;
	const bool operator< (UI_TYPE const &) const;
	const bool operator>=(UI_TYPE const &) const;
	const bool operator<=(UI_TYPE const &) const;

	const bool operator==(BigUnsignedInt const &) const;
	const bool operator!=(BigUnsignedInt const &) const;
	const bool operator> (BigUnsignedInt const &) const;
	const bool operator< (BigUnsignedInt const &) const;
	const bool operator>=(BigUnsignedInt const &) const;
	const bool operator<=(BigUnsignedInt const &) const;

	friend const BigUnsignedInt operator+(UI_TYPE const &, BigUnsignedInt const &);
	friend const BigUnsignedInt operator-(UI_TYPE const &, BigUnsignedInt const &);
	friend const BigUnsignedInt operator*(UI_TYPE const &, BigUnsignedInt const &);
	friend const BigUnsignedInt operator/(UI_TYPE const &, BigUnsignedInt const &);
	friend const BigUnsignedInt operator%(UI_TYPE const &, BigUnsignedInt const &);

	friend const bool operator==(UI_TYPE const &, BigUnsignedInt const &);
	friend const bool operator!=(UI_TYPE const &, BigUnsignedInt const &);
	friend const bool operator> (UI_TYPE const &, BigUnsignedInt const &);
	friend const bool operator< (UI_TYPE const &, BigUnsignedInt const &);
	friend const bool operator>=(UI_TYPE const &, BigUnsignedInt const &);
	friend const bool operator<=(UI_TYPE const &, BigUnsignedInt const &);

	const std::string toString() const;
};

#endif
