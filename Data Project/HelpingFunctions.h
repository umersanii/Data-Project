#pragma once
#include "Classes.h"
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

/////////////////
template <class t>
CircularLinkedList<t>* makeNumberOfMachines(int n)
{
	CircularLinkedList<t>* Clist = new CircularLinkedList<t>();
	for (int i = 0; i < n; i++)
	{
		Clist->insert(i);
	}

	return Clist;
}

template <typename t>
void  manuallyAssignIDs(CNode<t>* Cll)
{
	CNode<t>* tempHead = Cll;
	bool flag = true;
	cout << "Enter IDs for the Machine One by One. \n";
	int c = 1;
	while (Cll != nullptr) 
	{
		cout << "Enter ID for Machine " << c++ << ": ";
		int tempID;
		cin >> tempID;
		Cll->setID(tempID);

		Cll = Cll->getNext();

		if (tempHead == Cll && flag != true)
			break;

		flag = false;
	}

}	

template <typename t>
void insertaNewMachine(CircularLinkedList<t>* Cll)
{
	int ID;
	cout << "Enter the Machine ID: ";
	cin >> ID;
	Cll->insert(ID, ID);
	cout<<"\nMachine Added Successfully\n";
	return;
	
}