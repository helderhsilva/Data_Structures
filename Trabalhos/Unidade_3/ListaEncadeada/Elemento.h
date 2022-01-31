#ifndef DEC0006_LISTA_ENCADEADA_ELEMENTO_H
#define DEC0006_LISTA_ENCADEADA_ELEMENTO_H

/**
 * @brief Representa um elemento de uma lista encadeada.
 * 
 * @tparam T O tipo de dado armazenado no elemento.
 */
template<typename T>
struct Elemento
{
    /**
     * @brief O dado armazenado no elemento.
     * 
     */
    T dado;
    /**
     * @brief O ponteiro para o próximo elemento na lista. Pode ser nulo.
     * 
     */
    Elemento* proximo;

    /**
     * @brief Constrói um novo elemento.
     * 
     * @param dado O dado que será armazenado no elemento.
     * @param proximo O ponteiro para o próximo elemento. Por padrão, é nulo.
     */
    explicit Elemento(T dado, Elemento* proximo = nullptr);
};

template<typename T>
Elemento<T>::Elemento(T const dado, Elemento* const proximo):
    dado{dado}, proximo{proximo}
{}

#endif