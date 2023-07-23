#include <iostream>
#include <string>
#include <sstream>
#include "LinkedList.h"
#include "Node.h"
using namespace std;

LinkedList::LinkedList() : head(nullptr), tail(nullptr)
{
	// Implement this function
}

LinkedList::~LinkedList()
{
	// Implement this function
	this->clear();
}

LinkedList::LinkedList(const LinkedList &source)
{

	// Implement this function
	// copy the head and take the next node before entering loop
	// this->head = source.head;
	// Node *currNode = source.head;
	// Node *nextNode;
	// while (currNode != nullptr)
	// {
	// 	nextNode = currNode->next;
	// 	currNode = nextNode;
	// }
	// this->tail = source.tail;

	// start by creating temporary node varaibles to hold values pointed to when going through the linked list pass in argument
	Node *currNode = source.head;
	Node *copyNode;
	Node *nextNode;

	while (currNode != nullptr)
	{
		copyNode = new Node(currNode->data.id, currNode->data.year, currNode->data.month, currNode->data.temperature);
		if (currNode == nullptr)
		{
			nextNode = source.head->next;
			currNode = nextNode;
			this->head = source.head;
			this->tail->next = copyNode;
			this->tail = copyNode;
		}
		else
		{
			nextNode = currNode->next; // update next node and current node and then update where the tail node points to
			currNode = nextNode;
			this->tail->next = copyNode;
			this->tail = copyNode;
		}
	}
}

LinkedList &LinkedList::operator=(const LinkedList &source)
{
	// Implement this function
	// deallocate the original linked list
	// allocate new space creating new linked list of nodes
	// copy value form individual nodes from original to the new linked list nodes
	this->clear();
	// old linked list is cleared
	// create temporary nodes to store values pointed to when going through the linked list to allocate and copy
	Node *currNode = source.head;
	Node *copyNode;
	Node *nextNode;
	// while loop that continues until nullptr is found
	// each iteration of the loop starts with creation of new copyNode that is defined with the currNode's data
	while (currNode != nullptr)
	{
		copyNode = new Node(currNode->data.id, currNode->data.year, currNode->data.month, currNode->data.temperature);

		// if at the start of the linked list the source head is copied
		// else the next node and the current node are updated in addition to updating where the tail node will point to in this linked list
		if (this->head == nullptr)
		{
			nextNode = source.head->next;
			currNode = nextNode;
			this->head = source.head;
			this->tail->next = copyNode;
			this->tail = copyNode;

			// nextNode = currNode->next;
		}
		else
		{
			nextNode = currNode->next;
			currNode = nextNode;
			this->tail->next = copyNode;
			this->tail = copyNode;
		}
	}

	return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature)
{
	// Implement this function
	bool onward = true;
	Node *currNode = this->head;
	Node *nextNode = nullptr;
	Node *prevNode = nullptr;
	// create a new node that copies the data from currNode used to traverse the linked list
	Node *newNode = new Node(location, year, month, temperature);

	// empty linked list
	if (currNode == nullptr)
	{
		head = newNode;
		tail = newNode;
		onward = false;
	}

	// at least one node exists in list
	else
	{
		nextNode = currNode->next;
	}

	// exactly one node present in linked list
	if ((currNode != nullptr) && (nextNode == nullptr))
	{

		// new node inserts before existing head
		if (newNode->data < currNode->data)
		{
			head = newNode;
			head->next = currNode;
			newNode->next = currNode;
			tail = currNode;
		}
		// new node inserts after existing head
		else
		{
			currNode->next = newNode;
			tail->next = newNode;
			tail = newNode;
			
		}

		onward = false;
	}

	if (onward)
	{
		prevNode = currNode;
		currNode = nextNode;
		nextNode = currNode->next;
	}
	// linked list has x + 2 items present
	while (onward)
	{
		// new node inserts in middle of linked lsit
		if ((prevNode->data < newNode->data) && (newNode->data < currNode->data))
		{
			prevNode->next = newNode;
			newNode->next = currNode;
			break;
		}
		// new node becomes first node in linked list full of nodes
		else if (newNode->data < prevNode->data)
		{
			head = newNode;
			head->next = prevNode;
			newNode->next = prevNode;
			break;
		}
		// new node becomes last node in linked list full of nodes
		else if (nextNode == nullptr)
		{
			tail->next = newNode;
			tail = newNode;
			newNode->next = nullptr;
			break;
		}
		else
		{
			prevNode = currNode;
			currNode = nextNode;
			nextNode = currNode->next;
		}
	}

	// while ((nextNode != nullptr) && (newNode < currNode))
	// {
	// 	prevNode = currNode;
	// 	currNode = nextNode;
	// 	nextNode = currNode->next;
	// }

	// check if currNode is null indicating empty linked list

	// proper position has been found

	// middle of linked list that contains nodes
}

void LinkedList::clear()
{
	// Implement this function
	// traverse the linked list until nullptr is found
	// use temporary nodes to assign and delete each individual node while going through the linked list
	Node *currNode = head;
	Node *nextNode;
	while (currNode != nullptr)
	{
		nextNode = currNode->next; // assign the nextNode to the next node that currNode points to
		delete currNode;		   // delete the current node and then reassign currNode to nextNode and continue the process
		currNode = nextNode;
	}
	head = nullptr;
	tail = nullptr;
	currNode = nullptr;
	nextNode = nullptr;
}

Node *LinkedList::getHead() const
{
	// Implement this function it will be used to help grade other functions
	return head;
}

string LinkedList::print() const
{
	string outputString;
	ostringstream location;
	ostringstream year;
	ostringstream month;
	ostringstream temperature;
	// Implement this function
	Node *currNode = head;
	Node *nextNode;
	while (currNode != nullptr) {
		location << currNode->data.id;
		outputString += location.str();
		outputString += " ";
		year << currNode->data.year;
		outputString += year.str();
		outputString += " ";
		month << currNode->data.month;
		outputString += month.str();
		outputString += " ";
		temperature << currNode->data.temperature << endl;
		outputString += temperature.str();
		location.str("");
		year.str("");
		month.str("");
		temperature.str("");

		nextNode = currNode->next;
		currNode = nextNode;
	}
	return outputString;
}

ostream &operator<<(ostream &os, const LinkedList &ll)
{
	/* Do not modify this function */
	os << ll.print();
	return os;
}
