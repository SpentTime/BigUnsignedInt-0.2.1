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

	x += y + 1;

	srand(time(NULL));
	
	// Writing a simple python script to quickly test results
	ofstream pyfile;
	pyfile.open("TestCalc.py");
	pyfile << "#!/usr/bin/env python3" << endl;
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
		auto rn1 = rand();
      auto rn2 = rand();	
		pyfile << "print(" << (x*rn1).toString() << " * " << (y*rn2).toString() << " == "
			<< ((x*rn1) * (y*rn2)).toString() << ")" << endl;
	}

	pyfile << "print('Operation BigUnsignedInt / BigUnsignedInt')" << endl;
	for(int i = 0; i != 5; ++i)
	{
		auto rn = rand();
		if (!rn) rn = 1;
		pyfile << "print(" << x.toString() << " // " << (y*rn).toString() << " == "
			<< (x / (y*rn)).toString() << ")" << endl;
      pyfile << "print('Remainder: ', " << (x % (y*rn)).toString() << ")"<< endl;
		pyfile << "print('error: ', " << x.toString() << " // " << (y*rn).toString() << " - "
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

	system("chmod +x ./TestCalc.py");
	system("./TestCalc.py");

	return 0;
}
