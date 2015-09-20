#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <exception>
#include "BigUnsignedInt.h"

using namespace std;

int main()
{
	BigUnsignedInt x(1);
	for(int i = 0; i != 128; ++i)
		x *= 2;
	
	BigUnsignedInt y(1);
	for(int i = 0; i != 64; ++i)
		y *= 2;

	cout << x.toString() << " + " << y.toString() << " + " << 
		1 << " = " << (x + y + 1).toString() << endl;

	x += y + 1;

	srand(time(NULL));
	
	// Writing a simple python script to quickly test results
	ofstream pyfile;
	pyfile.open("TestCalc.py");
	//Standard operators by int types
	
	pyfile << "print('Operation BigUnsignedInt + integer')" << endl;
	for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();	
		pyfile << "print(" << x.toString() << " + " << rn << " == "
			<< (x + rn).toString() << ")" << endl;
	}
	
	pyfile << "print('Operation BigUnsignedInt - integer')" << endl;
	for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();	
		pyfile << "print(" << x.toString() << " - " << rn << " == "
			<< (x - rn).toString() << ")" << endl;
	}

	pyfile << "print('Operation BigUnsignedInt * integer')" << endl;
	for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();	
		pyfile << "print(" << x.toString() << " * " << rn << " == "
			<< (x * rn).toString() << ")" << endl;
	}

	pyfile << "print('Operation BigUnsignedInt / integer')" << endl;
	for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();
		if (!rn) rn = 1;
		pyfile << "print(" << x.toString() << " // " << rn << " == "
			<< (x / rn).toString() << ")" << endl;
	}

		for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();
		if (!rn) rn = 1;
		pyfile << "print(" << x.toString() << " % " << rn << " == "
			<< (x % rn).toString() << ")" << endl;
	}

	//Standard operators by BUI types
	
	y += 1;

	pyfile << "print('Operation BigUnsignedInt + BigUnsignedInt')" << endl;
	for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();	
		pyfile << "print(" << x.toString() << " + " << (y*rn).toString() << " == "
			<< (x + (y*rn)).toString() << ")" << endl;
	}

	pyfile << "print('Operation BigUnsignedInt - BigUnsignedInt')" << endl;
	for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();	
		pyfile << "print(" << x.toString() << " - " << (y*rn).toString() << " == "
			<< (x - (y*rn)).toString() << ")" << endl;
	}

	pyfile << "print('Operation BigUnsignedInt * BigUnsignedInt')" << endl;
	for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();	
		pyfile << "print(" << x.toString() << " * " << (y*rn).toString() << " == "
			<< (x * (y*rn)).toString() << ")" << endl;
	}

	pyfile << "print('Operation BigUnsignedInt / BigUnsignedInt')" << endl;
	for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();
		if (!rn) rn = 1;
		pyfile << "print(" << x.toString() << " // " << (y*rn).toString() << " == "
			<< (x / (y*rn)).toString() << ")" << endl;
	}

	pyfile << "print('Operation BigUnsignedInt % BigUnsignedInt')" << endl;
	for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();
		if (!rn) rn = 1;
		pyfile << "print(" << x.toString() << " % " << (y*rn).toString() << " == "
			<< (x % (y*rn)).toString() << ")" << endl;
	}

	// Friend operators

	pyfile << "print('Operation Int + BigUnsignedInt')" << endl;
	for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();
		BigUnsignedInt z = rand();	
		pyfile << "print(" << rn << " + " << z.toString() << " == "
			<< (rn + z).toString() << ")" << endl;
	}

	pyfile << "print('Operation Int -BigUnsignedInt')" << endl;
	for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();
		BigUnsignedInt z = rand();	
		try
		{
			pyfile << "print(" << rn << " - " << z.toString() << " == "
				<< (rn - z).toString() << ")" << endl;
		}
		catch(exception &e)
		{
			pyfile << "print('" << e.what() << "')" << endl;
		}
	}

	pyfile << "print('Operation Int * BigUnsignedInt')" << endl;
	for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();
		BigUnsignedInt z = rand();
		pyfile << "print(" << rn << " * " << z.toString() << " == "
			<< (rn * z).toString() << ")" << endl;
	}

	pyfile << "print('Operation Int / BigUnsignedInt')" << endl;
	for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();
		BigUnsignedInt z = rand();
		if (z == 0) z = 1;
		pyfile << "print(" << rn << " // " << z.toString() << " == "
			<< (rn / z).toString() << ")" << endl;
	}

	pyfile << "print('Operation Int % BigUnsignedInt')" << endl;
	for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();
		BigUnsignedInt z = rand();
		if (z == 0) z = 1;
		pyfile << "print(" << rn << " % " << z.toString() << " == "
			<< (rn % z).toString() << ")" << endl;
	}

	pyfile.close();

	return 0;
}
