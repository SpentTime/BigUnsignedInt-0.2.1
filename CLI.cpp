/*
* CLI.cpp
*
*	Created on: Sep 12, 2015
*		Author: Justin Sepulveda
*
*	Simple CLI to interface with my BigUnsignedInt class, and...
*	So far it is ugly.  I think I"ll rewrite this thing using OOP
*	to see if that somehow improves it.
* 
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <exception>
#include "BigUnsignedInt.h"

using namespace std;

inline void do_work(string input = "")
{
	bool again = !input.length();
	bool cli_arg = !again;
	BigUnsignedInt ans;
	
	do
	{
		if(again) getline(cin, input);
		istringstream buffer(input);
		istream_iterator<string> beg(buffer), end;
		vector<string> tokens(beg, end);
		char operation = 0;
		
		for(string &token : tokens)
		{
			// BigUnsignedInt n = 0;
			unsigned long long n = 0;
			
			if (token == "exit")
			{
				again = false;
				break;
			}

			if((token == "+" || token == "-" ||
				token == "*" || token == "/" || token == "%"))
			{
				if(!operation)
				{
					operation = token[0];
					continue;
				}
				else
				{
					cout << "Did you forget to type a number "
							"between those two operations?"<< endl;
					break;
				}			
			}
			else
			{
				try
				{
					n = stoull(token);
				}
				catch(exception &e)
				{
					cout << "Invalid number or operations."
							"Please try again or type 'exit'" << endl;
					break;
				}
			}
			
			switch (operation)
			{
			case '+':
				ans = ans + n;
				operation = 0;
				break;
			case '-':
				ans = ans - n;
				operation = 0;
				break;
			case '*':
				ans = ans * n;
				operation = 0;
				break;
			case '/':
				ans = ans / n;
				operation = 0;
				break;
			case '%':
				ans = ans % n;
				operation = 0;
				break;
			default:
				ans = n;
				break;
			}
		}
		if (again || cli_arg)
			cout << ans.toString() << endl;
	}while(again);
}

int main(int argc, char *argv[])
{
	try
	{
		if(argc == 1)		
			do_work();
		else
		{
			string input = "";
			for(int i = 1; i != argc; ++i)
				input = input + argv[i] + " ";
			input[input.length() - 1] = '\n';
			do_work(input);
		}
	}
	catch(exception &e)
	{
		cout << e.what() << endl;
	}
	return 0;
}
