#include "MeuGrafo.h"
// MeuGrafo

#include <cstddef>
// std::size_t
#include <iterator>
// std::empty
// std::size
#include <queue>
// std::priority_queue
#include <vector>
// std::vector

#include <algorithm>
#include <limits.h>

#include "excecoes.h"
// ExcecaoMatrizAdjacenciaVazia
// ExcecaoMatrizAdjacenciaNaoQuadrada
// ExcecaoCustoNegativo
// ExcecaoVerticeComLaco
// ExcecaoVerticeInvalido


MeuGrafo::MeuGrafo(MatrizAdjacencia const& matrizAdjacencia) : GrafoAbstrato(matrizAdjacencia)
{
  // Verificação de matriz vazia
  if (this->_matrizAdjacencia.size() <= 0)
  {
    throw ExcecaoMatrizAdjacenciaVazia();
  }
  else
  {
    // Verificação de matriz não quadrada
    for (size_t i = 0; i < this->_matrizAdjacencia.size(); i++)
    {
      if (this->_matrizAdjacencia.size() != this->_matrizAdjacencia[i].size())
      {
        throw ExcecaoMatrizAdjacenciaNaoQuadrada();
      }

      // Verificação de matriz com custo negativo ou vétice com laço
      for (size_t j = 0; j < this->_matrizAdjacencia[i].size(); j++)
      {
        if (this->_matrizAdjacencia[i][j] < 0)
        {
          throw ExcecaoCustoNegativo();
        }
        if (i == j && this->_matrizAdjacencia[i][j] != inf && this->_matrizAdjacencia[i][j] > 0)
        {
          throw ExcecaoVerticeComLaco();
        }
      }
    }
  }
};

std::size_t MeuGrafo::quantidadeVertices() const
{
  // Retorna o número de vétices da matriz NxN
  return this->_matrizAdjacencia.size();
};

std::size_t MeuGrafo::quantidadeArestas(std::size_t vertice) const
{
  //Verificação da não existência de vétice
  if (vertice > this->quantidadeVertices() - 1)
  {
    throw ExcecaoVerticeInvalido();
  }

  // Contagem do número de arestas de um vétice
  size_t nArestas = 0;

  for (size_t i = 0; i < this->_matrizAdjacencia[vertice].size(); i++)
  {
    if (this->_matrizAdjacencia[vertice][i] != inf)
    {
      nArestas++;
    }
  }
  return nArestas;
};

std::size_t MeuGrafo::quantidadeArestas() const
{
  size_t totalArestas = 0;
  size_t i = 0;

  // Pega o total de arestas na matriz NxN
  while (i < this->quantidadeVertices())
  {
    totalArestas += this->quantidadeArestas(i);
    i++;
  }
  return totalArestas;
};

double MeuGrafo::custo(std::size_t origem, std::size_t destino) const
{
  // Verificação se a origem e destino estão dentro dos vértices da matriz
  if (origem > this->quantidadeVertices() - 1 || destino > this->quantidadeVertices() - 1)
  {
    throw ExcecaoVerticeInvalido();
  }

  // Pega o custo da origem ao destino
  return this->_matrizAdjacencia[origem][destino];
};

double relaxamento(std::vector<double> dijkstra, std::vector<bool> aberto)
{
  int distancia = INT_MAX / 2;
  double indiceRelaxado;

  for (size_t i = 0; i < dijkstra.size(); i++)
  {
    if (aberto[i] == true && dijkstra[i] <= distancia)
    {
      distancia = dijkstra[i];
      indiceRelaxado = i;
    }
  }
  return indiceRelaxado;
};

std::vector<double> MeuGrafo::menoresDistancias(std::size_t origem) const
{
  // Verificação se a origem está dentro dos vértices da matriz
  if (origem > this->quantidadeVertices() - 1)
  {
    throw ExcecaoVerticeInvalido();
  }

  std::vector<double> dijkstra = {};
  dijkstra.resize(this->quantidadeVertices());

  std::vector<bool> aberto = {};
  aberto.resize(this->quantidadeVertices());

  for (size_t i = 0; i < this->quantidadeVertices(); i++)
  {
    dijkstra[i] = inf;
    aberto[i] = true;
  }

  dijkstra[origem] = 0;

  for (size_t index = 0; index <this->quantidadeVertices(); index++)
  {
    int distanciaRelaxada = relaxamento(dijkstra, aberto);
    aberto[distanciaRelaxada] = false;

    for (size_t k = 0; k < this->quantidadeVertices(); k++)
    {
      if (aberto[k])
      {
        if (dijkstra[distanciaRelaxada] != inf)
        {
          if (dijkstra[distanciaRelaxada] + this->_matrizAdjacencia[distanciaRelaxada][k] < dijkstra[k])
          {
            dijkstra[k] = dijkstra[distanciaRelaxada] + this->_matrizAdjacencia[distanciaRelaxada][k];
          }
        }
      }
    }
  }
  return dijkstra;
};