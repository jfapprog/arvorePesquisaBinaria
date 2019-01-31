/* 
 ** UC: 21046-Estruturas de Dados e Algoritmos Fundamentais
 ** e-fólio B 2015-16 (xbsti.cpp)
 **
 ** Aluno: 1301913 - José Póvoa
 */

#include <iostream>
#include "Fila.h"
using namespace std;

Fila::Fila()
{
    primeiro = 0;
    ultimo = 0;
    //para testes
    //cout << "Fila construida!" << endl;
}

Fila::~Fila()
{
    No* auxiliar = 0;
    //enquanto a fila não é vazia apagar o primeiro elemento
    //o primeiro passa a ser o seguinte
    while (!Vazia())
    {
        auxiliar = primeiro;
        primeiro = primeiro->seguinte;
        delete auxiliar;
    }
    //para testes
    //cout << "Fila destruida!" << endl;
}

bool Fila::Vazia() const
{
    //se o apontador para o primeiro elemento é nulo, então a fila está vazia
    return primeiro == 0;
}

void Fila::Esvaziar()
{
    while (Retirar());
}

void Fila::Colocar(const string& elem)
{
    //se a fila não está vazia o elemento a adicionar é o seguinte do último
    //que depois passa a ser o último
    if (!Vazia())
    {
        ultimo->seguinte = new No(elem);
        ultimo = ultimo->seguinte;
    } else
        ultimo = primeiro = new No(elem);
}

bool Fila::Retirar()
{
    if (Vazia())
        return false;
    //se a fila não está vazia
    //se apenas tem um elemento, o primeiro e o último passam a ser nulos
    No* auxiliar = primeiro;
    if (primeiro == ultimo)
        primeiro = ultimo = 0;
        //se tem mais do que um elemento
        //o primeiro passa a ser o seu seguinte
    else
        primeiro = primeiro->seguinte;
    delete auxiliar;
    return true;
}

string& Fila::Primeiro()
{
    return primeiro->elemento;
}

int Fila::NumeroElementos() const
{
if (Vazia())
        return 0;
    unsigned int contador = 0;
    No* atual = primeiro;
    //percorrer a fila para contar elementos
    while (atual != 0)
    {
        atual = atual->seguinte;
        contador++;
    }
    return contador;
}

