#include <iostream>
#include "Classes.h"
#include "HelpingFunctions.h"


using std::cout;
using std::cin;
using std::endl;
using std::string;
int main()
{
	//cout << "Rom Rom";
	cout << CalculateHash("Hello", 100);
	return 0;

	CircularLinkedList<string> list;
	list.insert("Hello");
	list.insert("World");
	list.insert("!");
	list.print();
	list.deleteData("World");
	list.print();
	return 0;
}