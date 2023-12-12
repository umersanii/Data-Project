#include <iostream>
#include "Classes.h"
#include "HelpingFunctions.h"
#include "BTree.h"


using std::cout;
using std::cin;
using std::endl;
using std::string;
int main()
{
    BTree t(3);
    t.insertion(8);
    t.insertion(9);
    t.insertion(10);
    t.insertion(11);
    t.insertion(15);
    t.insertion(16);
    t.insertion(17);
    t.insertion(18);
    t.insertion(20);
    t.insertion(23);

    cout << "The B-tree is: ";
    t.traverse();

    int k = 10;
    (t.search(k) != NULL) ? cout << endl
        << k << " is found"
        : cout << endl
        << k << " is not Found";

    k = 2;
    (t.search(k) != NULL) ? cout << endl
        << k << " is found"
        : cout << endl
        << k << " is not Found\n";

    /*
    BTree t(3);
    t.insertion(8);
    t.insertion(9);
    t.insertion(10);
    t.insertion(11);
    t.insertion(15);
    t.insertion(16);
    t.insertion(17);
    t.insertion(18);
    t.insertion(20);
    t.insertion(23);

    cout << "The B-tree is: ";
    t.traverse();

    t.deletion(20);

    cout << "\nThe B-tree is: ";
    t.traverse();
    */
	//cout << "Rom Rom";
	cout << CalculateHash("Hello", 100)<<"\n";
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


