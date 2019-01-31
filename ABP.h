/* 
 ** UC: 21046-Estruturas de Dados e Algoritmos Fundamentais
 ** e-fólio B 2015-16 (xbsti.cpp)
 **
 ** Aluno: 1301913 - José Póvoa
 */

#ifndef ABP_H
#define ABP_H

#include <iostream>
#include <cmath>
using namespace std;

template<class T>
class NoABP
{
public:
    T elemento;
    NoABP<T>* esquerda;
    NoABP<T>* direita;

    NoABP()
    {
        esquerda = direita = 0;
    }

    NoABP(const T& elem, NoABP<T>* esq = 0, NoABP<T>* dir = 0)
    {
        elemento = elem;
        esquerda = esq;
        direita = dir;
    }

    virtual ~NoABP()
    {
    }
};

template<class T>
class ABP
{
private:
    NoABP<T>* raiz;

public:
    ABP();
    virtual ~ABP();

    unsigned int Dimensao() const;
    unsigned int Altura() const;
    bool Balanceada() const;

    bool Inserir(const T& elem);
    bool Eliminar(const T& elem);
    void BalancearDSW();

    void ProfundidadePrimeiro() const;

private:
    unsigned int Dimensao(NoABP<T>* no) const;
    unsigned int Altura(NoABP<T>* no) const;
    bool Balanceada(NoABP<T>* no) const;

    void Eliminar(NoABP<T>* no, NoABP<T>* anterior);
    void TransformarArvoreLista();
    void BalancearArvoreLista();
    void RotacaoDireita(NoABP<T>* avo, NoABP<T>* pai, NoABP<T>* filho);
    void RotacaoEsquerda(NoABP<T>* avo, NoABP<T>* pai, NoABP<T>* filho);
    void RealizarRotacoes(int n);

    void PreOrdem(NoABP<T>* no, NoABP<T>* pai) const;
};

template<class T>
ABP<T>::ABP()
{
    raiz = 0;
}

template<class T>
ABP<T>::~ABP()
{
    //eliminar a raiz até que esta seja um apontador nulo
    while (raiz != 0)
        Eliminar(raiz, 0);
}

template<class T>
unsigned int ABP<T>::Dimensao() const
{
    //retorna o valor obtido pela função recursiva privada
    return Dimensao(raiz);
}

template<class T>
unsigned int ABP<T>::Dimensao(NoABP<T>* no) const
{
    //se nó é um apontador nulo a dimensão é zero
    if (no == 0)
        return 0;
    //se não adiciona 1 à dimensão das suas subárvores
    return 1 + Dimensao(no->esquerda) + Dimensao(no->direita);
}

template<class T>
unsigned int ABP<T>::Altura() const
{
    //retorna o valor obtido pela função recursiva privada
    return Altura(raiz);
}

template<class T>
unsigned int ABP<T>::Altura(NoABP<T>* no) const
{
    //se nó é um apontador nulo a áltura é zero
    if (no == 0)
        return 0;
    //se não adiciona 1 à altura máxima das suas subárvores
    return 1 + max(Altura(no->esquerda), Altura(no->direita));
}

template<class T>
bool ABP<T>::Balanceada() const
{
    //retorna o valor da função recursiva privada
    return Balanceada(raiz);
}

template<class T>
bool ABP<T>::Balanceada(NoABP<T>* no) const
{
    //se atinge um apontador nulo retorna true
    if (no == 0)
        return true;
        // caso contrário verifica se a diferença entre a altura das subárvores
        //direita e esquerda diferem no máximo de uma unidade
    else
        return (abs((int) (Altura(no->esquerda) - Altura(no->direita))) <= 1);
}

template<class T>
bool ABP<T>::Inserir(const T& elem)
{
    //se a raíz é um apontador nulo insere o nó na raíz
    if (raiz == 0)
    {
        raiz = new NoABP<T>(elem);
        return true;
    }
    //se não, percorre a árvore
    NoABP<T>* atual = raiz;
    NoABP<T>* anterior = 0;
    while (atual != 0)
    {
        anterior = atual;
        //se elemento é menor que o elemento do nó percorre subárvore esquerda
        if (elem < atual->elemento)
            atual = atual->esquerda;
            //se elemento é maior que o elemento do nó percorre subárvore direita
        else if (elem > atual->elemento)
            atual = atual->direita;
            //se é igual não insere o elemento
        else
            return false;
    }
    //inserir elemento no apontador nulo do anterior
    if (elem < anterior->elemento)
        anterior->esquerda = new NoABP<T>(elem);
    else
        anterior->direita = new NoABP<T>(elem);
    return true;
}

template<class T>
bool ABP<T>::Eliminar(const T& elem)
{
    //se a árvore não tem elementos não é eliminado nenhum elemento
    if (raiz == 0)
        return false;
    //se não, percorre a árvore até encontrar elemento ou até chegar a nulo
    NoABP<T>* atual = raiz;
    NoABP<T>* anterior = 0;
    while (atual != 0 && atual->elemento != elem)
    {
        anterior = atual;
        //se é menor desloca-se para a subávore à esquerda
        if (elem < atual->elemento)
            atual = atual->esquerda;
            //se é maior desloca-se para a subávore à direita
        else
            atual = atual->direita;
    }
    //se atingiu um apontador nulo então elemento não existe
    if (atual == 0)
        return false;
    //se não, apagar nó
    Eliminar(atual, anterior);
    return true;
}

template<class T>
void ABP<T>::Eliminar(NoABP<T>* no, NoABP<T>* anterior)
{
    NoABP<T>* noApagar = no;
    //se tem nulo à esquerda, o nó da direita substitui-o
    if (no->direita == 0)
        no = no->esquerda;
        //se tem nulo à direita, o nó da esquerda substitui-o
    else if (no->esquerda == 0)
        no = no->direita;
        //se tem subárvores esquerda e direita
    else
    {
        //procurar o menor da subárvore à direita
        //que é maior que todos os elementos da subárvore esquerda
        NoABP<T>* menor = no->direita;
        NoABP<T>* anteriorMenor = no;
        //percorre a árvore pela esquerda
        while (menor->esquerda != 0)
        {
            anteriorMenor = menor;
            menor = menor->esquerda;
        }
        //verificar se menor está à esquerda ou à direita do anterior
        //se está à direita então ligar a sua direita à direita do anterior
        if (anteriorMenor->direita == menor)
            anteriorMenor->direita = menor->direita;
            //se está à esquerda ligar a sua direita à esquerda do anterior
        else
            anteriorMenor->esquerda = menor->direita;
        //substituir elemento do nó pelo elemento do menor
        no->elemento = menor->elemento;
        //alterar apontador do nó a apagar para o menor
        noApagar = menor;
    }
    //se o nó a eliminar é a raiz, mudar o apontador da raíz
    if (noApagar == raiz)
        raiz = no;
        //se não é a raiz mudar os apontadores do seu anterior
        //excepto se originalmente era a raiz
    else if (anterior != 0)
    {
        if (anterior->esquerda == noApagar)
            anterior->esquerda = no;
        else if (anterior->direita == noApagar)
            anterior->direita = no;
    }
    delete noApagar;
}

template<class T>
void ABP<T>::BalancearDSW()
{
    if (raiz != 0)
    {
        //transformar a árvore numa árvore com todos os elementos à direita
        TransformarArvoreLista();
        //transformar a árvore anterior numa árvore balanceada
        BalancearArvoreLista();
    }
}

template<class T>
void ABP<T>::TransformarArvoreLista()
{
    //criar nós avô, pai e filho
    NoABP<T>* avo = 0;
    NoABP<T>* pai = raiz;
    NoABP<T>* filho = 0;
    //percorrer árvore
    while (pai != 0)
    {
        //o filho passa a ser o nó à esquerda do pai
        filho = pai->esquerda;
        //se o nó pai tem filho à esquerda, efetuar rotação à direita
        if (filho != 0)
        {
            RotacaoDireita(avo, pai, filho);
            pai = filho;
        }//se não tem filho à esquerda passa para o filho da direita
        else
        {
            avo = pai;
            pai = pai->direita;
        }
    }
}

template<class T>
void ABP<T>::BalancearArvoreLista()
{
    int n = Dimensao();
    float lg = log2((float) (n + 1));
    int exp = (int) floor(lg);
    int m = (int) pow(2.0, double(exp)) - 1;
    //realizar primeiro grupo de rotações à esquerda
    RealizarRotacoes(n-m);
    while(m>1)
    {
        m = m/2;
        //realizar segundo grupo de rotações à esquerda
        RealizarRotacoes(m);
    }
}

template<class T>
void ABP<T>::RotacaoDireita(NoABP<T>* avo, NoABP<T>* pai, NoABP<T>* filho)
{
    //se pai não é a raiz, o filho passa a pai
    if (avo != 0)
        avo->direita = filho;
        //se pai é a raiz, a nova raiz passa a ser o filho
    else
        raiz = filho;
    //a esquerda do pai passa a ser a direita do filho
    pai->esquerda = filho->direita;
    //a direita do filho passa a ser o pai
    filho->direita = pai;
}

template <class T>
void ABP<T>::RotacaoEsquerda(NoABP<T>* avo, NoABP<T>* pai, NoABP<T>* filho)
{
    //se pai não é a raiz, o filho passa a pai
    if (avo != 0)
        avo->direita = filho;
        //se pai é a raiz, a nova raiz passa a ser o filho
    else
        raiz = filho;
    //a direita do pai passa a ser a esquerda do filho
    pai->direita = filho->esquerda;
    //a esquerda do filho passa a ser o pai
    filho->esquerda = pai;
}

template <class T>
void ABP<T>::RealizarRotacoes(int n)
{
    //criar nós avô, pai e filho
    NoABP<T>* avo = 0;
    NoABP<T>* pai = raiz;
    NoABP<T>* filho = raiz->direita;
    for (int i = n; i > 0; i--)
    {
        if (filho != 0)
        {
            //realizar rotação à esquerda
            RotacaoEsquerda(avo, pai, filho);
            //avancar os apontadores após a rotação
            avo = filho;
            pai = avo->direita;
            filho = pai->direita;
        }
    }
}

template<class T>
void ABP<T>::ProfundidadePrimeiro() const
{
    //se a árvore está vazia indica e termina
    if (raiz == 0)
    {
        cout << "Arvore vazia!" << endl;
        return;
    }
    PreOrdem(raiz, 0);
    cout << endl;
}

template<class T>
void ABP<T>::PreOrdem(NoABP<T>* no, NoABP<T>* pai) const
{
    //mostra o elemento do nó e depois os elementos das subárvores esq e dir
    if (no == 0)
        return;
    cout << no->elemento;
    if (pai == 0)
        cout << ' ';
    else
        cout << '(' << pai->elemento << ") ";
    PreOrdem(no->esquerda, no);
    PreOrdem(no->direita, no);
}

#endif /* ABP_H */

