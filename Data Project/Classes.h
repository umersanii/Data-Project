#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

template <class t>
class CNode
{
	t data;
	CNode* next;

public:
	

	CNode()
	{
		data = 0;
		next = nullptr;
	}
	CNode(t xD)
	{
		data = xD;
		next = nullptr;
	}
	t getData()
	{
		return data;
	}
	void setData(int xD)
	{
		data = xD;
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
template <class t>
class CircularLinkedList
{
	CNode<t>* head;

public:
	CircularLinkedList()
	{
		head = nullptr;
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
			return;
		}

		CNode<t>* temp = head;
		while (temp->getNext() != head)
		{
			temp = temp->getNext();
		}
		
		temp->setNext(newNode);
		newNode->setNext(head);
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
			if (temp->data == xD)
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
			if (temp->data == v1)
				temp->data = v2;

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

	}

	void deleteData(t xD)
	{
		CNode<t>* temp = head;
		CNode<t>* prev = head;
		int c = 0;
		while (1)
		{

			if (temp->getData() == xD)
				break;
			if (c != 0)
				prev = prev->getNext();
			temp = temp->getNext();
			c++;
		}

		prev->setNext(temp->getNext());
		delete temp;
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
			cout << temp->getData() << " ";
			temp = temp->getNext();
			c++;
		}
		cout << "\n";
	}


};

