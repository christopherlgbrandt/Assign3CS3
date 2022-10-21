/*
	This file contains the implementation for class file.

	Sherine Antoun
    Colorado Mesa University
*/

#include <iostream>
#include <fstream>
#include "file.h"
using namespace std;

// the default constructor should just initialise the private members to nothing

file::file()
{

}


// initialisation constructor to associate file with class instance
// allocated appropriate segments on the heap.

file::file(char filename[])
{
	fileName = filename;
}

// associated method takes a file, seeks to end, allocates memory on heap then copies
// contents into buffer

void file::associate(char filename[])
{
	
}

void file::write(char filename[])
{
	ifstream fin;
	ofstream fout;
	string fileInfo;
	fin.open(fileName);
	fout.open("newFile.txt");
	while (!fin.eof())
	{
		fin >> fileInfo;
		fout << fileInfo;
	}
}
		
void file::print(char filename[])
{

}

void file::reverse(char filename[])
{

}
