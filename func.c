#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

//--------------------------------------------------------------
// VARIAVEIS GLOBAIS:
//--------------------------------------------------------------
int comp_abp = 0; // comparacoes de abp
int comp_avl = 0; // comparacoes de avl
int height_abp = 0; // altura da abp
int height_avl = 0; // altura da avl
int n_nodos_abp = 0; // quantidade de nodos abp
int n_nodos_avl = 0; // quantidade de nodos avl
int rotations_abp = 0; // rotacoes abp
int rotations_avl = 0; // rotacoes avl

//--------------------------------------------------------------
// FUNCOES PARA AVL:
//--------------------------------------------------------------

// funcao para inicicalizar uma avl
NodeAVL* initializeTreeAVL(){
    return NULL;
}

// funcao para obter altura de um nodo de uma avl
int height(NodeAVL* n){
    return n ? n->height : 0; // se n for diferente de NULL, retorna a altura do nodo, senao retorna 0
}

// funcao para calcular o valor maximo entre dois inteiros
int max(int a, int b){
    return (a > b) ? a : b; // se a for maior que b, retorna a, senao retorna b
}

// funcao para ciar um novo nodo de uma avl
NodeAVL* createNodeAVL(char* word_key, char* word_sub){
    NodeAVL* newNode = (NodeAVL*)malloc(sizeof(NodeAVL)); // aloca memoria para o novo nodo

    strcpy(newNode->word_key, word_key); // copia a palavra chave para o novo nodo
    strcpy(newNode->word_sub, word_sub); // copia a palavra substituta para o novo nodo

    newNode->left = NULL; // inicializa o ponteiro para o nodo da esquerda como NULL
    newNode->right = NULL; // inicializa o ponteiro para o nodo da direita como NULL
    newNode->height = 1; // inicializa a altura do nodo como 1

    return newNode; // retorna o novo nodo
}

// funcao para realizar uma rotacao a direita em uma avl
NodeAVL* rightRotate(NodeAVL* y){
    NodeAVL* x = y->left; // define x como o nodo da esquerda de y
    NodeAVL* T2 = x->right; // define T2 como o nodo da direita de x

    x->right = y;  // faz a rotacao
    y->left = T2; // faz a rotacao

    y->height = max(height(y->left), height(y->right)) + 1; // atualiza a altura de y
    x->height = max(height(x->left), height(x->right)) + 1; // atualiza a altura de x

    return x; // retorna o nodo x
}

// funcao para realizar uma rotaacao a esquerda em uma avl
NodeAVL* leftRotate(NodeAVL* x){
    NodeAVL* y = x->right; // define y como o nodo da direita de x
    NodeAVL* T2 = y->left; // define T2 como o nodo da esquerda de y

    y->left = x; // faz a rotacao
    x->right = T2;  // faz a rotacao

    x->height = max(height(x->left), height(x->right)) + 1; // atualiza a altura de x
    y->height = max(height(y->left), height(y->right)) + 1; // atualiza a altura de y

    return y; // retorna o nodo y
}

// funcao para obter o fator de balanceamento de um no de uma avl
int getBalance(NodeAVL* n){
    return n ? height(n->left) - height(n->right) : 0; // se n for diferente de NULL, retorna a diferenca entre a altura da subarvore esquerda e a altura da subarvore direita, senao retorna 0
}

// funcao para inserir um novo no na arvore AVL de forma alfabetica
NodeAVL* insertNodeAVL(NodeAVL* node, char* word_key, char* word_sub){
    if (node == NULL)
        return createNodeAVL(word_key, word_sub); // se a árvore estiver vazia, retorna um novo no

    // insercao com base na ordem alfabetica da word_key
    if (strcmp(word_key, node->word_key) < 0)
        node->left = insertNodeAVL(node->left, word_key, word_sub);
    else if (strcmp(word_key, node->word_key) > 0)
        node->right = insertNodeAVL(node->right, word_key, word_sub);
    else
        return node; // chaves duplicadas nao sao permitidas

    // atualiza a altura deste no ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // verifica o fator de balanceamento para ver se o no ficou desbalanceado
    int balance = getBalance(node);

    // se o nó estiver desbalanceado, ha 4 casos a serem considerados:

    // caso 1: rotacao a direita
    if (balance > 1 && strcmp(word_key, node->left->word_key) < 0){
        rotations_avl++;
        return rightRotate(node);
    }

    // caso 2: rotacao a esquerda
    if (balance < -1 && strcmp(word_key, node->right->word_key) > 0){
        rotations_avl++;
        return leftRotate(node);
    }

    // caso 3: rotacao a esquerda-direita
    if (balance > 1 && strcmp(word_key, node->left->word_key) > 0) {
        rotations_avl++;
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // caso 4: rotacao a direita-esquerda
    if (balance < -1 && strcmp(word_key, node->right->word_key) < 0) {
        rotations_avl++;
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // retorna o ponteiro do no (inalterado)
    return node;
}

// funcao para buscar uma palavra na arvore AVL
char* searchAVL(NodeAVL* root, char* word){
    if (root == NULL) { // se a raiz for NULL
        comp_avl++; // incrementa o contador de comparacoes da avl
        return word; // Palavra não encontrada
    }

    int comparison = strcmp(word, root->word_key);
    if (comparison == 0) { // se a palavra for encontrada
        comp_avl++; // incrementa o contador de comparacoes da avl
        return root->word_sub; // Palavra encontrada
    } else if (comparison < 0) { // se a palavra for menor que a palavra da raiz
        comp_avl++; // incrementa o contador de comparacoes da avl
        return searchAVL(root->left, word); // busca na subarvore esquerda
    } else {
        comp_avl++; // incrementa o contador de comparacoes da avl
        return searchAVL(root->right, word); // busca na subarvore direita
    }
}

//--------------------------------------------------------------
// FUNCOES PARA ABP:
//--------------------------------------------------------------

// funcao para inicializar uma abp
Node* initializeTree(){
    return NULL;
}

// funcao para criar um novo no na arvore abp
Node* createNode(char* word_key, char* word_sub){
    Node* newNode = (Node*)malloc(sizeof(Node)); // aloca memoria para o novo no

    strcpy(newNode->word_key, word_key); // copia a palavra chave para o novo no
    strcpy(newNode->word_sub, word_sub); // copia a palavra substituta para o novo no

    newNode->left = NULL; // inicializa o ponteiro para o no da esquerda como NULL
    newNode->right = NULL; // inicializa o ponteiro para o no da direita como NULL

    return newNode; // retorna o novo no
}

// funcao para inserir um novo no na arvore abp
Node* insertNode(Node* root, char* word_key, char* word_sub){
    if (root == NULL) { // se a arvore estiver vazia
        return createNode(word_key, word_sub); // retorna um novo no
    }

    if (strcmp(word_key, root->word_key) < 0) { // se a palavra for menor que a palavra da raiz
        root->left = insertNode(root->left, word_key, word_sub); // insere na subarvore esquerda
    } else if (strcmp(word_key, root->word_key) > 0) { // se a palavra for maior que a palavra da raiz
        root->right = insertNode(root->right, word_key, word_sub); // insere na subarvore direita
    }

    return root; // retorna o ponteiro do no (inalterado)
}

// funcao para consultar uma palavra na arvore abp
char* searchTree(Node* root, char* word) {
    if (root == NULL) { // se a raiz for NULL 
        comp_abp++; // incrementa o contador de comparacoes da abp
        return word; // Palavra não encontrada
    }

    int comparison = strcmp(word, root->word_key); // compara a palavra com a palavra da raiz

    if (comparison == 0) { // se a palavra for encontrada
        comp_abp++; // incrementa o contador de comparacoes da abp
        return root->word_sub; // Palavra encontrada
    } else if (comparison < 0) { // se a palavra for menor que a palavra da raiz
        comp_abp++; // incrementa o contador de comparacoes da abp
        return searchTree(root->left, word); // busca na subarvore esquerda
    } else{ // se a palavra for maior que a palavra da raiz
        comp_abp++; // incrementa o contador de comparacoes da abp
        return searchTree(root->right, word); // busca na subarvore direita
    }
}

// funcao para liberar memoria alocada para a ABP
void freeTree(Node* root) {
    if (root != NULL) { // se a raiz for diferente de NULL
        freeTree(root->left); // libera a subarvore esquerda
        freeTree(root->right); // libera a subarvore direita
        free(root); // libera a raiz
    }
}

// funcao para liberar memoria alocada para a AVL
void freeTreeAVL(NodeAVL* root) {
    if (root != NULL) { // se a raiz for diferente de NULL
        freeTreeAVL(root->left); // libera a subarvore esquerda
        freeTreeAVL(root->right); // libera a subarvore direita
        free(root); //  libera a raiz
    }
}

// funcao para dividir uma string em duas partes, separadas por uma tabulacao
void splitStringOnTab(char *input, char *firstWord, char *secondWord) {
    // encontra o indice da tabulacao na string de entrada
    char *tabPosition = strchr(input, '\t');

    if (tabPosition != NULL) {
        // calcula o comprimento da primeira palavra
        int firstWordLength = tabPosition - input;

        // copia a primeira palavra para 'firstWord'
        strncpy(firstWord, input, firstWordLength);
        firstWord[firstWordLength] = '\0';  // finaliza a primeira string

        // copia a segunda palavra para 'secondWord'
        strcpy(secondWord, tabPosition + 1);  // +1 para pular a tabulacao
    } else {
        // se nao houver tabulacao, retorna a string inteira na primeira palavra
        strcpy(firstWord, input);
        secondWord[0] = '\0';  // deixa a segunda string vazia
    }
}

// funcao que calcula a altura de uma arvore ABP
int alturaArvore(Node *node){
    // se arvore esta vazia, altura = -1
    if (node == NULL) {
        return -1;
    }

    // recursivamente encontra a altura da subarvore esquerda e direita
    int leftHeight = alturaArvore(node->left);
    int rightHeight = alturaArvore(node->right);

    // retorna o maximo entra a altura da subarvore esquerda e direita + 1
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// funca para contar o numero de nos na arvore AVL
int countNodesAVL(NodeAVL* root) {
    if (root == NULL) { // se a raiz for NULL
        return 0; // retorna 0
    }
    return 1 + countNodesAVL(root->left) + countNodesAVL(root->right); // senao, retorna 1 + a quantidade de nodos na subarvore esquerda + a quantidade de nodos na subarvore direita
}

// funcao para contar o numero de nos na arvore ABP
int contaNodos(Node *a){
    if(a == NULL){ // se info atual for diferente de NULL
        return 0; // retorna 0
    } else{
        return 1 + contaNodos(a->left) + contaNodos(a->right); //retorna o valor da função + 1, a quantidade de nodos
    }
}

// funcao para imprimir a arvore AVL
void printTree(NodeAVL* root, int level) {
    if (root == NULL) {
        return;
    }

    // primeiro imprime o subarvore direita
    printTree(root->right, level + 1);

    // imprime o no atual com indentacao
    for (int i = 0; i < level; i++) {
        printf("    "); // 4 espacos para cada nivel
    }
    printf("%s: %s\n", root->word_key, root->word_sub);

    // depois imprime a subarvore esquerda
    printTree(root->left, level + 1);
}
