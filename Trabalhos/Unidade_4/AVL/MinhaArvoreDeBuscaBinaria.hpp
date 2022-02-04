#ifndef MINHA_ARVORE_DE_BUSCA_BINARIA_HPP
#define MINHA_ARVORE_DE_BUSCA_BINARIA_HPP

#include "ArvoreDeBuscaBinaria.hpp"

/**
 * @brief Representa uma árvore binária de busca.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template<typename T>
class MinhaArvoreDeBuscaBinaria : public ArvoreDeBuscaBinaria<T>
{
    protected:
    int buscaQuantidade(Nodo<T> *chave) const
    {
        if (chave != nullptr)
        {
            return (1 + this->buscaQuantidade(chave->filhoEsquerda) + this->buscaQuantidade(chave->filhoDireita));
        }
        return 0;
    }

    /***********************************************************************************************************/

    void percursoEmOrdem(Nodo<T> *chave, ListaEncadeadaAbstrata<T> *listaEmOrdem) const
    {
        if (chave != nullptr)
        {
            this->percursoEmOrdem(chave->filhoEsquerda, listaEmOrdem);
            listaEmOrdem->adicionaNoFim(chave->chave);
            this->percursoEmOrdem(chave->filhoDireita, listaEmOrdem);
        }
        return;
    }

    void percursoPreOrdem(Nodo<T> *chave, ListaEncadeadaAbstrata<T> *listaPreOrdem) const
    {
        if (chave != nullptr)
        {
            listaPreOrdem->adicionaNoFim(chave->chave);
            this->percursoPreOrdem(chave->filhoEsquerda, listaPreOrdem);
            this->percursoPreOrdem(chave->filhoDireita, listaPreOrdem);
        }
        return;
    }

    void percursoPosOrdem(Nodo<T> *chave, ListaEncadeadaAbstrata<T> *listaPosOrdem) const
    {
        if (chave != nullptr)
        {
            this->percursoPosOrdem(chave->filhoEsquerda, listaPosOrdem);
            this->percursoPosOrdem(chave->filhoDireita, listaPosOrdem);
            listaPosOrdem->adicionaNoFim(chave->chave);
        }
        return;
    }

    /***********************************************************************************************************/

    void insereNaArvore(Nodo<T> *chaveAtual, T novoValor)
    {
        if (this->vazia())
        {
            Nodo<T> *novaChave = new Nodo<T>{novoValor, 0};

            delete this->_raiz;

            this->_raiz = novaChave;

            return;
        }

        if (novoValor < chaveAtual->chave)
        {
            if (chaveAtual->filhoEsquerda == nullptr)
            {
                Nodo<T> *novaChave = new Nodo<T>{novoValor, chaveAtual->altura+1};

                chaveAtual->filhoEsquerda = novaChave;
            }
            else
            {
                this->insereNaArvore(chaveAtual->filhoEsquerda, novoValor);
            }
        }
        else
        {
            if (chaveAtual->filhoDireita == nullptr)
            {
                Nodo<T> *novaChave = new Nodo<T>{novoValor, chaveAtual->altura+1};

                chaveAtual->filhoDireita = novaChave;
            }
            else
            {
                this->insereNaArvore(chaveAtual->filhoDireita, novoValor);
            }
        }
        return;
    }

    /***********************************************************************************************************/

    Nodo<T> *buscaContem(T chave, Nodo<T> *raiz) const
    {
        while (raiz != nullptr && raiz->chave != chave)
        {
            if (raiz->chave < chave)
            {
                raiz = raiz->filhoDireita;
            }
            else
            {
                raiz = raiz->filhoEsquerda;
            }
        }
        return raiz; 
    }

    Nodo<T> *buscaPai(T chave, Nodo<T> *pai) const
    {
        if (pai == nullptr)
        {
            return nullptr;
        }

        if (pai->chave == chave)
        {
            return nullptr;
        }

        if (pai != nullptr && pai->chave != chave)
        {
            if (pai->chave < chave)
            {
                if (pai->filhoDireita->chave != chave)
                {
                    return this->buscaPai(chave, pai->filhoDireita);
                }
            }

            if (pai->chave > chave)
            {
                if (pai->filhoEsquerda->chave != chave)
                {
                    return this->buscaPai(chave, pai->filhoEsquerda);
                }
            }
        }
        return pai;
    }

    /***********************************************************************************************************/

    int alturaSubArvore(Nodo<T> *chave) const
    {
        int alturaEsquerda = 0, alturaDireita = 0, altura = 0;

        if (chave->filhoEsquerda != nullptr)
        {
            alturaEsquerda = 1 + alturaSubArvore(chave->filhoEsquerda);
        }

        if (chave->filhoDireita != nullptr)
        {
            alturaDireita = 1 + alturaSubArvore(chave->filhoDireita);
        }

        return checaAltura(alturaEsquerda, alturaDireita, altura);
    }

    int checaAltura(int Esquerda, int Direita, int altura) const
    {
        if (Esquerda >= Direita)
        {
            altura = Esquerda;
            return altura;
        }
        else
        {
            altura = Direita;
            return altura;
        }
    }

    /***********************************************************************************************************/

    T removeDaArvore(T chaveParaRemover, Nodo<T> *chavePai)
    {
        Nodo<T> *chave;

        if (chavePai->chave == chaveParaRemover)
        {
            if (verificaFolha(chavePai))
            {
                T chaveRemovida = chavePai->chave;

                chavePai = nullptr;
                delete chavePai;

                return chaveRemovida;
            }
            chave = chavePai;
        }
        else if (chavePai->filhoEsquerda != nullptr && chavePai->filhoEsquerda->chave == chaveParaRemover)
        {
            chave = chavePai->filhoEsquerda;

            if (verificaFolha(chave))
            {
                T chaveRemovida = chave->chave;

                chavePai->filhoEsquerda = nullptr;
                delete chave;

                return chaveRemovida;
            }
        }
        else if (chavePai->filhoDireita != nullptr && chavePai->filhoDireita->chave == chaveParaRemover)
        {
            chave = chavePai->filhoDireita;

            if (verificaFolha(chave))
            {
                T chaveRemovida = chave->chave;

                chavePai->filhoDireita = nullptr;
                delete chave;

                return chaveRemovida;
            }
        }
        
        if(chave != nullptr && chave->filhoDireita != nullptr)
        {
            Nodo<T> *chaveAux = chave->filhoDireita;
            Nodo<T> *chavePaiAux = chave;

            while (chaveAux->filhoEsquerda != nullptr)
            {
                chavePaiAux = chaveAux;
                chaveAux = chaveAux->filhoEsquerda;
            }

            chave->chave = chaveAux->chave;
            chaveAux->chave = chaveParaRemover;
            return this->removeDaArvore(chaveParaRemover, chavePaiAux);
        }
        return chaveParaRemover;
    }

    bool verificaFolha(Nodo<T> *chave)
    {
        if (chave->filhoEsquerda == nullptr && chave->filhoDireita == nullptr)
        {
            return true;
        }
        return false;
    }

    /***********************************************************************************************************/

    void destruirArvore(Nodo<T> *chave)
    {
        if (chave != nullptr)
        {
            this->destruirArvore(chave->filhoEsquerda);
            this->destruirArvore(chave->filhoDireita);
            delete chave;
        }
    }
    
    public:
    ~MinhaArvoreDeBuscaBinaria() 
    {
        if (this->_raiz != nullptr)
        {
        this->destruirArvore(this->_raiz);
        }
        return;
    };

    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
    bool vazia() const 
    {
        if (this->quantidade() == 0 || this->_raiz == nullptr)
        {
            return true;
        }
        return false;
    };
    
    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    int quantidade() const 
    {
        int quantidade = 0;

        quantidade = this->buscaQuantidade(this->_raiz);

        return quantidade;
    };
    
    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    bool contem(T chave) const 
    {    
        if (!this->vazia())
        {
            Nodo<T> *raiz = this->buscaContem(chave, this->_raiz);

            if (raiz == nullptr)
            {
                return false;
            }

            if (raiz->chave == chave)
            {
                return true;
            }

        }
        return false;
    };
    
    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos. Se chave é nula, retorna a altura da arvore.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    std::optional<int> altura(T chave) const 
    {
        if (this->contem(chave))
        {
            Nodo<T> *raiz = this->buscaContem(chave, this->_raiz);
            return this->alturaSubArvore(raiz);
        }
        return std::nullopt;
    };

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */        
    void inserir(T chave) 
    {
        return this->insereNaArvore(this->_raiz, chave);
    };

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     * @return Retorna a chave removida ou nullptr se a chave nao esta na arvore
     */        
    void remover(T chave)
    {
        Nodo<T> *raiz = this->_raiz;


        if(raiz->chave == chave && this->verificaFolha(raiz))
        {
            this->_raiz = nullptr;

            delete raiz;

            return;
        }

        if (this->contem(chave))
        {
            Nodo<T> *chavePai = this->buscaPai(chave, raiz);
            if (chavePai == nullptr)
            {
                this->removeDaArvore(chave, raiz);
                return;
            }
            this->removeDaArvore(chave, chavePai);
        }
        return;
    };

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh chaveP do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    std::optional<T> filhoEsquerdaDe(T chave) const 
    {
        if (this->contem(chave))
        {
            Nodo<T> *chavePai = this->buscaContem(chave, this->_raiz);

            if (chavePai->filhoEsquerda != nullptr)
            {
                return chavePai->filhoEsquerda->chave;
            }
        }
        return std::nullopt;
    };

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */        
    std::optional<T> filhoDireitaDe(T chave) const 
    {
        if (this->contem(chave))
        {
            Nodo<T> *chavePai = this->buscaContem(chave, this->_raiz);

            if (chavePai->filhoDireita != nullptr)
            {
                return chavePai->filhoDireita->chave;
            }
        }
        return std::nullopt;
    };

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem. 
     */
    ListaEncadeadaAbstrata<T>* emOrdem() const 
    {
        ListaEncadeadaAbstrata<T> *listaEmOrdem = new MinhaListaEncadeada<T>();

        this->percursoEmOrdem(this->_raiz, listaEmOrdem);

        return listaEmOrdem;
    };

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem. 
     */
    ListaEncadeadaAbstrata<T>* preOrdem() const 
    {
        ListaEncadeadaAbstrata<T> *listaPreOrdem = new MinhaListaEncadeada<T>();

        this->percursoPreOrdem(this->_raiz, listaPreOrdem);

        return listaPreOrdem;
    };

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem. 
     */
    ListaEncadeadaAbstrata<T>* posOrdem() const 
    {
        ListaEncadeadaAbstrata<T> *listaPosOrdem = new MinhaListaEncadeada<T>();

        this->percursoPosOrdem(this->_raiz, listaPosOrdem);

        return listaPosOrdem;
    };
};

#endif