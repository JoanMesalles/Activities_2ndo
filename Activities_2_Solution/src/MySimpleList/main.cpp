#include "List.h"

int main() {
	List example;

	example.Push_back(2);
	example.Push_back(3);
	example.Push_back(4);

	//example.Pop_back();
	example.Push_front(1);
	//example.Pop_front();
	//example.Front();
	//example.Erase(3);
	example.Insert(2, 5);

	return 0;
}