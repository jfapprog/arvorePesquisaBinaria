/* 
 ** UC: 21046-Estruturas de Dados e Algoritmos Fundamentais
 ** e-fólio B 2015-16 (xbsti.cpp)
 **
 ** Aluno: 1301913 - José Póvoa
 */

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "Fila.h"
#include "ABP.h"
using namespace std;

void LerComandos(Fila* comandos)
{
    string linha = "";
    int posicaoEspaco = -1;
    cout << ">> ";
    getline(cin, linha);
    do
    {
        posicaoEspaco = (int) linha.find(' ');
        if (posicaoEspaco < 0)
            comandos->Colocar(linha);
        else
            comandos->Colocar(linha.substr(0, posicaoEspaco));
        linha = linha.substr(posicaoEspaco + 1, linha.length() - posicaoEspaco);
    } while (posicaoEspaco > 0);
}

int main()
{
    ABP<unsigned int>* inteiros = new ABP<unsigned int>();
    Fila* comandos = new Fila();
    bool naoSair = true;
    do
    {
        LerComandos(comandos);
        if (comandos->Primeiro() == "insert")
        {
            comandos->Retirar();
            if (comandos->NumeroElementos() == 0)
                cout << "Sintaxe correta: insert i1 i2 i3 ..." << endl;
            else
            {
                int elemento;
                do
                {
                    elemento = atoi(comandos->Primeiro().c_str());
                    if (elemento < 0 || !isdigit(comandos->Primeiro()[0]))
                        cout << "O elemento nao e numero nao negativo" << endl;
                    else
                    {
                        if (inteiros->Inserir(elemento))
                            cout << elemento << " inserido na arvore" << endl;
                        else
                            cout << elemento << " ja existe na arvore" << endl;
                    }
                    comandos->Retirar();
                } while (!comandos->Vazia());
            }
        } else if (comandos->Primeiro() == "preorder")
        {
            comandos->Retirar();
            if (comandos->NumeroElementos() != 0)
                cout << "Sintaxe correta: preorder" << endl;
            else
                inteiros->ProfundidadePrimeiro();
        } else if (comandos->Primeiro() == "delete")
        {
            comandos->Retirar();
            if (comandos->NumeroElementos() == 0)
                cout << "Sintaxe correta: delete i1 i2 i3 ..." << endl;
            else
            {
                int elemento;
                do
                {
                    elemento = atoi(comandos->Primeiro().c_str());
                    if (elemento < 0 || !isdigit(comandos->Primeiro()[0]))
                        cout << "O elemento nao e numero nao negativo" << endl;
                    else
                    {
                        if (inteiros->Eliminar(elemento))
                            cout << elemento << " removido da arvore" << endl;
                        else
                            cout << elemento << " nao existe na arvore" << endl;
                    }
                    comandos->Retirar();
                } while (!comandos->Vazia());
            }
        } else if (comandos->Primeiro() == "dsw")
        {
            comandos->Retirar();
            if (comandos->NumeroElementos() != 0)
                cout << "Sintaxe correta: dsw" << endl;
            else
                inteiros->BalancearDSW();
        } else if (comandos->Primeiro() == "exit")
        {
            comandos->Retirar();
            if (comandos->NumeroElementos() != 0)
                cout << "Sintaxe correta: exit" << endl;
            else
                naoSair = false;
        } else
            cout << "Introduziu um comando errado!" << endl;
        comandos->Esvaziar();
    } while (naoSair);
    delete inteiros;
    delete comandos;
    return 0;
}

