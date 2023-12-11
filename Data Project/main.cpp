#include <iostream>
#include "Classes.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
int main()
{
	CircularLinkedList<string> list;
	list.insert("Hello");
	list.insert("World");
	list.insert("!");
	list.print();
	list.deleteData("World");
	list.print();
	return 0;
}