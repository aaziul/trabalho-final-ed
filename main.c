#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "data.h"


/* OBJETIVO: O programa le um arquivo texto como entrada e gera um arquivo como saida com o conteudo do arquivo de entrada convertido para letras minusculas
Instrucoes: Para chamar, digite "exemplo entrada.txt saida.txt" */

// variaveis globais para armazenar as estatisticas
extern int comp_abp;
extern int comp_avl;
extern int height_abp;
extern int height_avl;
extern int n_nodos_abp;
extern int n_nodos_avl;
extern int rotations_abp;
extern int rotations_avl;


int main(int argc, char *argv[]) //argc conta o numero de parametros e argv armazena as strings correspondentes aos paramentros digitados
{
    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados

    FILE * dict; //arquivo dicionario
    FILE * entrada; //arquivo de entrada
    FILE * saida; //arquivo de saida
    FILE * stats; //arquivo de estatisticas

    char *palavra, linha[1000], linha_dict[1000], word_key[1000], word_sub[1000]; // linhas a serem lidas do arquivo
    char separador[] = {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"}; //caracteres que serao considerados como separadores de palavras

    Node* rootABP = initializeTree(); // inicializa abp
    NodeAVL* rootAVL = initializeTreeAVL(); // inicializa avl

    if (argc!=4){  //o numero de parametros esperado eh 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
        printf ("Numero incorreto de parametros.\n Para chamar o programa digite: exemplo <arq_dict> <arq_entrada> <arq_saida>\n");
        return 1;
    }else{
        dict = fopen(argv[1], "r"); // abre o arquivo para leitura -- argv[1] eh o primeiro parametro apos o nome do arquivo.
        if (dict == NULL){ //se nao conseguiu abrir o arquivo
            printf ("Erro ao abrir o arquivo %s",argv[1]);
            return 1;
        }else{
            // le o dicionario e insere as palavras na arvore
            while(fgets(linha_dict,1000,dict)){ // enquanto nao chegar ao final do arquivo
                linha_dict[strcspn(linha_dict, "\n")] = '\0'; // remove o \n do final da linha
                splitStringOnTab(linha_dict,word_key,word_sub); // separa a linha em duas palavras
                rootABP = insertNode(rootABP, word_key,word_sub); // insere a palavra na abp
                rootAVL = insertNodeAVL(rootAVL, word_key,word_sub); // insere a palavra na avl

            }
        }

        fclose(dict); // fecha o arquivo de dicionario

        entrada = fopen (argv[2], "r"); // abre o arquivo para leitura -- argv[1] eh o primeiro parametro apos o nome do arquivo.
        if (entrada == NULL){ //se nao conseguiu abrir o arquivo
            printf ("Erro ao abrir o arquivo %s",argv[2]);
            return 1;
        }else{ // arquivo de entrada OK
            saida = fopen (argv[3], "w"); // abre o arquivo para saida -- argv[2] eh o segundo parametro apos o nome do arquivo.

            while (fgets(linha,1000,entrada)){
                palavra = strtok(linha, separador); //considera qquer caractere nao alfabetico como separador
                while (palavra != NULL){ // enquanto nao chegar ao final da linha
                    palavra = searchAVL(rootAVL, palavra); // busca a palavra na arvore avl
                    fprintf(saida,"%s ", palavra); //strlwr eh a funcao que converte palavras para minusculo
                    palavra = strtok (NULL, separador); // pega a proxima palavra
                }
                fprintf(saida,"%s", "\n"); 
            }
            fseek(entrada, 0, SEEK_SET); // volta para o inicio do arquivo

            //percorre todo o arquivo lendo linha por linha
            while (fgets(linha,1000,entrada)){
                palavra = strtok(linha, separador); //considera qquer caractere n�o alfab�tico como separador
                while (palavra != NULL){
                    palavra = searchTree(rootABP, palavra);
                    fprintf(saida,"%s ", palavra); //strlwr � a fun��o que converte palavras para min�sculo
                    palavra = strtok (NULL, separador);
                }
                fprintf(saida,"%s", "\n");
            }

            height_avl = height(rootAVL); // calcula a altura da arvore avl
            height_abp = 1 + alturaArvore(rootABP); // calcula a altura da arvore abp
            n_nodos_avl = countNodesAVL(rootAVL); // conta o numero de nodos da arvore avl
            n_nodos_abp = contaNodos(rootABP); // conta o numero de nodos da arvore abp
            printf("%d \n", comp_abp); // imprime o numero de comparacoes da abp
            printf("%d \n", comp_avl); // imprime o numero de comparacoes da avl
            printf("%d \n", height_abp); // imprime a altura da abp
            printf("%d \n", height_avl); // imprime a altura da avl
            printf("%d \n", n_nodos_abp); // imprime o numero de nodos da abp
            printf("%d \n", n_nodos_avl); // imprime o numero de nodos da avl
            printf("%d \n", rotations_abp); // imprime o numero de rotacoes da abp
            printf("%d \n", rotations_avl); // imprime o numero de rotacoes da avl
            printf("\nArquivo %s gerado com sucesso.\n",argv[3]);
        }

        fclose (entrada); // fecha arquivo de entrada
        fclose (saida); // fecha arquivo de saida

        return 0;
    }
}

/*
int main(int argc, char *argv[]) //argc conta o n�mero de par�metros e argv armazena as strings correspondentes aos par�mentros digitados
{

    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados

    clock_t start, end; //para contar o tempo decorrido

    FILE * entrada;
    FILE * saida;

    char *palavra, linha[1000]; // linhas a serem lidas do arquivo
    char separador[]= {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};

    if (argc!=3)  //o numero de parametros esperado � 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
    {
        printf ("N�mero incorreto de par�metros.\n Para chamar o programa digite: exemplo <arq_entrada> <arq_saida>\n");
        return 1;
    }
    else
    {

        entrada = fopen (argv[1], "r"); // abre o arquivo para leitura -- argv[1] � o primeiro par�metro ap�s o nome do arquivo.
        if (entrada == NULL) //se n�o conseguiu abrir o arquivo
        {
            printf ("Erro ao abrir o arquivo %s",argv[1]);
            return 1;
        }
        else // arquivo de entrada OK

        {
            saida = fopen (argv[2], "w"); // abre o arquivo para saida -- argv[2] � o segundo par�metro ap�s o nome do arquivo.

            start = clock(); //inicia a contagem do tempo


            //percorre todo o arquivo lendo linha por linha
            while (fgets(linha,1000,entrada))
            {
                palavra = strtok (linha, separador); //considera qquer caractere n�o alfab�tico como separador
                while (palavra != NULL)
                {
                    fprintf(saida,"%s ", strlwr(palavra)); //strlwr � a fun��o que converte palavras para min�sculo
                    palavra = strtok (NULL, separador);
                }
            }

            printf("\nArquivo %s gerado com sucesso.\n",argv[2]);

            end = clock(); // finaliza contagem do tempo
            float miliseconds = (float)(end - start) / CLOCKS_PER_SEC * 1000; //calcula o tempo decorrido
            printf("Tempo: %.5f ms\n",miliseconds);
        }
        fclose (entrada); //fecha os arquivos
        fclose (saida);
        return 0;
    }
}
*/
