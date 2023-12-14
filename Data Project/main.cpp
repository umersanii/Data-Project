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
    BTree t1(3);
    t1.insertion(Key(8, "Value8"));
    t1.insertion(Key(9, "Value9"));
    t1.insertion(Key(10, "Value10"));
    Key * keyarray = new Key[t1.getTotalKeys()];
    t1.traverse();
    cout << "\n";

    // Create and insert into the second B-tree (t2)
    BTree t2(3);
    t2.insertion(Key(11, "Value11"));
    t2.insertion(Key(12, "Value12"));
    t2.insertion(Key(13, "Value13"));
    cout << "B-tree t2: ";
    t2.traverse();
    cout << "\n";

    // Merge t2 into t1
    mergeBTrees(&t1, &t2);

    cout << "Merged B-tree t2 into t1: ";
    t1.traverse();
    cout << "\n";

    cout << "B-tree t2 after merge: ";
    t2.traverse();
    cout << "\n";

    // Create and insert into a third B-tree (t3)
    BTree t3(3);
    t3.insertion(Key(20, "Value20"));
    t3.insertion(Key(21, "Value21"));
    t3.insertion(Key(22, "Value22"));

    cout << "B-tree t3: ";
    t3.traverse();
    cout << "\n";

    // Merge t1 and t3
    mergeBTrees(&t3, &t2);

    cout << "B-tree t2: ";
    t2.traverse();
    cout << "\n";

    cout << "B-tree t3: ";
    t3.traverse();
    cout << "\n";


    createFolderWithCurrentTime(Dir);
    int n = 2;
    CircularLinkedList* Clist = makeNumberOfMachines(n);  // Makes n Number of Nodes for Circular Linked List specified in the requirements
    addDatainMachines(Clist);
    //manuallyAssignIDs(Clist->getHead());  // Manually assigns IDs to the Nodes of the Circular Linked List
    //insertaNewMachine(Clist);  // Inserts a new Machine in the Circular Linked List

    cout << "The Circular Linked List is: ";
    Clist->printID();  // Prints the Circular Linked List

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
