#include <iostream>
#include "BigUnsignedInt.h"

int main()
{
	BigUnsignedInt x(1);
	for(int i = 0; i != 128; ++i)
		x *= 2;
	BigUnsignedInt y = x, ans;

	ans = x / y;
	std::cout << x.toString() << " / " << y.toString() 
		<< ": " << ans.toString () << std::endl;
	ans = y / x;
	std::cout << y.toString() << " / " << x.toString() 
		<< ": " << ans.toString () << std::endl;
	
	BigUnsignedInt temp(1);
	for(int i = 0; i != 64; ++i)
		temp *= 2;
	temp *= 3;

	x += temp * 4 + 6;
	y += temp + 6;
	
	x *= 6;
	
	ans = x/ y;
	std::cout << x.toString() << " / " << y.toString() 
		<< ": " << ans.toString () << std::endl;
	ans = y / x;
	std::cout << y.toString() << " / " << x.toString() 
		<< ": " << ans.toString () << std::endl;

	std::cout << "x < y " << (x < y) << std::endl;
	std::cout << "x > y " << (x > y) << std::endl;

	std::cout << "357 / " << x.toString() << ":" << 
			(357 / x).toString();	

	BigUnsignedInt z(3032);
	
	std::cout << "100034324 / " << z.toString() << ":" <<
			(100034324 / z).toString();

	return 0;
}
