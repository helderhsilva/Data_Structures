#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 *
 * @tparam T O tipo dos dados armazenados na lista.
 */
template <typename T>
class MinhaListaEncadeada : public ListaEncadeadaAbstrata<T>
{
    // Implemente aqui as funcões marcadas com virtual na ListaEncadeadaAbstrata
    // Lembre-se de implementar o construtor e destrutor da classe

    ~MinhaListaEncadeada()
    {

        Elemento<T> *EL_Atual = this->_primeiro;

        while (EL_Atual != nullptr)
        {
            Elemento<T> *EL_Auxiliar = EL_Atual->proximo;

            delete EL_Atual;

            EL_Atual = EL_Auxiliar;
        }
    };

    /*-*/

    /**
     * @brief Obtém a quantidade de itens na lista.
     *
     * @return Um inteiro maior ou igual a 0.
     */
    std::size_t tamanho() const
    {
        return this->_tamanho;
    };

    /**
     * @brief Indica se há algum item na lista ou não.
     *
     * @return true se houver algum item na lista; false caso contrário.
     */
    bool vazia() const
    {
        if (this->tamanho() == 0)
        {
            return true;
        }
        else
            return false;
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
    std::size_t posicao(T dado) const
    {
        if (this->vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }

        Elemento<T> *EL_Atual = this->_primeiro;
        std::size_t index = 0;

        while (EL_Atual != nullptr)
        {
            if (EL_Atual->dado == dado)
            {
                return index;
            }
            index++;
            EL_Atual = EL_Atual->proximo;
        }
        throw ExcecaoDadoInexistente();
    };

    /**
     *
     * @brief Indica se um dado item está contido na lista ou não.
     *
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    bool contem(T dado) const
    {
        Elemento<T> *EL_Atual = this->_primeiro;

        while (EL_Atual != nullptr)
        {
            if (EL_Atual->dado == dado)
            {
                return true;
            }
            EL_Atual = EL_Atual->proximo;
        }
        return false;
    };

    /**
     * @brief Insere um item no início da lista.
     *
     * @param dado O item sendo inserido.
     */
    void inserirNoInicio(T dado)
    {
        Elemento<T> *EL_InserirInicio = new Elemento<T>{dado, this->_primeiro};

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
    void inserir(std::size_t posicao, T dado)
    {
        if (posicao < 0 || posicao >= this->_tamanho + 1)
        {
            throw ExcecaoPosicaoInvalida();
        }

        if (posicao == 0)
        {
            this->inserirNoInicio(dado);
            return;
        }

        if (posicao == this->_tamanho)
        {
            this->inserirNoFim(dado);
            return;
        }

        Elemento<T> *EL_Auxiliar = this->_primeiro;

        for (int i = 1; i < posicao; i++)
        {
            EL_Auxiliar = EL_Auxiliar->proximo;
        }

        Elemento<T> *EL_InserirMeio = new Elemento<T>{dado, EL_Auxiliar->proximo};

        EL_Auxiliar->proximo = EL_InserirMeio;
        this->_tamanho++;
        return;
    };

    /**
     * @brief Insere um item no fim da lista.
     *
     * @param dado O item sendo inserido.
     */
    void inserirNoFim(T dado)
    {
        Elemento<T> *EL_Auxiliar = this->_primeiro;

        if (this->_primeiro == nullptr)
        {
            this->inserirNoInicio(dado);
            return;
        }

        Elemento<T> *EL_InserirFim = new Elemento<T>{dado, nullptr};

        while (EL_Auxiliar->proximo != nullptr)
        {
            EL_Auxiliar = EL_Auxiliar->proximo;
        }

        EL_Auxiliar->proximo = EL_InserirFim;
        this->_tamanho++;

        return;
    };

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     *
     * @return O item removido.
     */
    T removerDoInicio()
    {
        if (this->vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }

        Elemento<T> *EL_RemoverInicio = this->_primeiro;
        this->_primeiro = EL_RemoverInicio->proximo;
        T Auxiliar = EL_RemoverInicio->dado;

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
    T removerDe(std::size_t posicao)
    {
        if (posicao < 0 || posicao >= this->_tamanho)
        {
            throw ExcecaoPosicaoInvalida();
        }

        if (posicao == 0)
        {
            return this->removerDoInicio();
        }

        if (posicao == this->_tamanho - 1)
        {
            return this->removerDoFim();
        }

        Elemento<T> *EL_Auxiliar = this->_primeiro;

        for (int i = 0; i < posicao - 1; i++)
        {
            EL_Auxiliar = EL_Auxiliar->proximo;
        }

        Elemento<T> *EL_Remover = this->_primeiro;

        for (int j = 0; j < posicao; j++)
        {
            EL_Remover = EL_Remover->proximo;
        }

        T Auxiliar = EL_Remover->dado;
        EL_Auxiliar->proximo = EL_Remover->proximo;

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
    T removerDoFim()
    {
        if (this->vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }

        if (this->_tamanho == 1)
        {
            return this->removerDoInicio();
        }

        Elemento<T> *EL_RemoverFim = this->_primeiro;
        Elemento<T> *EL_AntesFim = this->_primeiro;

        while (EL_RemoverFim->proximo != nullptr)
        {
            EL_RemoverFim = EL_RemoverFim->proximo;
        }

        while (EL_AntesFim->proximo != EL_RemoverFim)
        {
            EL_AntesFim = EL_AntesFim->proximo;
        }

        EL_AntesFim->proximo = nullptr;
        T Auxiliar = EL_RemoverFim->dado;

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
    void remover(T dado)
    {
        if (this->tamanho() == 0)
        {
            throw ExcecaoListaEncadeadaVazia();
        }

        if (this->contem(dado))
        {
            this->removerDe(this->posicao(dado));
            return;
        }

        throw ExcecaoDadoInexistente();
    };
};

#endif