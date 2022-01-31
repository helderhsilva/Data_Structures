# Introdução à análise de complexidade de algoritmos

## Motivação
- É importante analisar o **comportamento** dos algoritmos para:
  - Entender com as entradas **alteram** o comportamento;
  -  **Comparar** algoritmos similares quanto ao comportamento

> Comportamento do Algoritmo = Complexidade do Algoritmo

## Complexidade de Algoritmos
- É a **qunatidade de recursos** que um algoritmo consome para resolver um determinado problema

> Tipos de recursos:
> - Complexidade temporal: pode ser relacionado ao processador; e
> - Complexidade de Espaço: relacionado a memória

## Comparando algoritmos

> Problema computável passa por diferentes algoritmos (x, y e z) e gera uma solução.
> O que gerar a solução com o menor tempo ou espaço será o mais eficiente.

- Como fazer essas comporações?

## 1. Avaliação empírica de complexidade
- Implementar com LP;
- Executar em SO/PC;
- Medir tempos; e
- Comparar tempos.

> Depende de hardware, do programador e das entradas limitadas

**Como analisar matematicamente a complexidade temporal de um algoritmo?**

## 2. Análise matemática de complexidade
- Abstrai hardware;
- Abstrai programador; e
- Extrapola entradas.

## Modelo Computacional Abstrato
- != tecnologias de CPU, != tempos para executar um algoritmo;
- Modelo Random Access Machine
  - 1 CPU de 1 core, memória ilimitada e sem hierarquia de cache;
  - Uma instrução simples (+, -, *, /, etc) é executada em **1passo**;
  - Um acesso a memória (ler, escrever) é executado em **1 passo**;
  - Loop ou subrotina é excutado em **n>0 passo(s)**.
    - Exemplo: ordenar um vator.

> - Pró: permite análises simples e não equivocadas;
> - Contras: pode contradizer a realidade das tecnologias atuais:
>   - Multiplicação leva mais **tempo** que soma para executar;
>   - Exponenciação pode ou não executar em **tempo** constante (ex.: 2^k);
>   - Cache afeta significativamente acesso na memória.

## Critérios para análise de complexidade
- **Tamanho** n>=0 da **entrada** do algoritmo
- Exemplo: **tamanho** n>-0 de um **vetor** v a ser ordenado por um algoritmo> v[1], v[2], v[3] ... v[n]. _tamanho n_
- **Quantidade** T(n) de **instruções** a executar como função do **tamanho** n da **entrada**. #instruções = T(n)
- O **estado** da **entrada** pode interferir em T(n).
- Qual caso priorizar no projeto de um sistema? (depende do contexto)

> - Intruções **sempre** executadas:
>   - Instruções **independentes** de condicionais;
>   - **Repetições conhecidas** a priori (for)
> 
> 1. n=5 (1)
> 2. f=1 (1)
> 3. para n=1, 2,...,n (2n)
> 4.    f=f*i (2)
> Portanto T(n)=4n+2

> - Instruções **nem sempre** executadas:
>   - Instruções **dependentes** de condicionais;
>   - **Repetições não conhecidas** a priori (if, else, while)

