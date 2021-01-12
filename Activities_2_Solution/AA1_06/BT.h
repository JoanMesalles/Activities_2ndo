#pragma once

#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>


//Binary Tree implemented with pointers


class BT
{
public:
	struct Node {
		int key; 
		Node* left; 
		Node* right; 
		Node(int x) :key(x), left(nullptr), right(nullptr) {};
	};


protected:
	Node * root; 
private:
	int GetNumberNodes(Node* n);
	void GetNPair(Node* n, std::vector<int>& v);
	void PreOrder(Node *n);
	void InOrder(Node *n);
	void PostOrder(Node *n);
	Node* Search(Node* n, int key);
	int Height(Node* n);
	bool IsBalanced(Node*, int);


public:
	 BT();
	 ~BT(); //Implementar

	 //Busca la clave key en el �rbol
	 //si existe, devuelve un puntero al nodo que contiene la clave key
	 //si no existe, devuelve nullptr
	 Node* Search(int key);	//Implementar (AA106)

	 //Busca la clave key en el �rbol
	 //si existe,devuelve true
	 //si no existe. devuelve false
	 bool Exist(int key);	//Implementar (AA106)

	//Recorridos usando recursi�n
	void PreOrder();
	void InOrder();
	void PostOrder();

	//Recorridos sin recursi�n, es decir, usando iteraci�n
	void PreOrderI();	//Implementar (AA106)
	void InOrderI();	//Implementar (AA106)
	void PostOrderI();	//Implementar (AA106)

	//Devuelve la altura del �rbol
	int Height();		//Implementar (AA106)

	//Devuelve true si el �rbol est� balanceado
	//Devuleve false si no
	bool IsBalanced(int);	//Implementar (AA106)

	//Devuelve el m�ximo de las claves
	int Max(); //Implementar (AA106)

	//Devuelve el m�nimo de las claves
	int Min(); //Implementar (AA106)

	//Devuelve el n�mero de nodos que tiene el �rbol (versi�n recursiva)
	int GetNumberNodes(); 

	//Devuelve el n�mero de nodos que tiene el �rbol (versi�n iterativa)
	int GetNumberNodesI();
		
	//Devuelve (c�mo par�metro) un vector con las claves encontradas que son par
	void GetNPair(std::vector<int>& v);
	


};

