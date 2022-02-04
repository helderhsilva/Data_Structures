#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "MinhaArvoreDeBuscaBinaria.hpp"

/**
 * @brief Representa uma árvore AVL.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public MinhaArvoreDeBuscaBinaria<T>
{
    private:

    Nodo<T> *LeftLeftRotation(Nodo<T> *pai) 
    {
        Nodo<T> *filho = pai->filhoDireita;
        pai->filhoDireita = filho->filhoEsquerda;
        filho->filhoEsquerda = pai;

        return filho;
    }

    Nodo<T> *RightRightRotation(Nodo<T> *pai) 
    {
        Nodo<T> *filho = pai->filhoEsquerda;
        pai->filhoEsquerda = filho->filhoDireita;
        filho->filhoDireita = pai;

        return filho;
    }

    Nodo<T> *LeftRightRotation(Nodo<T> *pai) 
    {
        pai->filhoEsquerda = this->LeftLeftRotation(pai->filhoEsquerda);
        return this->RightRightRotation(pai);
    }

    Nodo<T> *RightLeftRotation(Nodo<T> *pai) 
    {
        pai->filhoDireita = this->RightRightRotation(pai->filhoDireita);
        return this->LeftLeftRotation(pai);
    }

    int fator_b(Nodo<T> *chave) const 
    {
        int Fb = 0, He = 0, Hd = 0;

        if (chave != nullptr)
        {
            if (chave->filhoEsquerda != nullptr)
            {
                He = this->alturaSubArvore(chave->filhoEsquerda) + 1;
            }
            if (chave->filhoDireita != nullptr)
            {
                Hd = this->alturaSubArvore(chave->filhoDireita) + 1;
            }

            Fb = He - Hd;

            return Fb;
        }
        return 0;
    }

    void balanceiaArvore(Nodo<T> *pai)
    {
        if (pai != nullptr)
        {
            int Fb = this->fator_b(pai);

            // Rotação Simples a Esquerda
            if (Fb < -1)
            {
                Fb = this->fator_b(pai->filhoDireita);
                if (Fb <= 0)
                {
                    Nodo<T> *avo = this->buscaPai(pai->chave, this->_raiz);

                    if (avo == nullptr)
                    {
                        this->_raiz = this->LeftLeftRotation(pai);
                    }
                    else
                    {
                        avo->filhoDireita = this->LeftLeftRotation(pai);
                    }
                    return;

                }
                else    // Rotação Direita Esquerda
                {
                    Nodo<T> *avo = this->buscaPai(pai->chave, this->_raiz);

                    if (avo == nullptr)
                    {
                        this->_raiz = this->RightLeftRotation(pai);
                    }
                    else
                    {
                        avo->filhoDireita = this->RightLeftRotation(pai);
                    }

                    return;
                }
            }

            // Rotação Simples a Direita
            if (Fb > 1)
            {
                Fb = this->fator_b(pai->filhoEsquerda);
                if (Fb >= 0)
                {
                    Nodo<T> *avo = this->buscaPai(pai->chave, this->_raiz);

                    if (avo == nullptr)
                    {
                        this->_raiz = this->RightRightRotation(pai);
                    }
                    else
                    {
                        avo->filhoEsquerda = this->RightRightRotation(pai);
                    }
                    return;
                }
                else    // Rotação Esquerda Direita
                {   
                    Nodo<T> *avo = this->buscaPai(pai->chave, this->_raiz);

                    if (avo == nullptr)
                    {
                        this->_raiz = this->LeftRightRotation(pai);
                    }
                    else
                    {
                        avo->filhoEsquerda = this->LeftRightRotation(pai);
                    }
                    return;
                }
            }

            if (pai->chave == this->_raiz->chave)
            {
                return;
            }
            
            return balanceiaArvore(this->buscaPai(pai->chave, this->_raiz));
        }
        return;
    }

    public:

    void inserir(T chave)
    {
        MinhaArvoreDeBuscaBinaria<T>::inserir(chave);
        Nodo<T> *pai = this->buscaPai(chave, this->_raiz);
        this->balanceiaArvore(pai);
    }

    void remover(T chave)
    {
        Nodo<T> *pai = this->buscaPai(chave, this->_raiz);
        MinhaArvoreDeBuscaBinaria<T>::remover(chave);
        this->balanceiaArvore(pai);
    }
};

#endif