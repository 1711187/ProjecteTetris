#ifndef CUA_H
#define CUA_H

#include "Node.h"

class Cua
{
public:
	Cua();
	~Cua();

	bool empty() const;
	void afegeix(int valor[], int n);
	void treure();
	int size() const { return m_nElements; };
	void clear();
	Node* getPrimer() const;
	Node* getUltim() const;
private:
	Node* m_primer;
	Node* m_ultim;
	int m_nElements;
};

#endif