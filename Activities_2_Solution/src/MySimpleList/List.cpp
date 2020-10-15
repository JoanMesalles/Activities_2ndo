#include "List.h"

List::List() {
	last = nullptr;
	first = nullptr;
	numElements = 0;
}

List::~List() {
	last = nullptr;
	first = nullptr;
	numElements = 0;
}

void List::Push_back(int value) {

	if (numElements == 0) {
		first = last = new node(value, nullptr);
		numElements++;
	}
	else {
		node* temp = new node(value, nullptr);
		last->next = temp;
		last = temp;
		numElements++;
	}
}

void List::Pop_back() {

	if (numElements == 1) {
		first = nullptr;
		delete last;
		numElements--;
	}
	else {
		node* temp = first;
		while (temp->next != last) {
			temp = temp->next;
		}
		delete last;
		last = temp;
		numElements--;
	}
}
void List::Push_front(int value) {

	if (numElements == 0) {
		first = last = new node(value, nullptr);
		numElements++;
	}
	else {
		node* temp = new node(value, nullptr);
		node* temp2 = first;
		first = temp;
		first->next = temp2;
		numElements++;
	}
}
void List::Pop_front() {

	if (numElements == 1) {
		first = nullptr;
		delete last;
		numElements--;
	}
	else {
		node* temp = first->next;
		delete first;
		first = temp;
		numElements--;
	}
}

bool List::IsEmpty() const { return numElements == 0; }
int List::Front() const { return first->data; }
int List::Back() const { return last->data; }
int List::Size() const { return numElements; }

void List::Erase(int value) {
	node* temp = first;
	node* temp2 = first;
	int count = 0;
	while (temp->data != value) {
		temp = temp->next;
		count++;
	}
	for (int i = 0; i < count - 1; i++) {
		temp2 = temp2->next;
	}
	temp2->next = temp->next;
	delete temp;
	numElements--;

}
void List::Insert(int value1, int value2) {
	node* temp = first;
	node* temp2 = nullptr;
	while (temp->data != value1) {
		temp = temp->next;
	}
	temp2 = temp->next;
	temp->next = new node(value2, temp2);


}

bool operator==(const List& l1, const List& l2)
{

	return false;
}
