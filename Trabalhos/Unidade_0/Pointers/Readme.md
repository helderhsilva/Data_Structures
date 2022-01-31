# Ponteiros

## Definições

### Variável:

- É um espaço reservado de memória usado para guardar um **valor** que poder ser modificado pelo programa;

### Ponteiro:

- É um espaço reservado de memória usado para guardar o **endereço de memória** de outra variável.
- Um ponteiro é uma variável como qualquer outra do programa - sua diferença é que ela não armazena um valor inteiro, real, caractere ou booleano.
- Ela serve para armazenar endereços de memória (são valores inteiros sem sinal).

<br>

## Declaração

- Como qualquer variável, um ponteiro também possui um tipo.

```c++
//declaração de variável
tipo_variável nome_variável;

//declaração de ponteiro
tipo_ponteiro *nome_ponteiro;
```

- É o asterisco (\*) que informa ao compilador que aquela variável não vai guardar um valor mas sim um endereço para o tipo especificado.

```c++
int x;
float y;
struct ponto p;

int *x;
float *y;
struct ponto *p;
```

- Exemplos de declarações de variáveis e ponteiros:

```c++
int main() {
  //Declara um ponteiro para int
  int *p;
  //Declara um ponteiro para float
  float *x;
  //Declara um ponteiro para char
  char *y;
  //Declara um ponteiro para struct ponto
  struct ponto *p;
  //Declara uma variável do tipo int e um ponteiro para int
  int soma, *p2;

  return 0;
}
```

- Na linguagem C, quando declaramos um ponteiro nós informamos ao compilador para que tipo de variável vamos apntá-lo.
  - Um ponteiro int\* aponta para um inteiro, isto é, **int**;
  - Esse ponteiro guarda o endereço de memória onde se encontra armazenada uma variável do tipo **int**.

<br>

## Inicialização

- Ponteiros apontam para uma posição de memória.

  - **Cuidado:** Ponteiros não inicializados apontam para um lugar indefinido.

- Um ponteiro pode ter o valor especial NULL que é o endereço de nenhum lugar.

```c++
int *p = NULL;
```

- Os ponteiros devem ser inicializados antes de serem usados;
- Assim, devemos apontar um ponteiro para um lugar conhecido.

  - Podemos apontá-lo para uma variável que já exista no programa.

- O ponteiro armazena o endereço da variável para ele aponta.
  - Para saber o endereço de memória de uma variável do nosso programa, usamos o operador **&**.

```c++
int main() {
  //Declara uma variável int contendo o valor 10
  int c = 10;
  //Declara um ponteiro para int
  int *p;
  //Atribui ao ponteiro o endereço da variável int
  p = &c;

  return 0;
}
```

<br>

## Utilização

- Tendo um ponteiro armazenado um endereço de memória, como saber o valor guardado dentro dessa posição?

- Para acessar o **valor** guardado dentro de uma posição na memória apontada por um ponteiro, basta usar o operador **asterisco "&"** na frente do nome do ponteiro.

```c++
int main() {
  //Declara uma variável int contendo o valor 10
  int c = 10;

  //Declara um ponteiro para int
  int *p;

  //Atribui ao ponteiro o endereço da variável int
  p = &c;
  printf("Conteudo apontado por p: %d \n", *p); //10

  //Atribui um novo valor à posição de memória apontada por p
  *p = 12;
  printf("Conteudo apontado por p: %d \n", *p); //12
  printf("Conteudo de count: %d \n", c); //12

  return 0;
}
```

- **\*p:** conteúdo da posição de memória apontado por **p**;
- **&c:** o endereço na memória onde está armazenada a variável **c**.

- De modo geral, um ponteiro só pode receber o endereço de memória de uma variável do mesmo tipo do ponteiro.
  - Isso ocorre porque diferentes tipos de variáveis ocupam espaçõs de memória de tamanhos diferentes;
  - Na verdade, nós podemos atribuir a um ponteiro de inteiro (**int\***) o endereço de uma variável do tipo **float.** No entanto, o compilador assume que qualquer endereço que esse ponteiro armazene obrigatoriamente apontará para uma variável do tipo **int**;
  - Isso gera problemas na interpretação dos valores.

```c++
int main() {
  int *p, *p1, x =10;
  float y = 20.0;

  p = &x;
  printf("Conteudo apontado por p: %d \n", *p);

  p1 = p;
  printf("Conteudo apontado por p1: %d \n", *p1);

  p = &y;
  printf("Conteudo apontado por p: %d \n", *p);
  printf("Conteudo apontado por p: %f \n", *p);
  printf("Conteudo apontado por p: %f \n", *((float*)p));

  return 0;
}

//Obs: nem roda no VSCode isso...
```

<br>

## Operações com ponteiros

### Atribuição:

- p1 aponta para o mesmo lugar que p;

```c++
int *p, *p1;
int c = 10;

p = &c;

p1 = p; //Equivale a p1 = &c;
```

- a variável apontada por p1 recebe o mesmo conteúdo da variável apontada por p;

```c++
int *p, *p1;
int c = 10, d = 20;

p = &c;
p1 = &d;

*p1 = *p; //Equivale a d = c;
```

- Apenas duas operações aritiméticas podem ser utilizadas com no endereço armazenado pelo ponteiro: adição e subtração;
- Podemos apenas somar e subtrair valores INTEIROS:

  - p++;
    - soma +1 no endereço armazenado no ponteiro.
  - p--;
    - subtrai 1 no endereço armazenado no ponteiro.
      p = p+15;
    - soma +15 no endereço armazenado no ponteiro.

- As operações de adição e subtração no endereço dependem do tipo de dado que o ponteiro aponta.
  - Considere um ponteiro para inteiro, int\*.
  - O tipo int ocupa um espaço de 4 bytes na memória.
  - Assim, nas operações de adição e subtração são adicionados/subtraídos 4 bytes por incremento/decremente, pois esse é o tamanho de um inteiro na memória e, portantom é também o valor mínimo necessário para sair dessa posição reservada de memória.

### Operações Ilegais com ponteiros:

- Dividir ou multiplicar ponteiros;
- Somar o endereço de dois ponteiros;
- Não se pode adcionar ou subtrair valores dos tipos **float** ou **double** a ponteiros (ex: p = p + 1.5).

### Já sobre seu conteúdo apontado, valem todas as operações:

- \*p++:

  - incrementar o conteúdo da variável apontada pelo ponteiro p;

- *p = (*p) \* 10;
  - multiplica o conteúdo da variável apontada pelo ponteiro p por 10;

```c++
int *p;
int c = 10;

p = &c;

(*p)++;
*p = (*p) * 10;
```

### Operações relacionais

- == e != para saber se dois ponteiros são iguais ou diferentes.
- <, >, >= e <= para saber qual ponteiro aponta para uma posição mais alta na memoria.

```c++
int main() {
  int *p, *p1, x, y;
  p = &x;
  p1 = &y;

  if (p == p1) {
    printf("Ponteiros iguais \n");
  } else {
    printf("Ponteiros diferentes \n");
  }

  return 0;
}
```

<br>

## Ponteiro Genérico

- Normalmente, um ponteiro aponta para um tipo específico de dado.

  - Um ponteiro genérico é um ponteiro que pode apontar para qualquer tipo de dado.

- Declaração:

```c++
void *nome_ponteiro;
```

- Ponteiros void não suportam aritmética de ponteiros.

- Exemplos:

```c++
int main() {
  void *pp;
  int *p1, p2 = 10;

  p1 = &p2;

  //Recebe o endereço de um inteiro
  pp = &p2;
  printf("Endereco em pp: %p \n", pp);

  //Recebe o endereço de um ponteiro para inteiro
  pp = &p1
  printf("Endereco em pp: %p \n", pp);

  //Recebe o endereço guardado em p1 (endereço de p2)
  pp = p1;
  printf("Endereco em pp: %p \n", pp);

  return 0;
}
```

- Para acessar o **conteúdo** de um ponteiro genérico é preciso antes convertê-lo para o tipo de ponteiro com o qual se deseja trabalhar.
  - Isso é feito via **type cast**.

~~~c++
int main() {
  void *pp;
  int p2 = 10;
  //Ponteiro genérico recebe o endereço de um inteiro
  pp = &p2;
  //Tenta acessar o conteúdo do ponteiro genérico
  printf("Conteudo: %d \n", *pp); //ERRO
  //Converte o ponteiro genérico pp para (int*) antes de acessar seu conteúdo.
  printf("Conteudo: %d \n", *(int*)pp)); //CORRETO

  return 0;
}
~~~

<br>

## Ponteiros e Arrays

- Ponteiros e arrays possuem uma ligação muito forte.

  - Arays são agrupamentos de dados do mesmo tipo na memória;
  - Quando declaramos um array, informamos ao computador para reservar uma certa quantidade de memória a fim de armazenar os elementos array de forma contígua;
  - Como resultado dessa operação, o computador nos devolve um ponteiro que aponta para o começo dessa sequência de bytes na memória.

- O nome do array (sem índice) é apenas um ponteiro que aponta para o primeiro elemento array.

~~~c++
int vet[5] = {1,2,3,4,5};
int *p;

p = vet;
~~~

- Os colchetes **[]** substituem o uso conjunto de operações aritméticas e de acesso ao contúdo (operador "*") no acesso ao conteúdo de uma posição de um array ou ponteiro.
  - O valor entre colchetes é o deslocamento a partir da posição inicial do array.
  - Nesse caso, **p[2]** equivale a ***(p+2)**.

~~~c++
int main () {
  int vet[5] = {1,2,3,4,5};
  int *p;

  p = vet;

  printf("Terceiro elemento: %d ou %d", p[2], *(p+2));

  return 0;
}
~~~

- Temos então:
  - ***p** é equivalente a **vet[0]**;
  - **vet[indice]** é equivalente a ***(p+índice)**;
  - **vet** é equivalente a **&vet[0]**;
  - **&vet[índice]** é equivalente a **(vet + índice)**;

- Exemplo usando array:

~~~c++
int main () {
  int vet[5] = {1,2,3,4,5};
  int *p = vet;
  int i;

  for (i = 0; i < 5; i++) {
    printf ("%d \n", p[i]);
  }

  return 0;
}
~~~

- Exemplo usando ponteiro:

~~~c++
int main () {
  int vet[5] = {1,2,3,4,5};
  int *p = vet;
  int i;

  for (i = 0; i < 5; i++) {
    printf ("%d \n", *(p+i));
  }

  return 0;
}
~~~

### Arrays Multidimensionais:
- Apesar de terem mais de uma dimensão, na memória os dados são armazenados linearmente.

- Ex.: int mat[5][5]; (matriz quadrada 5x5 de inteiros)

- Pode-se então percorrer as várias dimensões do array como se existisse apenas uma dimensão. As dimensões mais a direita mudam mais rápido

- Exemplo usando array:

~~~c++
int main () {
  int mat[2][2] = {(1,2),(3,4)};
  int i, j;

  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2, j++) {
      printf ("%d \n", mat[i][j]);
    }
  }

  return 0;
}
~~~

- Exemplo usando ponteiro:

~~~c++
int main () {
  int mat[2][2] = {(1,2),(3,4)};
  int *p = &mat[0][0];
  int i;

  for (i = 0; i < 4; i++) {
    printf ("%d \n", *(p+i)));
  }

  return 0;
}
~~~

<br>

## Ponteiros para Struct
- Existem duas abordagens para acessar o conteúdo de um ponteiro para uma struct.

- Abordagem 1: Devemos acessar o conteúdo do ponteiro para struct para somente depois acessar os seus campos e modificá-los.

- Abordagem 2: Podemos usar o **operador seta "->"**
- **ponteiro->nome_campo**

~~~c++
struct ponto {
  int x, y;
};

struct ponto q;
struct ponto *p;

p = &q;

(*p).x = 10;
p->y = 20;
~~~

<br>

## Ponteiro para ponteiro
- A linguagem C permite criar ponteiros com diferentes níveis de apontamento.
  - É possível criar um ponteiro que aponte para outro ponteiro, criando assim vários níveis de apontamento.
  - Assim, um ponteiro poderá apontar para outro ponteiro, que, por sua vez, aponta para outro ponteiro, que aponta para um terceeiro ponteiro e assim por diante.

- Um ponteiro para um ponteiro é como se você anotasse o endereço de um papel que tem o endereço da casa do seu amigo.

- Podemos declarar um ponteiro para um ponteiro com a sequinte notação
  - **tipo_ponteiro **nome_ponteiro**;

- Acesso ao conteúdo:
  - ****nome_ponteiro** é o conteúdo final da variável apontada;
  - ***nome_ponteiro** é o conteúdo do ponteiro intermediário.

~~~c++
int c = 10;
int *p1 = &x;
int **p2 = &p1;

//Endereço em p2
printf("Endereco em p2: %p \n", p2);

//Conteúdo no endereço
printf("Conteudo em *p2: %p \n", *p2);

//Conteúdo do endereço do endereço
printf("Endereco em **p2: %p \n", **p2);
~~~

- É a quantidade de asteriscos (*) na declaração do ponteiroque indica o número de níveis de apontamento que ele possui.

~~~c++
//Variável inteira
int x;

//Ponteiro para um inteiro (1 nível)
int *p1;

//Ponteiro para ponteiro de inteiro (2 níveis)
int **p2;

//Ponteiro para ponteiro para ponteiro de inteiro (3 níveis)
int ***p3;
~~~

- conceito de "ponteiro para ponteiro":

~~~c++
char letra = 'a';
char *p1;
char **p2;
char ***p3;

p1 = &letra;
p2 = &p1;
p3 = &p2;
~~~

<br>

## Ponteiro de ponteiro & Arrays Mult

~~~c++
 char** mat = (char**) calloc(2, sizeof(char*));
 for (int i = 0; i < 2; i++) {
   *(mat+i) = (char*) calloc(2, sizeof(char));


   mat[0][0] = *(*(mat+0)+0)
 }
~~~

