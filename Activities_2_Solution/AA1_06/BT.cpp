

#include "BT.h"


BT::BT() {
	root = new Node(2);
	root->left = new Node(7);
	root->right = new Node(5);
	root->left->right = new Node(6);
	root->left->right->left = new Node(1);
	root->left->right->right = new Node(11);
	root->right->right = new Node(9);
	root->right->right->left = new Node(4);
};

//Implementar (AA106)
BT::~BT() {}

void BT::PreOrder()
{
	PreOrder(root);
}

void BT::PreOrder(Node* n)
{
	if (n == nullptr) return;
	std::cout << n->key << '-';  //raiz
	PreOrder(n->left);	  // se va al hijo izquierdo
	PreOrder(n->right);	  // se va al hijo derecho
}

void BT::InOrder()
{
	InOrder(root);
}

void BT::InOrder(Node* n)
{
	if (n == nullptr) return;
	InOrder(n->left);	  // se va al hijo izquierdo
	std::cout << n->key;  //raiz
	InOrder(n->right);	  // se va al hijo derecho
}

void BT::PostOrder()
{
	PostOrder(root);
}

void BT::PostOrder(Node* n)
{
	if (n == nullptr) return;
	PostOrder(n->left);	  // se va al hijo izquierdo
	PostOrder(n->right);	  // se va al hijo derecho
	std::cout << n->key;  //raiz
}

//Implementar (AA106)
BT::Node* BT::Search(int key)
{
	return Search(root, key);
}

BT::Node* BT::Search(Node* n, int key)
{
	if (n->key == key)
		return n;

	BT::Node* aux = nullptr;

	if (n->left != nullptr) {
		aux = Search(n->left, key);
	}
	if (aux != nullptr) return aux;
	if (n->right != nullptr) {
		aux = Search(n->right, key);
	}
	if (aux != nullptr) return aux;

	return nullptr;
}

//Implementar (AA106)
bool BT::Exist(int key)
{
	if (Search(key) != nullptr) {
		return true;
	}
	return false;
}

//Implementar uno de los siguientes: PreOrderI, InOrderI o PostOrderI
void BT::PreOrderI()
{
	Node* n = root;

	if (n == nullptr)	return;

	std::queue<Node*> q;

	q.push(n);
	while (!q.empty())
	{
		Node* temp = q.front();
		q.pop();
		
		if (temp->left != nullptr)
			q.push(temp->left);

		if (temp->right != nullptr)
			q.push(temp->right);

		std::cout << temp->key << "-";
	}
}

void BT::InOrderI()
{
}

void BT::PostOrderI()
{
}

//Devuelve en un vector los valores pares encontrados 
void BT::GetNPair(std::vector<int>& v) {
	return GetNPair(root, v);
};
void BT::GetNPair(Node* n, std::vector<int>& v) {
	if (n == nullptr) return;
	if (n->key % 2 == 0) { v.push_back(n->key); };
	GetNPair(n->left, v);
	GetNPair(n->right, v);
}




//Implementar (AA106)
int BT::Height()
{
	return Height(root);
}

int BT::Height(Node* n)
{
	if (n == nullptr) {
		return 0;
	}
	int left = Height(n->left);
	int right = Height(n->right);

	if (left < right) {
		return right + 1;
	}
	else {
		return left + 1;
	}
}



//Implementar (AA106)
bool BT::IsBalanced() {
	return IsBalanced(root);
}

bool BT::IsBalanced(Node* n)
{
	return false;
}

//Implementar (AA106)
int BT::Max()
{
	Node* n = root;

	if (n == nullptr)	return 0;

	std::queue<Node*> q;  

	int max = -1; 
	q.push(n);
	while (!q.empty())
	{
		Node* temp = q.front();
		q.pop();

		if (temp->key > max || max == -1) {
			max = temp->key;
		}

		if (temp->left != nullptr)
			q.push(temp->left);

		if (temp->right != nullptr)
			q.push(temp->right);
	}
	return max;
}

//Implementar (AA106)
int BT::Min()
{
	Node* n = root;

	if (n == nullptr)	return 0;

	std::queue<Node*> q;  

	int min = -1; 
	q.push(n);
	while (!q.empty())
	{
		Node* temp = q.front();
		q.pop();

		if (temp->key < min || min == -1) {
			min = temp->key;
		}

		if (temp->left != nullptr)
			q.push(temp->left);

		if (temp->right != nullptr)
			q.push(temp->right);
	}
	return min;
}


//Versión recursiva
int BT::GetNumberNodes() {
	return GetNumberNodes(root);
}

int BT::GetNumberNodes(Node* n) {
	if (n == nullptr) return 0;
	return GetNumberNodes(n->left) + GetNumberNodes(n->right) + 1;
}

//Versión iterativa
int BT::GetNumberNodesI() {
	Node* n = root;
	// Caso: tree vacio
	if (n == nullptr)	return 0;

	//Caso: tree no vacio
	std::queue<Node*> q;  //para guardar a los nodos que me quedan por visitar
	
	int count = 0; // contador de nodos
	q.push(n);
	while (!q.empty())
	{
		Node* temp = q.front();
		q.pop();

		count++;

		if (temp->left != nullptr)
			q.push(temp->left);

		if (temp->right != nullptr)
			q.push(temp->right);
	}
	return count;
}







