#include"BTree.h"
#include"helperFunctions.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include<string>

using std::cin;
using std::getline;
using namespace std;
struct Node
{
    long int data;
    Node* next;
    vector<Node*> shortcuts;
    vector<int> responsibleNodes;
    BTree* Tree;
    Node(int id, int BTreeOrderr) : data(id), next(nullptr) {
        Tree = new BTree(BTreeOrderr);
    }
};

class CircularLinkedList
{
private:
    Node* head;
    int totalNodes;
    int k;
    int BTreeOrderr;

public:
    CircularLinkedList(int N, int shortcutPower, vector<int> ids,int BtreeOrder) : totalNodes(N), k(shortcutPower)
    {
        head = nullptr;
        buildCircularList(ids);
        buildShortcuts(head);
        BTreeOrderr = BtreeOrder;
    }

    void buildCircularList(vector<int> ids)
    {
        if (totalNodes <= 0)
        {
            cout << "Invalid totalNodes value." << endl;
            return;
        }

        Node* last = nullptr;
      
        for (int i = 0; i < ids.size(); ++i)
        {
            createFolder(to_string(ids[i]));
            Node* newNode = new Node(ids[i],BTreeOrderr);

            if (head == nullptr)
            {
                head = newNode;
                last = newNode;
            }
            else
            {
                int temp = last->data;
                last->next = newNode;
                last = newNode;
                PopulateIntVector(last->responsibleNodes, temp, last->data);
            }
        }

        // Link the last node back to the head to make it circular
        int temp1 = last->data;
        if (last)
        {
            last->next = head;
        }
        PopulateIntVector(head->responsibleNodes, temp1, head->data);
    }

    void PopulateIntVector(vector<int>& original, int a, int b)
    {
        if (!(a >= b))
        {
            for (int i = a + 1; i < b; ++i)
            {
                original.push_back(i);
            }
        }
        else {
            b = totalNodes;
            for (int i = a + 1; i < b; ++i)
            {
                original.push_back(i);
            }

        }
    }
    void printResponsibleVector(vector<int> res)
    {
        cout << "responsible Nodes for the current Node : ";
        for (int i = 0; i < res.size(); i++)
        {
            cout << res[i] << " ";
        }
        cout << endl;
    }
    Node* findNodeOrNext(Node* head1, int value)
    {
        Node* current = head1;
        Node* found = nullptr;
        int count = 0;

        do
        {
            if (current->data >= value)
            {
                if (found == nullptr || current->data < found->data)
                {
                    found = current;
                }
            }
            current = current->next;
            count++;
        } while (current != head1 && count < totalNodes);

        if (found == nullptr)
        {
            found = head1;
        }
        return found;
    }

    void buildShortcuts(Node* start)
    {

        Node* current = start;
        buildDoublyList(current);
        current = current->next;
        while (current != start)
        {
            buildDoublyList(current);
            current = current->next;
        }
    }

    void buildDoublyList(Node* node)
    {
        if (node->shortcuts.empty() == 0) {
            node->shortcuts.clear();
        }

        for (int i = 1; i <= k; ++i)
        {
            int temp2 = node->data + pow(2, i - 1);
            int shortcutId = temp2 % totalNodes;

            Node* newNode = findNodeOrNext(head, shortcutId);
            node->shortcuts.push_back(newNode);
        }
    }

    void printList()
    {
        Node* current = head;
        cout << "Node " << current->data << ": ";
        printShortcuts(current);
        cout << endl;
       /* printResponsibleVector(current->responsibleNodes);*/
        cout << endl;
        current = current->next;
        while (current != head)
        {
            cout << "Node " << current->data << ": ";
            printShortcuts(current);
            cout << endl;
           /* printResponsibleVector(current->responsibleNodes);*/
            cout << endl;
            current = current->next;
        }
    }
    Node* returnHead() {
        return head;
    }
    void printShortcuts(Node* current1)
    {
        cout << "shortcuts : ";
        for (int i = 0; i < current1->shortcuts.size(); i++)
        {

            cout << current1->shortcuts[i]->data;
            if (i != current1->shortcuts.size() - 1)
            {
                cout << ",";
            }
        }
    }
    bool resposibilityCheck(int target, vector<int> res)
    {
        for (int i = 0; i < res.size(); i++)
        {
            if (target == res[i])
            {
                return 1;
            }
        }
        return 0;
    }
    void searchNodes(int firstNodeValue, int secondNodeValue)
    {
        Node* firstNode = nullptr;
        Node* secondNode = nullptr;
        vector<int> firstPath;
        vector<int> secondPath;
        vector<Node*> firstNodeShortcuts;
        vector<Node*> secondNodeShortcuts;
        // Search for the first node
        Node* current = head;
        firstPath.push_back(current->data);
        while (current->data != firstNodeValue)
        {
            copyshortcuts(firstNodeShortcuts, current);
            while (!firstNodeShortcuts.empty())
            {
                Node* max = firstNodeShortcuts[0];
                for (int i = 0; i < firstNodeShortcuts.size(); i++)
                {
                    if (firstNodeShortcuts[i]->data > max->data)
                    {
                        max = firstNodeShortcuts[i];
                    }
                }
                if (max->data > firstNodeValue)
                {
                    auto it = std::find(firstNodeShortcuts.begin(), firstNodeShortcuts.end(), max);
                    if (it != firstNodeShortcuts.end())
                    {
                        firstNodeShortcuts.erase(it);
                    }
                }
                else
                {
                    break;
                }
            }
            Node* max = firstNodeShortcuts[0];
            for (int i = 0; i < firstNodeShortcuts.size(); i++)
            {
                if (firstNodeShortcuts[i]->data > max->data)
                {
                    max = firstNodeShortcuts[i];
                }
            }
            current = max;
            firstPath.push_back(current->data);
        }
        firstNode = current;

        // Search for the second node

        secondPath.push_back(current->data);

        while (current->data != secondNodeValue)
        {
            copyshortcuts(secondNodeShortcuts, current);
            while (!secondNodeShortcuts.empty())
            {
                Node* max = secondNodeShortcuts[0];
                for (int i = 0; i < secondNodeShortcuts.size(); i++)
                {
                    if (secondNodeShortcuts[i]->data > max->data)
                    {
                        max = secondNodeShortcuts[i];
                    }
                }
                if (max->data > secondNodeValue)
                {
                    auto it = std::find(secondNodeShortcuts.begin(), secondNodeShortcuts.end(), max);
                    if (it != secondNodeShortcuts.end())
                    {
                        secondNodeShortcuts.erase(it);
                    }
                }
                else
                {
                    break;
                }
            }
            Node* max = secondNodeShortcuts[0];
            for (int i = 0; i < secondNodeShortcuts.size(); i++)
            {
                if (secondNodeShortcuts[i]->data > max->data)
                {
                    max = secondNodeShortcuts[i];
                }
            }
            current = max;
            secondPath.push_back(current->data);
        }

        secondNode = current;

        // Print the paths
        cout << "Path to first node: ";
        for (int i : firstPath)
        {
            cout << i << " ";
        }
        cout << endl;

        cout << "Path to second node: ";
        for (int i : secondPath)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    void copyshortcuts(vector<Node*>& firstnodeshortcuts, Node* current)
    {
        for (int i = 0; i < current->shortcuts.size(); i++)
        {
            firstnodeshortcuts.push_back(current->shortcuts[i]);
        }
    }
    Node* searchNonActiveNode(int value, Node* start)
    {
        Node* firstNode = nullptr;

        vector<int> firstPath;

        vector<Node*> firstNodeShortcuts;

        // Search for the first node
        Node* current = head;
        firstPath.push_back(current->data);
        while (current->data != value)
        {
            for (int i = 0; i < current->shortcuts.size(); i++)
            {
                if (resposibilityCheck(value, current->shortcuts[i]->responsibleNodes) == 1)
                {
                    return current->shortcuts[i];
                }
            }

            copyshortcuts(firstNodeShortcuts, current);
            while (!firstNodeShortcuts.empty())
            {
                Node* max = firstNodeShortcuts[0];
                for (int i = 0; i < firstNodeShortcuts.size(); i++)
                {
                    if (firstNodeShortcuts[i]->data > max->data)
                    {
                        max = firstNodeShortcuts[i];
                    }
                }
                if (max->data > value)
                {
                    auto it = std::find(firstNodeShortcuts.begin(), firstNodeShortcuts.end(), max);
                    if (it != firstNodeShortcuts.end())
                    {
                        firstNodeShortcuts.erase(it);
                    }
                }
                else
                {
                    break;
                }
            }
            Node* max = firstNodeShortcuts[0];
            for (int i = 0; i < firstNodeShortcuts.size(); i++)
            {
                if (firstNodeShortcuts[i]->data > max->data)
                {
                    max = firstNodeShortcuts[i];
                }
            }
            current = max;
            firstPath.push_back(current->data);
        }
        firstNode = current;

        return firstNode;
    }
    Node* searchNodeAndReturn(int firstNodeValue) {
        Node* firstNode = nullptr;

        vector<int> firstPath;

        vector<Node*> firstNodeShortcuts;

        // Search for the first node
        Node* current = head;
        firstPath.push_back(current->data);
        while (current->data != firstNodeValue)
        {
            copyshortcuts(firstNodeShortcuts, current);
            while (!firstNodeShortcuts.empty())
            {
                Node* max = firstNodeShortcuts[0];
                for (int i = 0; i < firstNodeShortcuts.size(); i++)
                {
                    if (firstNodeShortcuts[i]->data > max->data)
                    {
                        max = firstNodeShortcuts[i];
                    }
                }
                if (max->data > firstNodeValue)
                {
                    auto it = std::find(firstNodeShortcuts.begin(), firstNodeShortcuts.end(), max);
                    if (it != firstNodeShortcuts.end())
                    {
                        firstNodeShortcuts.erase(it);
                    }
                }
                else
                {
                    break;
                }
            }
            Node* max = firstNodeShortcuts[0];
            for (int i = 0; i < firstNodeShortcuts.size(); i++)
            {
                if (firstNodeShortcuts[i]->data > max->data)
                {
                    max = firstNodeShortcuts[i];
                }
            }
            current = max;
            firstPath.push_back(current->data);
        }
        firstNode = current;

        return firstNode;
    }
    void printROutingTable(int id) {
        Node* temp = searchNodeAndReturn(id);
        for (int i = 0; i < temp->shortcuts.size(); i++)
        {
            cout << " " << temp->shortcuts[i]->data ;
        }
        cout << endl;
    }
    //  vector<Node*> findNodeUsingNext(int target,Node* first){
    //     Node*current=first;
    //     vector<Node*> res;
    //     while(current->next->data!=target){
    //     current=current->next;
    //     }
    //     return res;
    //  }
    void addNodeAfterInitialization(int N) {
        createFolder(to_string(N));
        Node* newNode = new Node(N,BTreeOrderr);
        newNode->next = nullptr;

        if (head == nullptr || head->data >= N) {
            newNode->next = head;

            if (head != nullptr) {
                Node* last = head;
                while (last->next != head) {
                    last = last->next;
                }
                last->next = newNode;
            }

            head = newNode;
        }
        else {
            Node* prev = nullptr;
            Node* current = head;

            while (current->next != head && current->data < N) {
                prev = current;
                current = current->next;
            }

            // If the new node should be inserted at the end of the list
            if (current->next == head && current->data < N) {
                current->next = newNode;
                newNode->next = head;
            }
            else {
                prev->next = newNode;
                newNode->next = current;
            }
        }
        buildShortcuts(newNode);
        newNode->responsibleNodes = removeFromResponsibleVector(newNode->next->responsibleNodes, N);
    }
    vector<int> removeFromResponsibleVector(vector<int>& res, int value) {
        for (int i = 0; i < res.size(); i++)
        {
            if (res[i] == value) {
                res.erase(res.begin() + i);
            }
        }
        vector<int> toReturn;
        for (int i = 0; i < res.size(); i++)
        {
            if (res[i] < value) {
                toReturn.push_back(res[i]);
            }
        }
        for (int i = 0; i < res.size(); i++)
        {
            if (res[i] < value) {
                res.erase(res.begin() + i);
            }
        }
        if (res.size() == 1 && res[0] < value) {
            res.clear();
        }

        return toReturn;

    }
    void removeNodeAfterInitialization(int N) {

        Node* successor = nullptr;
        vector<int> sh;
        Node* current = head;
        Node* prev = nullptr;

        // If head node itself holds the key to be deleted
        if (current->data == N && current->next == head) {
            sh = current->responsibleNodes;
            head = nullptr;
            Node* temp = current;
            delete temp;

        }

        // If head needs to be removed
        if (current->data == N) {
            while (current->next != head) {
                current = current->next;
            }
            Node* temp = head;
            sh = temp->responsibleNodes;
            current->next = head->next;
            head = current->next;
            successor = head;
            delete temp;

        }

        // Either the node to be deleted is not found or the end of list is not reached
        while (current->next != head && current->next->data != N) {
            prev = current;
            current = current->next;
        }

        // If node to be deleted was found
        if (current->next->data == N) {
            Node* temp = current->next;
            sh = temp->responsibleNodes;
            successor = temp->next;
            if (current->next == head) { // Node to be deleted is at the end
                head = current;
            }
            current->next = temp->next;
            delete temp;

        }
        buildShortcuts(successor);
        for (int i = 0; i < sh.size(); ++i) {
            successor->responsibleNodes.insert(successor->responsibleNodes.begin(), sh[i]);
        }
        successor->responsibleNodes.push_back(N);
    }
    void AddFile(int CurrentNode) {
        stringstream content;
       
        string line;
        cout << "Enter content of the File : ";

        while (true)
        {
            getline(cin, line);

            if (line == "141")
            {
                break;
            }
            content << line << '\n';

        }
        string filecontent(content.str());
        Key k;
        long int Temp = CalculateHash(filecontent);
        k.key = Temp;
        string filename = to_string(Temp);
        Temp = Temp % totalNodes;
        int Hash = Temp;
        int targetNode = Hash;
        Node* founded = searchNodeAndReturn(CurrentNode);
        Node* Target = searchNonActiveNode(targetNode, founded);
        string targetFolder = Dir;
        targetFolder=targetFolder+ "\\";
        targetFolder = targetFolder + to_string(Target->data);
        targetFolder = targetFolder + "\\";
        string path=insertFile(targetFolder, filename, filecontent);
        k.path = path;
        Target->Tree->insertion(k);
        Target->Tree->traverse();
        

        
    }
};
