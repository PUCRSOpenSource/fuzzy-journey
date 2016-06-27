# fuzzy-journey

Grupo:
* [Daniel Amarante](https://github.com/amarantedaniel)
* [Giovanni Cupertino](https://github.com/GiovanniCuper)
* [Matthias Nunes](https://github.com/execb5)

#### Como compilar:

Apenas execute `make` no diretório raiz para compilar o projeto inteiro, `make
run` para compilar e já executar direto.

Para vizualização da *BTree*, é necessário ter o `graphviz` instalado junto com
o visualizador de imagens `feh`. Para trocar o visualizador é só substituir na
chamada de sistema no `src/table.cpp:207`, trocar `feh` pelo seu visualizador de
escolha.

#### Como utilizar:

Quando o simulador começa, ele já entra no **Sif** (shell desenvolvido para o
programa). Ele é um shell como qualquer outro, mas suas funções *built-in*
interagem com a nossa estrutura de banco.

***Built-ins***:

* `cd` - mudar de diretório

```sh
cd ~/fuzzy/journey
```

* `help` - comando de ajuda

```sh
help
```

* `exit` - sai do **Sif** shell

```sh
exit
```

* `print_tree` - imprime a *Btree* no terminal na vertical

```sh
print_tree
```

* `graph_print` - abre um *.png* que representa  *BTree*

```sh
graph_print
```

* `insert` - insere um registro na *BTree*

```sh
insert 1 Inseri_essa_descrição_na_chave_1
```

* `insertn` - insere *n* registros na *BTree* com descrições aleatórias

```sh
insertn 15
```

* `select` - seleciona um registro utilizando seu código

```sh
select 1 
```

* `selectd` - seleciona um registro utilizando sua descrição

```sh
selectd Inseri_essa_descrição_na_chave_1
```

* `update` - atualiza um registro

```sh
update 1 Agora_troquei_a_descrição_da_chave_1
```

* `arruda` - imprime a cara do professor **Arruda** no terminal

```sh
arruda
```


---

# Enunciado

## Simulador de B\*

### Objetivo

Construir um simulador de árvores B\*(B\*Tree), conforme algoritmo visto em aula e
definido em [KNUTH, 1998].

Todo o desenvolvimento, desde a análise e o projeto até a implementação, deverá
ser realizado empregando orientação a objetos.

Será tolerada a utilização de qualquer linguagem de programação baseada em
objetos (Java, C++, C#, etc.), recomendando fortemente que seja utilizado C++ ou
Java.

### Requisitos

1. **_Datafile_**
	1. Tamanho total de 32MB
	2. Deve ser alocado previamente, completando com fillers (zeros)
	3. Deve, obviamente, garantir a persistência dos dados entre as execuções do
		 simulador
2. **Tabela**
	1. O simulador deverá suportar somente uma tabela de dados com a seguinte
		 estrutura:
		1. Código (PK) = 4B
		2. Descrição = até 200 caracteres
	2. O código é único: inserção de registros com código duplicado sinaliza erro
3. **_Datablocks_**
	1. Tamanho = 2KB
	2. Total de 16.384 datablocks no datafile, endereçados de 0 a 16.383
		 (endereços seriam de 14 bits, mas podem ser arredondados para 2B)
4. **_Datablocks_ da tabela**
	1. Deverão possuir uma tabela de endereçamento dos registros em seu header
	2. Cada entrada da tabela de endereçamento deverá indicar:
		1. Posição inicial do registro: 2B
		2. Tamanho do registro: 2B
5. **_RowId_ dos registros de dados**
	1. RowId = [endereço do datablock] + [endereço do registro] = 2B + 2B = 4B
6. **B\*Tree**
	1. Sobre a tabela de dados deverá ser implementado um índice secundário B\*Tree
		 externa
	2. A chave de busca (k) da B\*Tree deve ser a coluna código de registro de
		 dados = 4B
	3. Conforme o algoritmo B\*Tree, a ocupação mínima de cada nó deverá ser de
		 2/3 (66%)
7. **_Buffer_**
	1. 256 _frames_ (1.024KB)
	2. Seleção de vítimas via algoritmo FIFO
	3. Operar com write-back cache: se o conteúdo do _datablock_ tiver sido
		 alterado, quando ele for escolhido como vítima pelo FIFO, seu conteúdo deve
		 ser salvo no _datafile_ (_flush_)
8. **Operações suportadas**
	1. insert(código, descrição)
	2. insert(n): insere n registros com valores aleatórios para código e
		 descrição
	3. select(código)
	4. select(descrição)
	5. update(chave, nova\_descrição)
	6. delete(chave)

### Entregáveis

Deverá ser entregue obrigatoriamente documentação digital composta por:

1. Documentação de análise e projeto em UML. Os diagramas a serem entregues são:
	 Diagrama de Classes (incluindo a representação de atributos e métodos) e
	 Diagramas de Seqüência.
2. Código fonte comentado.
3. Instruções detalhadas para instalação e teste.

### Critérios de avaliação

1. Modelagem: 0,5
	1. Diagrama de Classes
	2. Diagrama de Seqüência
2. Datafile: 0,5
3. Datablocks: 0,5
4. Buffer: 0,5
5. Operações:
	1. insert(código, descrição): 2,0
	2. insert(n): insere n registros com valores aleatórios para código e
		 descrição: 0,5
	3. select(código): 1,0
	4. select(descrição): 0,5
	5. update(chave, nova\_descrição): 0,5
	6. delete(chave): 2,0
6. Código fonte comentado: 0,5
7. Apresentação: 1,0
8. Interface **gráfica** que mostre a árvore: +1,0

### Observações

Todos os integrantes do grupo deverão apresentar o trabalho no laboratório em
data a ser definida pelo professor.

Em caso de plágio da web, de semestres anteriores ou de outra turma, cuja
comprovação será realizada pelo professor junto ao grupo, também será atribuída
nota ZERO!

### Referência

[KNUTH, 1998] Knuth, Donald (1998), Sorting and Searching, The Art of Computer
Programming, Volume 3 (Second ed.), Addison-Wesley, ISBN 0-201-89685-0. Section
6.2.4: Multiway Trees, pp. 481–491. Also, pp. 476–477 of section 6.2.3 (Balanced
Trees) discusses 2-3 trees.
