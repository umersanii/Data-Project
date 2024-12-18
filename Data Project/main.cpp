#include <iostream>
#include "Classes.h"
#include "HelpingFunctions.h"
#include "BTree.h"
#include <stack>

using std::cout;
using std::cin;
using std::endl;
using std::string;
string Dir;


int main()
{
   

    createFolderWithCurrentTime(Dir);
    int n = 2;
    CircularLinkedList* Clist = makeNumberOfMachines(n); 
     // Makes n Number of Nodes for Circular Linked List specified in the requirements
    addDatainMachines(Clist);
    cout << "The Circular Linked List is: ";
    Clist->printWhole();
    manuallyAssignIDs(Clist->getHead());  // Manually assigns IDs to the Nodes of the Circular Linked List
    //insertaNewMachine(Clist);  // Inserts a new Machine in the Circular Linked List

    // Prints the Circular Linked List
    
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
        */
}
