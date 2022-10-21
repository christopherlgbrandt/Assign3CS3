/*
	Driver program for file class..
	
    Sherine Antoun
    Colorado Mesa University
	
    This is what you should see on the terminal.
	
	Printing without skipping (forward) 
	The cat sat on the mat

	Printing without skipping (reverse) 

	tam eht no tas tac ehT

	Printing with 1 skip (forward) 
	Tectsto h a

	Printing with 1 skip (reverse) 

	a h otstceT
*/

#include <iostream>
#include "file.h"
using namespace std;

int main()
{
	file f1("dataset.txt");
	
	cout << "Printing without skipping (forward) " << endl;
	f1.print(0);

	cout << "Printing without skipping (reverse) " << endl;
	f1.reverse(0);

	cout << "Printing with 1 skip (forward) " << endl;
	f1.print(1);

	cout << "Printing with 1 skip (reverse) " << endl;
	f1.reverse(1);

	f1.write("dataset2.txt");

	return 0;
}

