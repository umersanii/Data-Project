#pragma once
#include "Classes.h"

#include <iostream>
#include <windows.h>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <fstream>
#include <stdlib.h>


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
using std::ofstream;
using std::ifstream;
using std::getline;
using std::stringstream;

extern string Dir;


void createFolderWithCurrentTime(const wstring& parentPath);
int CalculateHash(string file, int identifierSpace);
CircularLinkedList* makeNumberOfMachines(int n);
void  manuallyAssignIDs(CNode* Cll);
void insertFile(string Dir);
void deleteFile(string Dir);
void relocateFile(string source, string destination);
void addDatainMachines();
void createFolder(string name);
void mergeBTrees(BTree* source, BTree* destination);


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
CircularLinkedList* makeNumberOfMachines(int n)
{
	char choice;
	bool flag = true;
enteragain:
	cout<<"Would you like to add the machines ID manually? (y/n): \n";
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		flag = false;
	}
	else if (choice == 'n' || choice == 'N')
	{
		flag = true;
	}
	else
	{
		cout << "Invalid Choice. Enter again\n";
		goto enteragain;
	}
	CircularLinkedList* Clist = new CircularLinkedList();
	for (int i = 0; i < n; i++)
	{
		Clist->insert(i);
		if (flag == true)
		{
			createFolder(to_string(i));
		}
	}

	if(flag == false)
	{
		manuallyAssignIDs(Clist->getHead());

	}
	return Clist;
}

void  manuallyAssignIDs(CNode* Cll)
{
	CNode* tempHead = Cll;
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
		createFolder(to_string(tempID));
	}

}	

template <typename t>
void insertaNewMachine(CircularLinkedList* Cll)
{
	int ID;
	cout << "Enter the Machine ID: ";
	cin >> ID;
	Cll->insert(ID);
	cout<<"\nMachine Added Successfully\n";

	createFolder(to_string(ID));
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


void createFolder(string name)
{
	
	wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	wstring folderName = converter.from_bytes(name);

	wstring wideFolderPath = converter.from_bytes(Dir + "\\" + name);
	string tDir = converter.to_bytes(wideFolderPath);
	if (CreateDirectory(wideFolderPath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{
		wcout << L"Folder '" << folderName << L"' created successfully." << endl;
	}
	else
	{
		DWORD error = GetLastError();
		if (error == ERROR_PATH_NOT_FOUND)
		{
			wcerr << L"One or more intermediate directories do not exist." << endl;
		}
		else
		{
			wcerr << L"Failed to create folder. Error code: " << error << endl;
		}
	}
}


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

void insertFile(string dir)
{
	
	string fileName;
	cout << "Enter File Name: ";
	cin >> fileName;
	fileName = fileName + ".txt";
	string filePath = dir + "\\" + fileName;
	string line;
	stringstream content;
	cout << "Input the text you want to write to the file. Type 141 to exit\n";
	while (true) 
	{
		getline(cin, line);

		if (line == "141") 
		{
			break;
		}
		content << line << '\n';

	}

	ofstream outputFile(filePath);
	if (outputFile.is_open()) 
	{
		outputFile << content.str() << endl;
		outputFile.close();

		cout << "File created successfully: " << fileName << std::endl;
	}
	else
	{
		cerr << "Error opening file: " << fileName << std::endl;
	
	}


}

void deleteFile(string Dir)
{
	string fileName;


	cout << "Enter File Name: ";
	cin >> fileName;

	string filePath = Dir + "\\" + fileName + ".txt";
	if (remove(filePath.c_str()) != 0)
		perror("Error deleting file");
	else
		puts("File successfully deleted");
}

void relocateFile(string source, string destination)
{
	ifstream inputFile(source);
	string fileName;
	if (!inputFile.is_open()) {
		cerr << "Error opening file: " << source << std::endl;
		return;
	}

	stringstream contentStream;
	contentStream << inputFile.rdbuf();
	inputFile.close();

	int found = source.find_last_of("/\\");
	if (found != string::npos) 
	{
		fileName = source.substr(found + 1);
	}
	else 
	{
		fileName = source;
	}
	cout << fileName;
	if (remove(source.c_str()) != 0)
		perror("Error deleting file");
	else
		puts("File successfully deleted");
	destination = destination + "\\" + fileName;
	ofstream outputFile(destination);
	if (outputFile.is_open())
	{
		outputFile << contentStream.str() << endl;
		outputFile.close();

		cout << "File created successfully: " << fileName << std::endl;
	}
	else
	{
		cerr << "Error opening file: " << fileName << std::endl;

	}

}

void addDatainMachines(CircularLinkedList* Cll)
{
	int c = 0;
	CNode* tempHead = Cll->getHead();
	cout<<"Enter data in Machines\n"; 
	for (int i = 0; i < Cll->getCount(); i++)
	{
		cout<<"Enter No of Files you want to add for Machine with ID: "<<Cll->getHead()->getID()<<": \n";
		cin >> c;
		for (int i = 0; i < c; i++)
		{
			string dir = Dir + "\\" + to_string(tempHead->getID());
			insertFile(dir);
			tempHead = tempHead->getNext();

		}

	}
}

void mergeBTrees(BTree* source, BTree* destination)
{
	cout << "\n\n\n";
	source->traverse();
	source->getTotalKeys();
	cout << "\n\n\n";


	Key* keyarray = new Key[source->getTotalKeys()];
	source->returnkeys(keyarray, source->getTotalKeys());
	for (int i = 0; i < source->getTotalKeys(); i++)
	{
		destination->insertion(keyarray[i]);
	}
	for (int i = 0; i < source->getTotalKeys(); i++)
	{
		source->deletion(keyarray[i].key);
	}
	source->root = nullptr;
	delete[] keyarray;
	return;
}