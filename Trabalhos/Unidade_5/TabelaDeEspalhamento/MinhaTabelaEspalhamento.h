#ifndef MINHA_TABELA_ESPALHAMENTO_H
#define MINHA_TABELA_ESPALHAMENTO_H

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente

#include <cmath>
#include <typeinfo>

template<typename T, std::size_t _capacidade>
class MinhaTabelaEspalhamento final: public TabelaEspalhamentoAbstrata<T, _capacidade>
{
public:
    ~MinhaTabelaEspalhamento() {};

    /**
     * @brief Obtém a capacidade da tabela.
     * 
     * @return Um inteiro maior do que 0.
     */
    std::size_t capacidade() const 
    {
        size_t capacity = this->_tabela.size();

        return capacity;
    };

    /**
     * @brief Insere um dado na tabela. Se a tabela já contiver o dado, ele não
     * é inserido novamente.
     * 
     * @param dado O dado a ser inserido.
     */
    void inserir(T dado) 
    {
        if (!this->contem(dado))
        {
            size_t chave = funcaoEspalhamento(dado);
            this->_tabela.at(chave).adicionaNoFim(dado);
        }
        else
        {
            return;
        }
    };

    /**
     * @brief Remove um dado da tabela. Se a tabela não contiver o dado, uma
     * exceção ExcecaoDadoInexistente é lançada.
     * 
     * @param dado O dado a ser removido.
     */
    void remover(T dado) 
    {
        if (this->contem(dado))
        {
            size_t chave = funcaoEspalhamento(dado);
            this->_tabela.at(chave).retiraEspecifico(dado);
        }
        else
        {
            throw ExcecaoDadoInexistente();
        }
    };

    /**
     * @brief Verifica se \p dado está contido na tabela.
     * 
     * @param dado O dado sendo buscado.
     * @return true se o dado está contido na tabela; false caso contrário.
     */
    bool contem(T dado) const
    {
        size_t chave = funcaoEspalhamento(dado);
        bool contain = this->_tabela.at(chave).contem(dado);

        return contain;
    };

    /**
     * @brief Obtém a quantidade de dados contidos na árvore.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
    std::size_t quantidade() const 
    {
        size_t amount = 0;

        for (size_t i = 0; i < this->_tabela.size(); i++)
        {
            amount = amount + this->_tabela.at(i).getTamanho();
        }
        
        return amount;
    };

protected:
    /**
     * @brief Obtém a posição correspondente na tabela para o dado.
     * 
     * @param dado O dado.
     * @return Um inteiro na faixa [0, capacidade).
     */
    std::size_t funcaoEspalhamento(T dado) const 
    {
        size_t chave = T_dado(dado) % this->capacidade();

        return chave;
    };

    // Funções para realizar o hash
    std::size_t T_dado(int dado) const
    {
        size_t intForKey = (size_t)dado;

        return intForKey;
    };

    std::size_t T_dado(std::string dado) const
    {
        size_t intForKey = 0;

        for (size_t i = 0; i < dado.length(); i++)
        {
            intForKey += (size_t)dado[i] * pow(31, dado.length() - (i+1));
        }
                
        return intForKey;
    };
};

#endif
