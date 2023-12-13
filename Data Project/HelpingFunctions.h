#pragma once
#include "Classes.h"
#include <iostream>

#include <iostream>
#include <windows.h>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <locale>
#include <codecvt>

using std::string;
using std::wstring;
using std::chrono::system_clock;
using std::time_t;
using std::tm;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::put_time;
using std::wstringstream;
using std::wcout;
using std::wcerr;
using std::cout;
using std::cin;
using std::endl;

void createFolderWithCurrentTime(const wstring& parentPath);
int CalculateHash(string file, int identifierSpace);
template <class t>
CircularLinkedList<t>* makeNumberOfMachines(int n);
template <typename t>
void  manuallyAssignIDs(CNode<t>* Cll);


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
	Cll->insert(ID);
	cout<<"\nMachine Added Successfully\n";
	return;
	
}

//void MergeBTrees(BTree* source, BTree* destination)
//{
//	int c = source->root->t;
//	for (int i = 0; i < c; i++)
//	{
//		string content = source->root->content;
//		int key = source->root->key;
//		
//		//destination->insertion(source->root->);
//	}
//}




void createFolderWithCurrentTime(string &Dir)
{
	system_clock::time_point nowTimePoint = system_clock::now();
	time_t currentTime = system_clock::to_time_t(nowTimePoint);
	string curDir = "MachineData";
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	wstring wideCurDir = converter.from_bytes(curDir);
	tm localTime;
	localtime_s(&localTime, &currentTime);
	wstringstream ss;
	ss << put_time(&localTime, L"%d-%m %H-%M-%S");
	wstring folderName = ss.str();

	wstring wideFolderPath = wideCurDir + L"\\" + folderName;
	Dir = converter.to_bytes(wideFolderPath);
	if (CreateDirectory(wideFolderPath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{
		wcout << L"Folder '" << folderName << L"' created successfully." << std::endl;
	}
	else
	{
		DWORD error = GetLastError();
		if (error == ERROR_PATH_NOT_FOUND)
		{
			wcerr << L"One or more intermediate directories do not exist." << std::endl;
		}
		else
		{
			wcerr << L"Failed to create folder. Error code: " << error << std::endl;
		}
	}
}
