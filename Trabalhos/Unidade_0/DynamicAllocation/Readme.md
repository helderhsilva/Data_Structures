# Alocação Dinâmica

## Definição

- Sempre que escrevemos um programa, é preciso reservar espaço para as informações que serão processadas.
- Para isso utilizamos as variáveis.
  - Uma variável é uma posição de memória que armazena uma informação que pode ser modificada pelo programa.
  - Ela deve ser definida antes de ser usada.

- Variáveis usadas até agora são de dois tipos
  - Estáticas:
    - criadas quando o programa é executado;
    - destruídas quando o programa termina.
  - Automáticas:
    - criadas quando um bloco ou função é executado;
    - destruídas quando o bloco ou função termina.

- Nem sempre é possível **saber antes de executar um programa** o tamanho ou quantidade de variáveis necessárias.
- Exemplo:
  - Faça um programa para cadastrar o preço de **N** produtos, em que **N** é um valor informado pelo usuário.

~~~c++
int N, i;
double produtos[N]; //Errado! Não sabemos o valor de N

int N, i;

scanf("%d", &N);    //Funciona, mas não é o mais indicado

double produtos[N];
~~~

- A _alocação dinâmica_ permite ao programador criar "variáveis" em tempo de execução, ou seja, alocar memória para novas variáveis quando o programa está sendo executado, e n~~ao apenas quando se está escrevendo o programa
  - Quantidade de memória é alocada sob demanda, ou seja, quando o programa precisa.
  - Menos desperdício de memória.
    - Espaço é reservado até liberação explícita;
    - Depois de liberado, estará disponibilizado para outros usos e não pode mais ser acessado;
    - Espaço alocado e não liberado explicitamente é automaticamente liberado ao final da execução.

## Alocação Dinâmica:

- A linguagem C ANSI usa apenas 4 funções para o sistema de alocação dinâmica, disponíveis na stdlib.h:
  - malloc
  - calloc
  - realloc
  - free

- Lembre-se da **diretiva #include <stdlib.h>**

## Alocação Dinâmica - Malloc

- **malloc**:
  - A função malloc() serve para alocar memória e tem o seguinte protótipo:

~~~c++
void *malloc (unsigned int num);
~~~

- Funcionalidade:
  - Dado o número de bytes que queremos alocar (**num**), ela aloca na memória e retorna um ponteiro **void** para o primeiro byte alocado.
  - A memória alocada vem preenchida com **qualquer valor**

- O ponteiro **void*** pode ser atribuído a qualquer tipo de ponteiro via _type cast_. Se não houver memória suficiente para aloca a memória requisitada a função malloc() retorna um ponteiro nulo.

- Alocar 1000 bytes de memória para caracteres.

~~~c++
char *p;
p = (char *) malloc(1000);
~~~

- Alocar espaço para 50 inteiros:

~~~c++
int *p;
p = (int *) malloc(50*sizeof(int));
~~~

- Operador **sizeof()**
  - Retorna o número de **bytes** de um dado tipo de dado.
  - Ex.: int, float, char, struct...

~~~c++
struct ponto{
  int x, y;
};

int main() {

  printf("char: %d\n", sizeof(char)); // 1
  printf("int: %d\n", sizeof(int)); // 4
  printf("float: %d\n", sizeof(float)); // 4
  printf("ponto: %d\n", sizeof(struct ponto)); // 8

  return 0;
}
~~~

- No exemplo anterior:

~~~c++
int *p;
p = (int *) malloc(50*sizeof(int));
~~~

- **sizeof(int)** retorna 4 bytes;
- Portanto, são alocados 50*4 = 200 bytes;
- 200 bytes = 50 posições do tipo **int** na memória.

---

- Se não houver memória suficiente para alocar a memória requisitada, a função **malloc() retorna um ponteiro nulo:

~~~c++
int main() {
  int *p;
  p = (int *) malloc(5*sizeof(int));
  if (p == NULL) {
    printf("Erro: Memoria Insuficiente! \n");
    system("pause");
    exit(1);
  }
  int i;
  for (i=0; i<5; i++) {
    printf("Digite o valor da posição %d: ", i);
    scanf("%d", &p[i]);
  }

  return 0;
}
~~~

## Alocação Dinâmica - Calloc

- **calloc**
 - A função calloc() também serve para alocar memória;
 - A memória alocada vem preenchida com **zeros**.

 ~~~c++
void *calloc (unsigned int num, unsigned int size);
 ~~~

 - Exemplo da função **calloc**:

 ~~~c++
int main() {
  //alocação com malloc
  int *p;
  p = (int *) malloc(50*sizeof(int));
  if (p == NULL) {
    printf("Erro: Memoria Insuficiente! \n");
  }
  //alocação com calloc
   int *p1;
  p1 = (int *) calloc(50,sizeof(int));
  if (p1 == NULL) {
    printf("Erro: Memoria Insuficiente! \n");
  }

  return 0;
}
~~~

## Alocação Dinâmica - Realloc

- **realloc**
  - A função realloc() serve para realocar memória e tem o seguinte protótipo:

~~~c++
void *realloc (void *ptr, unsigned int num);
 ~~~

 - Funcionalidade:
  - A função modifica o tamanho da memória previamente alocada e apontada por ***ptr** para aquele especificado por **num**.
  - O valor de **num** pode ser maior ou menor que o original.
  - Um ponteiro para o bloco é devolvido porque realloc() pode precisar mover o bloco para aumentar seu tamanho.
  - Se isso ocorrer, o conteúdo do bloco antigo é copiado para o novo bloco, e nenhuma informação é perdida.

~~~c++
int main() {
  int i;
  int *p = malloc(5*sizeof(int));
  for (i = 0; i < 5; i++) {
    p[i] = i+1;
  }
  for (i = 0; i < 5; i++) {
    printf("%d \n", p[i]);
  }
  printf("\n");
  //Diminui o tamanho do array
  p = realloc(p,3*sizeof(int));
  for (i = 0; i < 3; i++) {
    printf("%d \n", p[i]);
  }
  printf("\n");
  //Aumenta o tamanho do array
  p = realloc(p,10*sizeof(int));
  for (i = 0; i < 10; i++) {
    printf("%d \n", p[i]);
  }

  return 0;
}
~~~

- Observações sobre realloc()
  - Se ***ptr** for nulo, aloca **num** bytes e devolve um ponteiro (igual malloc);
  - Se **num** é zero, a memória apontada por ***ptr** é liberada (igual free).
  - Se não houver memória suficiente para a alocação, um ponteiro nulo é devolvido e o bloco original é deixado inalterado.

~~~c++
void *realloc (void *ptr, unsigned int num);
~~~

## Alocação Dinâmica - Free

- **free**
  - Diferente das variáveis definidas durante a escrita do programa, as variáveis alocadas dinamicamente não são liberadas automaticamente pelo programa.
  - Quando alocamos memória dinamicamente é necessário que nós a liberemos quando ela não for mais necessária.
  - Para isto existe a função free() cujo protótipo é:

~~~c++
void free(void *p);
~~~

- Assim, para liberar a memória, basta passar como parâmetro para a função free() o ponteiro que aponta para o início da memória a ser desalocada.
- Como o programa sabe quantos bytes deve ser liberados?
  - Quando se aloca a memória, o programa guarda o número de bytes alocados numa "tabela de alocação" interna.

- Exemplo da função free():

~~~c++
int main() {
  int *p, i;
  p = (int *) malloc(50*sizeof(int));
  if (p == NULL) {
    printf("Erro: Memoria Insuficiente! \n");
    system("pause");
    exit(1);
  }
  for (i = 0; i < 50; i++) {
    p[i] = i+1;
  }
  for (i = 0; i < 50; i++) {
    printf("%d \n", p[i]);
  }
  //Libera a memória alocada
  free(p);

  return 0;
}
~~~

## Vazamento de Memória

- Alocação dinâmica != variáveis automáticas
  - Desalocação não ocorre quando termina contexto
- Dificuldade de rastrear toda memória alocada em programas complexos.
- É comum de esquecer de liberar memória (memory leak)

## Custo Computacional

- malloc, calloc, realloc e free são chamadas de sistema (requer intervenção do sistema operacional)
- Custo computacional inerente
- Usar alocação dinâmica somente quando necessário.

## Alocação de Arrays

- Para armazenar um array o compilador C calcula o tamanho, em bytes, necessário e reserva posições sequênciais na memória.
  - Note que isso é muito parecido com alocação dinâmica
- Existe uma ligação muito forte entre ponteiros e arrays.
  - O nome do array é apenas um ponteiro que aponta para o primeiro elemento do array.
- Ao alocarmos memória estamos, na verdade, alocando um array.

~~~c++
int *p;
int i, N = 100;

p = (int *) malloc(N*sizeof(int));

for (i = 0; i < N; i++) {
  scanf("%d", &p[i]);
}

free();
~~~

- Note, no entanto, que o array alocado possui apenas uma dimensão.
- Para liberá-lo da memória, basta chmar a função free() ao final do programa.

---

- Para alocarmos arrays com mais de uma dimensão, utilizamos o conceito de "ponteiro para ponteiro".
  - Ex.: 
  
~~~c++
char ***p3; //array de 3 dimensões com chars
~~~

- Para cada nível do ponteiro, fazemos a alocação de uma dimensão do array.
- Em um ponteiro para ponteiro, cada nível do ponteiro permite criar uma nova dimensão no array.

~~~c++
int **p; //2 "*" = 2 níveis = 2 dimensões
int i, j, N = 2;

p = (int **) malloc(N*sizeof(int*));

for (i = 0; i < N; i++) {
  p[i] = (int *) malloc(N*sizeof(int));
  for (j = 0; j < N; j++) {
    scanf("%d", &p[i][j]);
}

//Desalocação
for (i = 0; i < N; i++) {
  free(p[i]);
}
free(p);
~~~

- A primeira alocação e para as linhas e para cada linha é alocado uma coluna.

- Diferente dos arrays de uma dimensão, para liberar um array com mais de uma dimensão da memória, é preciso liberar a memória alocada em cada uma de suas dimensões, na ordem inversa da que foi alocada.
  - Isso é feito porque se começarmos desalocando pelas linhas nós perderemos o acesso para os arrays, ou seja perdemos as referencias para as memórias.

## Alocação de Struct

- Assim como os tipos básicos, também é possível fazer a alocação dinâmica de estruturas.
- As regras são exatamente as mesmas para a alocação de uma **struct**.
- Podemos fazer a alocação de:
  - uma única **struct**
  - um array de **structs**

---

-  Para alocar uma única **struct**:
  - Um ponteiro para **struct** receberá o **malloc()**.
  - Utilizamos o **operador seta** para acessar o conteúdo.
  - Usamos **free()** para liberar a memória alocada

~~~c++
struct cadastro {
  char nome[50];
  int idade;
};

int main() {
  struct cadastro *cad = (struct cadastro*) malloc (sizeof(struct cadastro));
  strcpy(cad->nome, "Maria");
  cad->idade = 30;

  free(cad);

  return 0;
}
~~~

- Pode-se ainda ter um vetor de structs:
  - Utilizamos os **colchetes []** para acessar o contúdo.
  - Ao invés da seta "->", é utilizado o ".", pois quando usa o colchete e o índice não estamos pegando o endereço do elemento, mas sim estamos pegando o elemento diretamente.

~~~c++
struct cadastro {
  char nome[50];
  int idade;
};

int main() {
  struct cadastro *vcad = (struct cadastro*) malloc (10*sizeof(struct cadastro));

  strcpy(vcad[0].nome, "Maria");
  vcad[0].idade = 30;

  strcpy(vcad[1].nome, "Cecilia");
  vcad[1].idade = 10;

  strcpy(vcad[2].nome, "Ana");
  vcad[2].idade = 20;

  free(vcad);

  return 0;
}
~~~