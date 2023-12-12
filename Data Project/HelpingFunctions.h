#pragma once

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;


int CalculateHash(string file, int identifierSpace)
{
    int hash = 0;
    for (int i = 0; i < file[i]!= NULL; i++)
    {
		hash += file[i];
		hash *= 'A';
		hash *= 'S';
		hash *= 'U';
	}
	return hash % identifierSpace;
}


