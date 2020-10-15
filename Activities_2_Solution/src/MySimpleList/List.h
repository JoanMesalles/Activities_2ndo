#pragma once
#include <iostream>
class List
{
	struct node {
		int data;
		node* next;
		node() : data(0), next(nullptr) {};
		node(int _data, node* _next) :data(_data), next(_next) {};
	};
	node* first;		//puntero al primer elemento de la lista
	node* last;		//puntero al último elemento de la lista
	int numElements;		//numero de elementos que tiene la lista

public:
	List();
	~List();

	void Push_back(int value);	//inserta un nuevo elemento al final de la lista con valor value
	void Pop_back();			//elimina el último elemento de la lista
	void Push_front(int value); 	//inserta un nuevo elemento al principio de la lista con valor value
	void Pop_front();		//elimina el primer elemento de la lista
	bool IsEmpty() const;		//devuelve true si la lista está vacía, sino devuelve false
	int Front() const;		//devuelve el valor del primer elemento de la lista
	int Back() const;		//devuelve el valor del último elemento de la lista
	int Size()const;			//devuelve el tamaño (numero de elementos) de la lista
	void Erase(int value);		//elimina el elemento de la lista que tiene como valor value.
								//El primero que encuentre
	void Insert(int value1, int value2); //inserta un nuevo elemento con value2 después del elemento con value1
	friend bool operator==(const List& l1, const List& l2); //compara el contenido de dos listas l1 y l2. 
	   //Devuelve true si son iguales, false en caso contrario
	/*
	friend std::ostream& operator<<(std::ostream& o, const List& l);
	*/
};
