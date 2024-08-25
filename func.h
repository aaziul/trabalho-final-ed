#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_WORD_LENGTH 100 // tamanho maximo para as palavras

//----------------------------------------------
// ESTRUTURAS:
//----------------------------------------------

// estrutura do no da arvore AVL
typedef struct NodeAVL {
    char word_key[MAX_WORD_LENGTH];
    char word_sub[MAX_WORD_LENGTH];
    struct NodeAVL *left;
    struct NodeAVL *right;
    int height;
} NodeAVL;

// estrutura do no da arvore ABP
typedef struct Node {
    char word_key[MAX_WORD_LENGTH];
    char word_sub[MAX_WORD_LENGTH];
    struct Node* left;
    struct Node* right;
} Node;

//----------------------------------------------
// FUNCOES:
//----------------------------------------------

NodeAVL* initializeTreeAVL();
int height(NodeAVL *N);
int max(int a, int b);
NodeAVL* newNodeAVL(char* word_key,char* word_sub);
NodeAVL *rightRotate(NodeAVL *y);
NodeAVL *leftRotate(NodeAVL *x);
int getBalance(NodeAVL *N);
NodeAVL* insertNodeAVL(NodeAVL* node, char* word_key,char* word_sub);
char* searchAVL(NodeAVL* root, char* word);
void freeTreeAVL(NodeAVL* root);

Node* initializeTree();
Node* createNode(char* word_key,char* word_sub);
Node* insertNode(Node* root, char* word_key,char* word_sub);
char* searchTree(Node* root, char* word);
void freeTree(Node* root);

void splitStringOnTab(char *input, char *firstWord, char *secondWord);
void printInOrder(Node* root);

int alturaArvore(Node *a);
int countNodesAVL(NodeAVL* root);
int contaNodos(Node *a);

void printTree(NodeAVL* root, int level);
int strcasecmp(const char *s1, const char *s2);
