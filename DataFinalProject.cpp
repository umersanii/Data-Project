#include <iostream>
#include"CircularList.h"
#include"BTree.h"
#include<cmath>
#include <sstream>
#include<vector>
#include"helperFunctions.h"
std::string Dir = R"(C:\Users\ammaa\OneDrive\Desktop\code1\DataFinalProject\DataFinalProject\MachineData)";
using std::cout;
using std::cin;
using std::getline;
int main() {
    vector<int> ids;
    vector<string> idsInString;
    int choice = 0;
    int orderBtree = 0;
    int numberOfActiveMachines = 0;
    int identifierSpace = 0;
    bool assignedID = false;
    bool AssignedSpace = false;
    int maxMachines = 0;
    {
        std::cout << "                              \033[1;31mTriUnity File System\033[0m\n"; // Red color
        cout << endl << endl;
        std::cout << "                 \033[1;32mDevelopers: Umer Sani, Umer Ali, Ammaar Ahmed\033[0m\n"; // Green color
        cout << endl << endl;
        std::cout << "                      \033[1;35mLet's Start Building the System ;)\033[0m\n"; // Green color
        cout << endl << endl;
        // identifier space 
        if (AssignedSpace == false) {
            cout << "Enter the Identifier Space : ";
            cin >> identifierSpace;
            maxMachines = pow(2, identifierSpace);
            cout << "Enter B-Tree Order Of Each Machine : ";
            cin >> orderBtree;
            
        }
        AssignedSpace = true;
        // Currently Active Machines and Assigning ID's to them 
        if (AssignedSpace == true) {
            cout << "Enter number of Currently Active Machines : ";
            cin >> numberOfActiveMachines;
            cout << "Press 1 to Manually assign ID's to each machine using Each Machine's Name Or Press 2 to Automatically Assign ID's, " << endl;
            cout << "alternatively Press 3 to Manually Assign Id's to Each Machine by Giving int ID's :";
            int temp = 0;
            cin >> temp;
            if (temp == 1) {
                for (int i = 0; i < numberOfActiveMachines; i++)
                {
                    cout << "Enter Name of Machine (" << i + 1 << ") :";
                    string temp;
                    cin >> temp;
                    idsInString.push_back(temp);
                }
                convertStringVectorToIntVector(ids, idsInString,identifierSpace);
                sortVectorAscending(ids);
               

            }
            else if (temp == 2) {
                generateRandomNumbers(numberOfActiveMachines, maxMachines, ids);
                sortVectorAscending(ids);
               
            }
            else if (temp==3) {
                for (int i = 0; i <numberOfActiveMachines; i++)
                {
                    cout << "Enter Integer ID of Machine (" << i + 1 << ") : ";
                    int temp = 0;
                    cin >> temp;
                    ids.push_back(temp);
                }
                sortVectorAscending(ids);
               
            }
            else {
                cout << "invalid choice !!" << endl;
            }
        }

    } 
    CircularLinkedList CLL(maxMachines, identifierSpace, ids,orderBtree);
    for (int i = 0; i < ids.size(); i++)
    {
        
    }
    printVector(ids);
    CLL.printList();
    
    while (true) {
        std::cout << "                              \033[1;31mTriUnity File System\033[0m\n"; // Red color
        std::cout << "                 \033[1;32mDevelopers: Umer Sani, Umer Ali, Ammaar Ahmed\033[0m\n"; // Green color
        std::cout << endl << endl;
        std::cout << "\033[1;34m1. Insert files in the form of key, value pairs from any machine.\033[0m\n";
        std::cout << "\033[1;34m2. Remove data by specifying the key from any machine.\033[0m\n";
        std::cout << "\033[1;34m3. Print the routing table of any machine.\033[0m\n";
        std::cout << "\033[1;34m4. Add new machines on the fly.\033[0m\n";
        std::cout << "\033[1;34m5. Remove any machine on the fly.\033[0m\n";
        std::cout << "\033[1;34m6. Exit.\033[0m\n";
        std::cout << "\033[1;34m7. Print the Fly\033[0m\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            int temp123;
            cout << "Enter the Machine From Which you would like to add file :";
            cin >> temp123;
            CLL.AddFile(temp123);
            break;
        case 2:
            // Remove data by specifying the key from any machine
            break;
        case 3:
            // Print the routing table of any machine
            cout << "Enter The ID of the Machine Whose Routing Table you wish to print : ";
            int temp1;
            cin >> temp1;
            CLL.printROutingTable(temp1);
            break;
        case 4:
            int temp2;
            cout << "Enter the Node you wish to Add : ";
            cin >> temp2;
            CLL.addNodeAfterInitialization(temp2);
            break;
        case 5:
            // Remove any machine on the fly
            int temp3;
            cout << "Enter the Node you wish to remove : ";
            cin >> temp3;
            CLL.removeNodeAfterInitialization(temp3);
            break;
        case 6:
           //Print the fly 
            CLL.printList();

        case 7:
            // Exit the program
            return 0;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 9.\n";
            break;
        }
    }

    return 0;
}
