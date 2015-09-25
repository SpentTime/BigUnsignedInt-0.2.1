#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <fstream>
#include "BigUnsignedInt.h"

using namespace std;

int main()
{
   BigUnsignedInt x(1), y(1), z;
   ofstream pyTestCalc;
   pyTestCalc.open("PyTestCalc.py");   

   pyTestCalc << "#!/usr/bin/env python3\n" << endl;

   srand(time(NULL));
   
   for(short i = 0; i != 100; ++i)
   {
      for(int i = 0; i != 128; ++i)
         x *= 2;
      x *= rand();      
      
      for(int i = 0; i != 64; ++i)
         y *= 2;

      x = y * rand() + rand();

      y = y * rand() + rand();

      z = x / y;      

      pyTestCalc << "if not " << x.toString() <<  " // " <<  y.toString()<< " == " << z.toString()  << ":\n"
         << "\tprint('exe answer: " << z.toString() << " ')\n"
         << "\tprint('py answer: {0}', " << x.toString() << " / " << y.toString() << " )"
         << endl;
      
   }
   pyTestCalc.close();

   system("python3 ./PyTestCalc.py");

   return 0;
}
