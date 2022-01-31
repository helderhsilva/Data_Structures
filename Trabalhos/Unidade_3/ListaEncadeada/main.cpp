#include <array>
// std::array
#include <cstddef>
// std::size_t
#include <initializer_list>
// {...}
#include <iostream>
// std::clog
#include <iterator>
// std::size

#include "gtest/gtest.h"
// testing::InitGoogleTest
// RUN_ALL_TESTS

#include "excecoes.h"
// ExcecaoListaEncadeadaVazia
// ExcecaoPosicaoInvalida
#include "ListaEncadeadaAbstrata.h"
// ListaEncadeadaAbstrata
#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada

using std::clog;
using std::size;

using testing::InitGoogleTest;

template class MinhaListaEncadeada<int>;
template class MinhaListaEncadeada<std::string>;

template <typename T>
struct Esperado
{
    T dado;
    std::size_t posicao;
};

TEST(TesteListaEncadeada, Inicializacao)
{
    using T = int;

    ListaEncadeadaAbstrata<T> const *const lista{new MinhaListaEncadeada<T>};

    ASSERT_TRUE(lista->vazia());
    ASSERT_EQ(lista->tamanho(), 0);

    delete lista;
}

TEST(TesteListaEncadeada, InsercaoNoInicio)
{
    using T = int;

    ListaEncadeadaAbstrata<T> *const lista{new MinhaListaEncadeada<T>};

    std::array<Esperado<T>, 5> const esperados{{{0, 4},
                                                {10, 3},
                                                {20, 2},
                                                {30, 1},
                                                {40, 0}}};

    for (Esperado<T> const &esperado : esperados)
        lista->inserirNoInicio(esperado.dado);

    ASSERT_EQ(lista->tamanho(), size(esperados));
    ASSERT_TRUE(!lista->vazia());

    for (Esperado<T> const &esperado : esperados)
    {
        ASSERT_EQ(lista->posicao(esperado.dado), esperado.posicao);
        ASSERT_TRUE(lista->contem(esperado.dado));
    }

    delete lista;
}

TEST(TesteListaEncadeada, Insercao)
{
    using T = int;

    ListaEncadeadaAbstrata<T> *lista{nullptr};

    // Posições inválidas
    {
        lista = new MinhaListaEncadeada<T>;

        T const dado{0};

        for (std::size_t const posicao : {1, 2, 100})
            ASSERT_THROW(lista->inserir(posicao, dado), ExcecaoPosicaoInvalida);

        ASSERT_EQ(lista->tamanho(), 0);
        ASSERT_TRUE(lista->vazia());
        ASSERT_THROW(lista->posicao(dado), ExcecaoListaEncadeadaVazia);
        ASSERT_TRUE(!lista->contem(dado));

        delete lista;
    }

    // Inserção no fim
    {
        lista = new MinhaListaEncadeada<T>;

        std::array<Esperado<T>, 6> const esperados{{{0, 0},
                                                    {10, 1},
                                                    {20, 2},
                                                    {30, 3},
                                                    {40, 4},
                                                    {10, 1}}};

        for (std::size_t i{0}; i < size(esperados); ++i)
            lista->inserir(i, esperados[i].dado);

        ASSERT_THROW(lista->posicao(50), ExcecaoDadoInexistente);

        ASSERT_THROW(
            lista->inserir(size(esperados) + 1, 0),
            ExcecaoPosicaoInvalida);

        ASSERT_EQ(lista->tamanho(), size(esperados));
        ASSERT_TRUE(!lista->vazia());

        for (Esperado<T> const &esperado : esperados)
        {
            ASSERT_EQ(lista->posicao(esperado.dado), esperado.posicao);
            ASSERT_TRUE(lista->contem(esperado.dado));
        }

        delete lista;
    }

    // Inserção no início e no meio
    {
        lista = new MinhaListaEncadeada<T>;

        std::array<Esperado<T>, 5> const dados{{{0, 0},
                                                {10, 1},
                                                {20, 2},
                                                {30, 3},
                                                {40, 4}}};

        for (Esperado<T> const &dado : dados)
            lista->inserir(dado.posicao, dado.dado);

        std::array<Esperado<T>, 2> const esperados{{{50, 0},
                                                    {60, 3}}};

        for (Esperado<T> const &esperado : esperados)
            lista->inserir(esperado.posicao, esperado.dado);

        ASSERT_EQ(lista->tamanho(), size(dados) + size(esperados));

        for (Esperado<T> const &esperado : esperados)
        {
            ASSERT_EQ(lista->posicao(esperado.dado), esperado.posicao);
            ASSERT_TRUE(lista->contem(esperado.dado));
        }

        delete lista;
    }
}

TEST(TesteListaEncadeada, InsercaoNoFim)
{
    using T = int;

    ListaEncadeadaAbstrata<T> *lista{new MinhaListaEncadeada<T>};

    std::array<Esperado<T>, 5> const esperados{{{0, 0},
                                                {10, 1},
                                                {20, 2},
                                                {30, 3},
                                                {40, 4}}};

    for (Esperado<T> const &esperado : esperados)
        lista->inserirNoFim(esperado.dado);

    ASSERT_EQ(lista->tamanho(), size(esperados));
    ASSERT_TRUE(!lista->vazia());

    for (Esperado<T> const &esperado : esperados)
    {
        ASSERT_EQ(lista->posicao(esperado.dado), esperado.posicao);
        ASSERT_TRUE(lista->contem(esperado.dado));
    }

    delete lista;
}

TEST(TesteListaEncadeada, RemocaoDoInicio)
{
    using T = int;

    ListaEncadeadaAbstrata<T> *lista{nullptr};

    // Lista vazia
    {
        lista = new MinhaListaEncadeada<T>;
        ASSERT_THROW(lista->removerDoInicio(), ExcecaoListaEncadeadaVazia);
        delete lista;
    }

    // Todos os itens
    {
        lista = new MinhaListaEncadeada<T>;

        std::array<T, 5> const dados{0, 10, 20, 30, 40};

        for (T const dado : dados)
            lista->inserirNoFim(dado);

        constexpr std::size_t quantidadeRemover{2};

        for (std::size_t i{0}; i < quantidadeRemover; ++i)
        {
            ASSERT_EQ(lista->removerDoInicio(), dados[i]);
            ASSERT_EQ(lista->tamanho(), size(dados) - i - 1);
            ASSERT_TRUE(!lista->contem(dados[i]));
        }

        for (std::size_t i{quantidadeRemover}; i < size(dados); ++i)
            ASSERT_EQ(lista->posicao(dados[i]), i - quantidadeRemover);

        for (std::size_t i{quantidadeRemover}; i < size(dados); ++i)
            ASSERT_EQ(lista->removerDoInicio(), dados[i]);

        ASSERT_TRUE(lista->vazia());

        delete lista;
    }
}

TEST(TesteListaEncadeada, RemocaoDePosicao)
{
    using T = int;

    ListaEncadeadaAbstrata<T> *lista{new MinhaListaEncadeada<T>};

    std::array<T, 5> const dados{0, 10, 20, 30, 40};

    for (T const dado : dados)
        lista->inserirNoFim(dado);

    std::array<Esperado<T>, 3> const esperados{{
        {dados[0], 0}, // Do início.
        {dados[3], 2}, // Do meio.
        {dados[4], 2}  // Do fim.
    }};

    std::size_t tamanho{size(dados)};

    for (Esperado<T> const &esperado : esperados)
    {
        ASSERT_EQ(lista->removerDe(esperado.posicao), esperado.dado);
        --tamanho;

        ASSERT_EQ(lista->tamanho(), tamanho);
        ASSERT_TRUE(!lista->contem(esperado.dado));
    }

    for (std::size_t const posicao : {2, 3, 100})
        ASSERT_THROW(lista->removerDe(posicao), ExcecaoPosicaoInvalida);

    for (std::size_t i{0}; i < tamanho; ++i)
        [[maybe_unused]] T const dado{lista->removerDoInicio()};

    for (std::size_t const posicao : {0, 1})
        ASSERT_THROW(lista->removerDe(posicao), ExcecaoPosicaoInvalida);

    ASSERT_TRUE(lista->vazia());

    delete lista;
}

TEST(TesteListaEncadeada, RemocaoDoFim)
{
    using T = int;

    ListaEncadeadaAbstrata<T> *lista{nullptr};

    // Lista vazia
    {
        lista = new MinhaListaEncadeada<T>;
        ASSERT_THROW(lista->removerDoFim(), ExcecaoListaEncadeadaVazia);
        delete lista;
    }

    // Todos os itens
    {
        lista = new MinhaListaEncadeada<T>;

        std::array<T, 5> const dados{0, 10, 20, 30, 40};

        for (T const dado : dados)
            lista->inserirNoFim(dado);

        constexpr std::size_t quantidadeRemover{2};

        for (std::size_t i{0}; i < quantidadeRemover; ++i)
        {
            std::size_t const j{size(dados) - i - 1};

            ASSERT_EQ(lista->removerDoFim(), dados[j]);
            ASSERT_EQ(lista->tamanho(), j);
            ASSERT_TRUE(!lista->contem(dados[j]));
        }

        for (std::size_t i{quantidadeRemover}; i < size(dados); ++i)
            ASSERT_EQ(lista->removerDoFim(), dados[size(dados) - i - 1]);

        ASSERT_TRUE(lista->vazia());

        delete lista;
    }
}

TEST(TesteListaEncadeada, Remocao)
{
    using T = int;

    ListaEncadeadaAbstrata<T> *lista{new MinhaListaEncadeada<T>};

    ASSERT_THROW(lista->remover(0), ExcecaoListaEncadeadaVazia);

    for (T const dado : {0, 10, 20, 30, 40, 10})
        lista->inserirNoFim(dado);

    for (T const dado : {1, 11, 21, 31, 41})
        ASSERT_THROW(lista->remover(dado), ExcecaoDadoInexistente);

    std::size_t tamanho{lista->tamanho()};

    for (T const dado : {0, 40, 20, 30})
    {
        lista->remover(dado);
        --tamanho;

        ASSERT_TRUE(!lista->contem(dado));
        ASSERT_EQ(lista->tamanho(), tamanho);
    }

    T const repetido{10};

    lista->remover(repetido);
    --tamanho;

    ASSERT_TRUE(lista->contem(repetido));
    ASSERT_EQ(lista->tamanho(), tamanho);

    lista->remover(repetido);
    --tamanho;

    ASSERT_TRUE(!lista->contem(repetido));
    ASSERT_EQ(lista->tamanho(), tamanho);

    delete lista;
}

int main(int argc, char **argv)
{
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}