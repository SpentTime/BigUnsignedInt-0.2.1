#include "BigUnsignedInt.h"
#include <stdexcept>
#include <iostream>

//Private methods

void BigUnsignedInt::addUnsignedInt(UI_DEQUE::iterator const &lhIter, UI_TYPE const &rhValue)
{
	if(rhValue == 0)
		return;
	if(lhIter == this->ui_deque.end())
	{
		this->ui_deque.push_back(rhValue);
		return;
	}
	if(*lhIter > UI_MAX - rhValue)
	{
		*lhIter += rhValue;
		this->addUnsignedInt(lhIter + 1, 1);
	}
	else
		*lhIter += rhValue;
}
void BigUnsignedInt::subtractUnsignedInt(UI_DEQUE::iterator const &lhIter, UI_TYPE const &rhValue)
{
	if(lhIter == this->ui_deque.end())
		throw std::underflow_error("Underflow error");
	if(rhValue == 0)
		return;
	if(*lhIter < rhValue)
	{
		*lhIter -= rhValue;
		this->subtractUnsignedInt(lhIter + 1, 1);
	}
	else
		*lhIter -= rhValue;
}
void BigUnsignedInt::multiplyUnsignedInt(UI_DEQUE::iterator const &lhIter, UI_TYPE const &rhValue)
{
	if(lhIter == this->ui_deque.end())
		return;
	if(rhValue == 0)
	{
		this->ui_deque = {0};
		return;
	}
	if(rhValue == 1)
		return;
	if(*lhIter > UI_MAX / rhValue)
	{
		UI_TYPE buffer[2] = {};
		for(int i = 0; i != UI_BIT_SIZE; ++i)
		{

			UI_TYPE bitProduct = *lhIter * ((rhValue & (1ULL << i)) >> i),
					a = bitProduct << i,
					b = (i) ? bitProduct >> (UI_BIT_SIZE - i) : 0;
			if(!a && !b)
				continue;
			if(buffer[0] > UI_MAX - a)
				++buffer[1];
			buffer[0] += a;
			buffer[1] += b;
		}
		*lhIter = buffer[0];
		this->multiplyUnsignedInt(lhIter + 1, rhValue);
		this->addUnsignedInt(lhIter + 1, buffer[1]);
	}
	else
	{
		*lhIter *= rhValue;
		this->multiplyUnsignedInt(lhIter + 1, rhValue);
		
	}
}
const BigUnsignedInt::UI_TYPE BigUnsignedInt::divideBigUnsignedInt(UI_DEQUE::reverse_iterator const &lhRIter, 
	UI_TYPE const &divisor, UI_TYPE remainder = 0)
{
	if(divisor == 0)
		throw std::runtime_error("Divide by zero exception.");

	UI_TYPE final_remainder = 0;

	if(divisor == 1)
	{
		return final_remainder;
	}

	if(remainder == 0)
	{
		remainder = *lhRIter % divisor;
		*lhRIter /= divisor;
	}
	else
	{
		int bit_size = log2(remainder) + 1;
		UI_TYPE buffer = 0;
		auto previous_remainder = remainder;
		remainder = 0;

		for(int i = 0; i != bit_size; ++i)
		{
			int current_bit = bit_in_location(previous_remainder, i);
			if(!current_bit) continue;
			remainder += ((UI_MAX % divisor) << i) + (1ULL << i);
			buffer += (UI_MAX / divisor) << i;
			buffer += remainder / divisor;
			remainder %= divisor;
		}

		remainder += *lhRIter % divisor;
		*lhRIter = (*lhRIter / divisor) + buffer + (remainder / divisor);
		remainder %= divisor;
	}

	if(lhRIter + 1 == this->ui_deque.rend())
		final_remainder = remainder;
	else
		final_remainder = this->divideBigUnsignedInt(lhRIter + 1, divisor, remainder);

	return final_remainder;
}
const BigUnsignedInt BigUnsignedInt::divideBigUnsignedInt(BigUnsignedInt const &other)
{
	UI_DEQUE::size_type elem_to_move = other.ui_deque.size() - 1;
	UI_TYPE divisor = *other.ui_deque.rbegin();
	BigUnsignedInt remainder(*this);
	*this = 0;
	while(remainder >= other)
	{
		BigUnsignedInt result = remainder / divisor;
		BigUnsignedInt subtrahend(result);
		subtrahend.ui_deque.erase(subtrahend.ui_deque.begin(), subtrahend.ui_deque.begin() + elem_to_move);
		subtrahend *= other;
		if(subtrahend <= remainder)	
         remainder -= subtrahend;
		else
      {
      	BigUnsignedInt result = remainder / (divisor + 1);
		   BigUnsignedInt subtrahend(result);
   		subtrahend.ui_deque.erase(subtrahend.ui_deque.begin(), subtrahend.ui_deque.begin() + elem_to_move);
	   	subtrahend *= other;
         remainder -= subtrahend;
      }
      *this += result;
	}
	if(this->ui_deque.size() >= other.ui_deque.size())
		this->ui_deque.erase(this->ui_deque.begin(), this->ui_deque.begin() + elem_to_move);
	else
		*this = 0;
	return remainder;
}

void BigUnsignedInt::elem_left_shift_by(UI_DEQUE::size_type const &n)
{
	if(!n) return;
	UI_TYPE *insertElems = new UI_TYPE[n]{};
	this->ui_deque.insert(ui_deque.begin(), insertElems, insertElems + n);
	delete insertElems;
}	
inline bool BigUnsignedInt::bit_in_location(UI_TYPE const &ui_elem, int const &location)
{
	bool bit = ((ui_elem & (1ULL << location)) >> location); 	
	return bit;
}
inline bool BigUnsignedInt::is_zero() const
{
	return (this->ui_deque.size() == 1 && this->ui_deque[0] == 0);
}
//end of private methods

//Public methods

BigUnsignedInt::BigUnsignedInt() {this->ui_deque = {0};}
BigUnsignedInt::BigUnsignedInt(const BigUnsignedInt &other) : ui_deque(other.ui_deque){}
BigUnsignedInt::BigUnsignedInt(const UI_TYPE &value) : ui_deque({value}) {}

BigUnsignedInt& BigUnsignedInt::operator=(const BigUnsignedInt &other)
{
	this->ui_deque = other.ui_deque;
	return *this;
}

BigUnsignedInt BigUnsignedInt::operator+=(UI_TYPE const &rhValue)
{
	this->addUnsignedInt(this->ui_deque.begin(), rhValue);
	return *this;
}
BigUnsignedInt BigUnsignedInt::operator-=(UI_TYPE const &rhValue)
{
	this->subtractUnsignedInt(this->ui_deque.begin(), rhValue);
	if(this->ui_deque[this->ui_deque.size() - 1] == 0 && this->ui_deque.size() > 1)
		this->ui_deque.pop_back();
	return *this;
}
BigUnsignedInt BigUnsignedInt::operator*=(UI_TYPE const &rhValue)
{
	this->multiplyUnsignedInt(this->ui_deque.begin(), rhValue);
	return *this;
}
BigUnsignedInt BigUnsignedInt::operator/=(UI_TYPE const &rhValue)
{
	this->divideBigUnsignedInt(this->ui_deque.rbegin(), rhValue);
	if(this->ui_deque[this->ui_deque.size() - 1] == 0 && this->ui_deque.size() > 1)
		this->ui_deque.pop_back();
	return *this;
}
BigUnsignedInt BigUnsignedInt::operator%=(UI_TYPE const &rhValue)
{
	UI_DEQUE remainder = {this->divideBigUnsignedInt(this->ui_deque.rbegin(), rhValue)};
	this->ui_deque = remainder;
	return *this;
}

const BigUnsignedInt BigUnsignedInt::BigUnsignedInt::operator+(UI_TYPE const &rhValue) const
{
	BigUnsignedInt newBUI = *this;
	newBUI += rhValue;
	return newBUI;
}
const BigUnsignedInt BigUnsignedInt::operator-(UI_TYPE const &rhValue) const
{
	BigUnsignedInt newBUI = *this;
	newBUI -=  rhValue;
	return newBUI;
}
const BigUnsignedInt BigUnsignedInt::operator*(UI_TYPE const &rhValue) const
{
	BigUnsignedInt newBUI = *this;
	newBUI *= rhValue;
	return newBUI;
}
const BigUnsignedInt BigUnsignedInt::operator/(UI_TYPE const &rhValue) const
{
	BigUnsignedInt newBUI = *this;
	newBUI /= rhValue;
	return newBUI;
}
const BigUnsignedInt BigUnsignedInt::operator%(UI_TYPE const &rhValue) const
{
	BigUnsignedInt newBUI = *this;
	newBUI %= rhValue;
	return newBUI;
}

BigUnsignedInt& BigUnsignedInt::operator+=(BigUnsignedInt const &other)
{
	if(this->ui_deque.size() < other.ui_deque.size())
		this->ui_deque.resize(other.ui_deque.size());
	for(decltype(other.ui_deque.size()) i = 0; i != other.ui_deque.size(); ++i)
		this->addUnsignedInt(this->ui_deque.begin() + i, other.ui_deque[i]);
	return *this;
}
BigUnsignedInt& BigUnsignedInt::operator-=(BigUnsignedInt const &other)
{
	if(this->ui_deque.size() < other.ui_deque.size())
		throw std::underflow_error("Underflow error");
	auto i = other.ui_deque.size();
	do {
		--i;
		this->subtractUnsignedInt(this->ui_deque.begin() + i, other.ui_deque[i]);
	} while (i != 0);
	if (this->ui_deque[this->ui_deque.size() - 1] == 0 && this->ui_deque.size() > 1)
		this->ui_deque.pop_back();
	return *this;
		
}
BigUnsignedInt& BigUnsignedInt::operator*=(BigUnsignedInt const &other)
{
	BigUnsignedInt bufferBUI = *this;
	*this = 0;
	for(UI_DEQUE::size_type i = 0; i != other.ui_deque.size(); ++i)
	{
		BigUnsignedInt productBUI = bufferBUI;
		productBUI.multiplyUnsignedInt(productBUI.ui_deque.begin(), other.ui_deque[i]);
		productBUI.elem_left_shift_by(i);
		*this += productBUI;
	}
	return *this;
}
BigUnsignedInt& BigUnsignedInt::operator/=(BigUnsignedInt const &other)
{
	if(other == 0ULL)
		throw std::runtime_error("Divide by zero exception.");
	if(other == 1ULL)
		return *this;
	if(other.ui_deque.size() == 1)
	{
		*this /= other.ui_deque[0];
		return *this;
	}
	this->divideBigUnsignedInt(other);
	return *this;
}
BigUnsignedInt& BigUnsignedInt::operator%=(BigUnsignedInt const &other)
{
	if(other == 0ULL)
		throw std::runtime_error("Divide by zero exception.");
	if(other == 1ULL)
	{
		*this = 0ULL;
		return *this;
	}
	if(other.ui_deque.size() == 1)
	{
		*this %= other.ui_deque[0];
		return *this;
	}
	*this = this->divideBigUnsignedInt(other);
	return *this;
}

const BigUnsignedInt BigUnsignedInt::operator+(BigUnsignedInt const &other)  const
{
	BigUnsignedInt newBUI = *this;
	newBUI += other;
	return newBUI;
}
const BigUnsignedInt BigUnsignedInt::operator-(BigUnsignedInt const &other)  const
{
	BigUnsignedInt newBUI = *this;
	newBUI -= other;
	return newBUI;
}
const BigUnsignedInt BigUnsignedInt::operator*(BigUnsignedInt const &other)  const
{
	BigUnsignedInt newBUI = *this;
	newBUI *= other;
	return newBUI;
}
const BigUnsignedInt BigUnsignedInt::operator/(BigUnsignedInt const &other)  const
{
	BigUnsignedInt newBUI = *this;
	newBUI /= other;
	return newBUI;
}
const BigUnsignedInt BigUnsignedInt::operator%(BigUnsignedInt const &other) const
{
	BigUnsignedInt newBUI = *this;
	newBUI %= other;
	return newBUI;
}

const bool BigUnsignedInt::operator==(UI_TYPE const &rhValue) const
{
	if(this->ui_deque.size() != 1)
		return false;
	return this->ui_deque[0] == rhValue;
}
const bool BigUnsignedInt::operator!=(UI_TYPE const &rhValue) const
{
	return !(*this == rhValue);
}
const bool BigUnsignedInt::operator> (UI_TYPE const &rhValue) const
{
	if(this->ui_deque.size() > 1)
		return true;
	return this->ui_deque[0] > rhValue;
}
const bool BigUnsignedInt::operator< (UI_TYPE const &rhValue) const
{
	if(this->ui_deque.size() != 1)
		return false;
	return this->ui_deque[0] < rhValue;
}
const bool BigUnsignedInt::operator>=(UI_TYPE const &rhValue) const
{
	return (*this > rhValue || *this == rhValue);
}
const bool BigUnsignedInt::operator<=(UI_TYPE const &rhValue) const
{
	return (*this < rhValue || *this == rhValue);
}

const bool BigUnsignedInt::operator==(BigUnsignedInt const &other) const
{
	if(this->ui_deque.size() != other.ui_deque.size())
		return false;
	for(UI_DEQUE::size_type i = 0; i != other.ui_deque.size(); ++i)
		if(this->ui_deque[i] != other.ui_deque[i])
			return false;
	return true;
}
const bool BigUnsignedInt::operator!=(BigUnsignedInt const &other) const
{
	return !(*this == other);
}
const bool BigUnsignedInt::operator> (BigUnsignedInt const &other) const
{
	if(this->ui_deque.size() < other.ui_deque.size())
		return false;
	if(this->ui_deque.size() > other.ui_deque.size())
		return true;
	auto rIter = this->ui_deque.rbegin();
	for(auto orIter = other.ui_deque.rbegin(); orIter != other.ui_deque.rend(); ++orIter)
	{
		if(*rIter > *orIter)
			return true;
		else if(*rIter < *orIter)
			return false;
		++rIter;
	}
	return false;
}
const bool BigUnsignedInt::operator< (BigUnsignedInt const &other) const
{
	if(this->ui_deque.size() > other.ui_deque.size())
		return false;
	if(this->ui_deque.size() < other.ui_deque.size())
		return true;
	auto rIter = this->ui_deque.rbegin();
	for(auto orIter = other.ui_deque.rbegin(); orIter != other.ui_deque.rend(); ++orIter)
	{
		if(*rIter < *orIter)
			return true;
		else if(*rIter > *orIter)
			return false;
		++rIter;
	}
	return false;
}
const bool BigUnsignedInt::operator>=(BigUnsignedInt const &other) const
{
	return (*this > other || *this == other);
}
const bool BigUnsignedInt::operator<=(BigUnsignedInt const &other) const
{
	return (*this < other || *this == other);
}

// Friend functions.  

const BigUnsignedInt operator+(BigUnsignedInt::UI_TYPE const &lhValue, BigUnsignedInt const &bui)
{
	return bui + lhValue;
}
const BigUnsignedInt operator-(BigUnsignedInt::UI_TYPE const &lhValue, BigUnsignedInt const &bui)
{	
	if(lhValue > bui)
	{
		BigUnsignedInt newBUI;	
		newBUI = lhValue - bui.ui_deque[0];
		return newBUI;
	}
	else
		throw std::underflow_error("Underflow error");
}
const BigUnsignedInt operator*(BigUnsignedInt::UI_TYPE const &lhValue, BigUnsignedInt const &bui)
{
	return bui * lhValue;
}
const BigUnsignedInt operator/(BigUnsignedInt::UI_TYPE const &lhValue, BigUnsignedInt const &bui)
{	
	BigUnsignedInt newBUI;
	if(lhValue >= bui)
		newBUI = lhValue / bui.ui_deque[0];
	return newBUI;
}
const BigUnsignedInt operator%(BigUnsignedInt::UI_TYPE const &lhValue, BigUnsignedInt const &bui)
{
	BigUnsignedInt newBUI;
	if(lhValue >= bui)
		newBUI = lhValue % bui.ui_deque[0];
	else
		newBUI = lhValue;
	return newBUI;
}

const bool operator==(BigUnsignedInt::UI_TYPE const &lhValue, BigUnsignedInt const &bui)
{
	return (bui == lhValue);
}
const bool operator!=(BigUnsignedInt::UI_TYPE const &lhValue, BigUnsignedInt const &bui)
{
	return (bui != lhValue);
}
const bool operator> (BigUnsignedInt::UI_TYPE const &lhValue, BigUnsignedInt const &bui)
{
	return (bui < lhValue);
}
const bool operator< (BigUnsignedInt::UI_TYPE const &lhValue, BigUnsignedInt const &bui)
{
	return (bui > lhValue);
}
const bool operator>=(BigUnsignedInt::UI_TYPE const &lhValue, BigUnsignedInt const &bui)
{
	return (bui <= lhValue);
}
const bool operator<=(BigUnsignedInt::UI_TYPE const &lhValue, BigUnsignedInt const &bui)
{
	return (bui >= lhValue);
}

// End of friend functions

const std::string BigUnsignedInt::toString() const
{
	std::string decimal_display;
	if(this->is_zero())
	{
		decimal_display = "0";
		return decimal_display;
	}
	BigUnsignedInt tempBUI(*this);
	while(!tempBUI.is_zero())
	{
		int remainder_of_10 = tempBUI.divideBigUnsignedInt(tempBUI.ui_deque.rbegin(), 10);
		if(tempBUI.ui_deque[tempBUI.ui_deque.size() - 1] == 0 && tempBUI.ui_deque.size() > 1)
			tempBUI.ui_deque.pop_back();
		decimal_display = std::to_string(remainder_of_10) + decimal_display;
	}
	return decimal_display;
}
