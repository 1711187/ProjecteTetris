#ifndef NODE_H
#define NODE_H

#include "Figura.h"

const int MAX_VALORS_NODE = 4;

class Node
{
public:
	Node() { m_next = nullptr; for (int i = 0; i < MAX_VALORS_NODE; i++) m_valor[i] = 0; };
	int getValor(const int index) const { return m_valor[index]; }
	Node* getNext() const { return m_next; }

	void setValor(const int valor[], const int n) { for (int i = 0; i < n; i++) m_valor[i] = valor[i]; }
	void setNext(Node* next) { m_next = next; }
private:
	int m_valor[MAX_VALORS_NODE];
	Node* m_next;
};


#endif