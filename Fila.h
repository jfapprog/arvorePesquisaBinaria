/* 
 ** UC: 21046-Estruturas de Dados e Algoritmos Fundamentais
 ** e-fólio B 2015-16 (xbsti.cpp)
 **
 ** Aluno: 1301913 - José Póvoa
 */

#ifndef FILA_H
#define FILA_H

#include <string>
using namespace std;

class No
{
public:
    string elemento;
    No* seguinte;
    No()
    {
        seguinte = 0;
    }
    No(const string& elem, No* seg = 0)
    {
        elemento = elem;
        seguinte = seg;
    }   
};

class Fila
{
private:
    No* primeiro;
    No* ultimo;
public:
    Fila();
    virtual ~Fila();
    
    bool Vazia() const;
    void Esvaziar();
    
    void Colocar(const string& elem);
    bool Retirar();
    
    string& Primeiro();
    int NumeroElementos() const;
};

#endif /* FILA_H */

