#pragma once

#include <iostream>
#include "BTree.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

extern string Dir;


class CNode
{
	int ID;
	CNode* next;
	BTree* btree;

public:


	CNode()
	{
		ID = 0;
		next = nullptr;
		ID = 0;
	}
	CNode(int xD)
	{
		ID = xD;
		next = nullptr;
	}
	int getID()
	{
		return ID;
	}
	void setID(int xD)
	{
		ID = xD;
	}
	CNode* getNext()
	{
		return next;
	}
	void setNext(CNode* xN)
	{
		next = xN;
	}
	
};


class CircularLinkedList
{
	CNode* head;
	int count;
public:
	int getCount()
	{
		return count;
	}

	CircularLinkedList()
	{
		head = nullptr;
		count = 0;
	}

	CNode* getHead()
	{
		return head;
	}
	void insert(int xN)
	{
		CNode* newNode = new CNode(xN);

		if (head == nullptr)
		{
			head = newNode;
			head->setNext(head);
			count++;
			return;
		}

		CNode* temp = head;
		while (temp->getNext() != head)
		{
			temp = temp->getNext();
		}

		temp->setNext(newNode);
		newNode->setNext(head);
		count++;
	}



	bool isEmpty()
	{
		if (head == nullptr)
			return true;
		return false;
	}

	bool search(int xD)
	{
		int i = 0;
		CNode* temp = head;
		int c = 0;
		while (1)
		{
			if (c != 0)
			{
				if (temp == head)
				{
					break;
				}
			}
			if (temp->getID() == xD)
				return true;

			temp = temp->getNext();
			c++;
		}
		return false;
	}

	void update(int v1, int v2)
	{
		CNode* temp = head;
		int c = 0;
		while (1)
		{
			if (c != 0)
			{
				if (temp == head)
				{
					break;
				}
			}
			if (temp->getID() == v1)
				temp->setID(v2);

			temp = temp->getNext();
			c++;
		}
	}

	void insertAtIndex(int value, int position)
	{

		CNode* newNode = new CNode(value);
		CNode* temp = head;
		int c = 1;
		while (temp != nullptr)
		{
			if (c == position)
			{
				newNode->setNext(temp->getNext());
				temp->setNext(newNode);
				break;
			}
			c++;

			temp = temp->getNext();
		}
		count++;

	}

	void deleteID(int xD)
	{
		CNode* temp = head;
		CNode* prev = head;
		int c = 0;
		while (1)
		{

			if (temp->getID() == xD)
				break;
			if (c != 0)
				prev = prev->getNext();
			temp = temp->getNext();
			c++;
		}

		prev->setNext(temp->getNext());
		delete temp;
		count--;
	}


	void print()
	{
		CNode* temp = head;
		int c = 0;
		while (1)
		{
			if (c != 0)
			{
				if (temp == head)
					break;
			}
			cout << temp->getID() << " ";
			temp = temp->getNext();
			c++;
		}
		cout << "\n";
	}


	void printID()
	{
		CNode* temp = head;
		int c = 0;
		while (1)
		{
			if (c != 0)
			{
				if (temp == head)
					break;
			}
			cout << temp->getID() << " ";
			temp = temp->getNext();
			c++;
		}
		cout << "\n";
	}

};

