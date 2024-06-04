#include "Cua.h"

Cua::Cua()
{
    m_primer = nullptr;
    m_ultim = nullptr;
    m_nElements = 0;
}

Cua::~Cua()
{
    Node* iterador = m_primer;
    Node* next;
    while (iterador != nullptr)
    {
        next = iterador->getNext();
        delete iterador;
        iterador = next;
    }
}

bool Cua::empty() const
{
    bool retorna = false;

    if (m_nElements == 0)
        retorna = true;

    return retorna;
}

Node* Cua::getPrimer() const
{
    Node* retorna = m_primer;

    return m_primer;
}

Node* Cua::getUltim() const
{
    Node* retorna = m_ultim;
    return m_ultim;
}
void Cua::afegeix(int valor[], int n)
{
    Node* aux = new Node;
    aux->setValor(valor, n);
    aux->setNext(nullptr);

    if (m_nElements == 0)
    {
       m_primer = aux;
    }
    else
    {
        m_ultim->setNext(aux);
    }
    m_ultim = aux;
    m_nElements++;
}

void Cua::treure()
{
    Node* aux = m_primer;
    if (m_nElements == 1)
    {
        m_ultim = nullptr;
        m_primer = nullptr;
    }
    else
    {
        m_primer = aux->getNext();
    }

    delete aux;

    m_nElements--;
}

void Cua::clear()
{
    while (!empty())
    {
        treure();
    }
}