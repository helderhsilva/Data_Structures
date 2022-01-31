#ifndef MINHALISTAENCADEADA_H
#define MINHALISTAENCADEADA_H

#include "ListaEncadeadaAbstrata.hpp"

template <typename T>
class MinhaListaEncadeada :  public ListaEncadeadaAbstrata<T>
{
    public:
    MinhaListaEncadeada()
    {
        this->_tamanho = 0;
        this->_primeiro = nullptr;
    };

    ~MinhaListaEncadeada()
    {

        Elemento<T> *EL_Atual = this->_primeiro;

        while (EL_Atual != nullptr)
        {
            Elemento<T> *EL_Auxiliar = EL_Atual->_proximo;

            delete EL_Atual;

            EL_Atual = EL_Auxiliar;
        }
    };

    /*-*/

    /**
     * @brief Indica se há algum item na lista ou não.
     *
     * @return true se houver algum item na lista; false caso contrário.
     */
    bool estaVazia()
    {
        if (this->getTamanho() == 0)
        {
            return true;
        }
        else
            return false;
    };

    /**
     * @brief Obtém a quantidade de itens na lista.
     *
     * @return Um inteiro maior ou igual a 0.
     */
    int getTamanho()
    {
        return this->_tamanho;
    };

    /**
     * @brief Obtém a posição de um item na lista. Lança
     * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     *
     * @param dado O item cuja posição deseja-se obter.
     * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
     * item na lista, a posição da primeira ocorrência.
     */
    int posicao(T umDado)
    {
        if (this->estaVazia())
        {
            throw lista_encadeada_vazia_exception();
        }

        Elemento<T> *EL_Atual = this->_primeiro;
        int index = 0;

        while (EL_Atual != nullptr)
        {
            if (EL_Atual->_dado == umDado)
            {
                return index;
            }
            index++;
            EL_Atual = EL_Atual->_proximo;
        }
        throw posicao_invalida_exception();
    };

    /**
     *
     * @brief Indica se um dado item está contido na lista ou não.
     *
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    bool contem(T umDado)
    {
        Elemento<T> *EL_Atual = this->_primeiro;

        while (EL_Atual != nullptr)
        {
            if (EL_Atual->_dado == umDado)
            {
                return true;
            }
            EL_Atual = EL_Atual->_proximo;
        }
        return false;
    };

    /**
     * @brief Insere um item no início da lista.
     *
     * @param dado O item sendo inserido.
     */
    void adicionaNoInicio(T umDado)
    {
        Elemento<T> *EL_InserirInicio = new Elemento<T>();

        EL_InserirInicio->_dado = umDado;
        EL_InserirInicio->_proximo = this->_primeiro;

        this->_primeiro = EL_InserirInicio;
        this->_tamanho++;
        return;
    };

    /**
     * @brief Insere um item em uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa
     * [0, tamanho].
     *
     * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
     * uma posição já ocupada, a posição do item que já estava naquela posição
     * será posicao + 1; inserir-se na posicao tamanho significa inserir-se no
     * fim da lista.
     * @param dado O item sendo inserido.
     */
    void adicionaNaPosicao(T umDado, int umaPosicao)
    {
        if (umaPosicao < 0 || umaPosicao >= this->_tamanho + 1)
        {
            throw posicao_invalida_exception();
        }

        if (umaPosicao == 0)
        {
            this->adicionaNoInicio(umDado);
            return;
        }

        if (umaPosicao == this->_tamanho)
        {
            this->adicionaNoFim(umDado);
            return;
        }

        Elemento<T> *EL_Auxiliar = this->_primeiro;

        for (int i = 1; i < umaPosicao; i++)
        {
            EL_Auxiliar = EL_Auxiliar->_proximo;
        }

        Elemento<T> *EL_InserirMeio = new Elemento<T>();

        EL_InserirMeio->_dado = umDado;
        EL_InserirMeio->_proximo = EL_Auxiliar->_proximo;

        EL_Auxiliar->_proximo = EL_InserirMeio;
        this->_tamanho++;
        return;
    };

    /**
     * @brief Insere um item no fim da lista.
     *
     * @param dado O item sendo inserido.
     */
    void adicionaNoFim(T umDado)
    {
        if (this->_primeiro == nullptr)
        {
            this->adicionaNoInicio(umDado);
            return;
        }

        Elemento<T> *EL_Auxiliar = this->_primeiro;

        while (EL_Auxiliar->_proximo != nullptr)
        {
            EL_Auxiliar = EL_Auxiliar->_proximo;
        }

        Elemento<T> *EL_InserirFim = new Elemento<T>();
        EL_InserirFim->_dado = umDado;
        EL_InserirFim->_proximo = nullptr;

        EL_Auxiliar->_proximo = EL_InserirFim;
        this->_tamanho++;

        return;
    };

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     *
     * @return O item removido.
     */
    T retiraDoInicio()
    {
        if (this->estaVazia())
        {
            throw lista_encadeada_vazia_exception();
        }

        Elemento<T> *EL_RemoverInicio = this->_primeiro;
        this->_primeiro = EL_RemoverInicio->_proximo;
        T Auxiliar = EL_RemoverInicio->_dado;

        delete EL_RemoverInicio;

        this->_tamanho--;

        return Auxiliar;
    };

    /**
     * @brief Remove um item de uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
     *
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    T retiraDaPosicao(int umaPosicao)
    {
        if (umaPosicao < 0 || umaPosicao >= this->_tamanho)
        {
            throw posicao_invalida_exception();
        }

        if (umaPosicao == 0)
        {
            return this->retiraDoInicio();
        }

        if (umaPosicao == this->_tamanho - 1)
        {
            return this->retiraDoFim();
        }

        Elemento<T> *EL_Auxiliar = this->_primeiro;

        for (int i = 0; i < umaPosicao - 1; i++)
        {
            EL_Auxiliar = EL_Auxiliar->_proximo;
        }

        Elemento<T> *EL_Remover = this->_primeiro;

        for (int j = 0; j < umaPosicao; j++)
        {
            EL_Remover = EL_Remover->_proximo;
        }

        T Auxiliar = EL_Remover->_dado;
        EL_Auxiliar->_proximo = EL_Remover->_proximo;

        delete EL_Remover;

        this->_tamanho--;

        return Auxiliar;
    };

    /**
     * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     *
     * @return O item removido.
     */
    T retiraDoFim()
    {
        if (this->estaVazia())
        {
            throw lista_encadeada_vazia_exception();
        }

        if (this->_tamanho == 1)
        {
            return this->retiraDoInicio();
        }

        Elemento<T> *EL_RemoverFim = this->_primeiro;
        Elemento<T> *EL_AntesFim = this->_primeiro;

        while (EL_RemoverFim->_proximo != nullptr)
        {
            EL_RemoverFim = EL_RemoverFim->_proximo;
        }

        while (EL_AntesFim->_proximo != EL_RemoverFim)
        {
            EL_AntesFim = EL_AntesFim->_proximo;
        }

        EL_AntesFim->_proximo = nullptr;
        T Auxiliar = EL_RemoverFim->_dado;

        delete EL_RemoverFim;

        this->_tamanho--;

        return Auxiliar;
    };

    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     *
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */
    T retiraEspecifico(T umDado)
    {
        if (this->getTamanho() == 0)
        {
            throw lista_encadeada_vazia_exception();
        }

        if (this->contem(umDado))
        {
            return this->retiraDaPosicao(this->posicao(umDado));
        }

        throw posicao_invalida_exception();
    };
};

#endif