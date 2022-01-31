#ifndef DEC0006_LISTA_ENCADEADA_ABSTRATA_H
#define DEC0006_LISTA_ENCADEADA_ABSTRATA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento

/**
 * @brief A interface de uma lista encadeada de dados.
 * 
 * @tparam T O tipo dos dados armazenados na lista.
 */
template<typename T>
class ListaEncadeadaAbstrata
{
public:
    virtual ~ListaEncadeadaAbstrata();

    /**
     * @brief Obtém a quantidade de itens na lista.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t tamanho() const = 0;
    /**
     * @brief Indica se há algum item na lista ou não.
     * 
     * @return true se houver algum item na lista; false caso contrário.
     */
    virtual bool vazia() const = 0;

    /**
     * @brief Obtém a posição de um item na lista. Lança
     * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item cuja posição deseja-se obter.
     * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
     * item na lista, a posição da primeira ocorrência.
     */
    virtual std::size_t posicao(T dado) const = 0;
    /**
     * @brief Indica se um dado item está contido na lista ou não.
     * 
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    virtual bool contem(T dado) const = 0;

    /**
     * @brief Insere um item no início da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado) = 0;
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
    virtual void inserir(std::size_t posicao, T dado) = 0;
    /**
     * @brief Insere um item no fim da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado) = 0;

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoInicio() = 0;
    /**
     * @brief Remove um item de uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    virtual T removerDe(std::size_t posicao) = 0;
    /**
     * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoFim() = 0;
    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */
    virtual void remover(T dado) = 0;

protected:
    Elemento<T>* _primeiro{nullptr};
    std::size_t _tamanho{0};
};

template<typename T>
ListaEncadeadaAbstrata<T>::~ListaEncadeadaAbstrata() = default;

#endif