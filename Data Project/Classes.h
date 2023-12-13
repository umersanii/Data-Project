
#include <iostream>
#include "BTree.h"

#pragma once
using std::cout;
using std::cin;
using std::endl;
using std::string;

extern string Dir;


template <class t>
class CNode
{
	t ID;
	CNode* next;
	BTree* btree;

public:


	CNode()
	{
		ID = 0;
		next = nullptr;
		ID = 0;
	}
	CNode(t xD)
	{
		ID = xD;
		next = nullptr;
	}
	t getID()
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


template <typename t>
class CircularLinkedList
{
	CNode<t>* head;
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

	CNode<t>* getHead()
	{
		return head;
	}
	void insert(t xN)
	{
		CNode<t>* newNode = new CNode<t>(xN);

		if (head == nullptr)
		{
			head = newNode;
			head->setNext(head);
			count++;
			return;
		}

		CNode<t>* temp = head;
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

	bool search(t xD)
	{
		int i = 0;
		CNode<t>* temp = head;
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
			if (temp->ID == xD)
				return true;

			temp = temp->next;
			c++;
		}
		return false;
	}

	void update(t v1, t v2)
	{
		CNode<t>* temp = head;
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
			if (temp->ID == v1)
				temp->ID = v2;

			temp = temp->next;
			c++;
		}
	}

	void insertAtIndex(t value, t position)
	{

		CNode<t>* newNode = new CNode<t>(value);
		CNode<t>* temp = head;
		int c = 1;
		while (temp != nullptr)
		{
			if (c == position)
			{
				newNode->next = temp->next;
				temp->next = newNode;
				break;
			}
			c++;

			temp = temp->next;
		}
		count++;

	}

	void deleteID(t xD)
	{
		CNode<t>* temp = head;
		CNode<t>* prev = head;
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
		CNode<t>* temp = head;
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
		CNode<t>* temp = head;
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
