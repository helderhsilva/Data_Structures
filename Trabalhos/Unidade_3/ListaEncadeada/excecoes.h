#ifndef DEC0006_LISTA_ENCADEADA_EXCECOES_H
#define DEC0006_LISTA_ENCADEADA_EXCECOES_H

#include <stdexcept>
// std::length_error
// std::logic_error
// std::out_of_range
// std::runtime_error
#include <string>
// std::string

/**
 * @brief Exceção lançada caso se obter a posição de um dado que não está
 * contido na lista encadeada.
 * 
 */
class ExcecaoDadoInexistente: public std::logic_error
{
public:
    ExcecaoDadoInexistente();
};

/**
 * @brief Exceção lançada caso se tente realizar operações em uma lista
 * encadeada que não pode estar vazia.
 * 
 */
class ExcecaoListaEncadeadaVazia: public std::length_error
{
public:
    ExcecaoListaEncadeadaVazia();
};

/**
 * @brief Exceção lançada por funções que ainda não foram implementadas e não
 * devem ser chamadas.
 * 
 */
class [[maybe_unused]] ExcecaoNaoImplementado: public std::runtime_error
{
public:
	/**
	 * @brief Constrói uma ExcecaoNaoImplementado.
	 * 
	 * @param nome O nome da função de onde a exceção está sendo lançada.
	 */
	explicit ExcecaoNaoImplementado(std::string const& nome);
};

/**
 * @brief Exceção lançada caso se tente acessar uma posição inválida em uma
 * lista encadeada.
 * 
 */
class ExcecaoPosicaoInvalida: public std::out_of_range
{
public:
    ExcecaoPosicaoInvalida();
};

ExcecaoDadoInexistente::ExcecaoDadoInexistente():
    std::logic_error{"esse dado nao se encontra na lista"}
{}

ExcecaoListaEncadeadaVazia::ExcecaoListaEncadeadaVazia():
    std::length_error{"a lista encadeada esta vazia"}
{}

ExcecaoNaoImplementado::ExcecaoNaoImplementado(std::string const& nome):
	std::runtime_error
	{
		std::string{"\""} + nome + "\" nao foi implementado ainda"
	}
{}

ExcecaoPosicaoInvalida::ExcecaoPosicaoInvalida():
    std::out_of_range{"posicao invalida na lista encadeada"}
{}

#endif