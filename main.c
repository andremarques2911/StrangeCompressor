#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/** DEFINICAO DA ARVORE */
typedef struct node
{
    int               frequencia;
    char              caractere;
    int               internalNode;
    struct node       *esquerda;
    struct node       *direita;

}node;

/** VARIAVEIS */
int listaFrequencia[256] = {0};
int tamanho;
int contRefFolhas=0;
int contRefNodes=0;
int contAddRefNode=0;
node *listaRefFolhas;
node *listaRefNodes;
node *lista;

/** PROTOTIPOS */
void CompressFile();
void createLists();
void print(node *lisSt, int tamanhoLista);
void ordena(node *list, int tam);
void remove2(node *list, int *tam);
void insereOrdenado(node *list, int *tam);
void addLists(node *esquerda, node *direita);
node newNode(node *esquerda, node *direita);
void addListaRefFolhas(node folha);
void addListaRefNodes(node node);
void addLeftRefNode(node *n);
void addRigthRefNode(node *n);
void addLeftRefFolha(node *n);
void addRigthRefFolha(node *n);

node newNode(node *esquerda, node *direita)
{
    node n;
    n.caractere = '#';
    n.frequencia = esquerda->frequencia + direita->frequencia;
    n.internalNode = 1;
    return n;
}
void addListaRefFolhas(node folha)
{
    listaRefFolhas[contRefFolhas] = folha;
    contRefFolhas++;
}
void addListaRefNodes(node node)
{
    listaRefNodes[contRefNodes] = node;
    contRefNodes++;
}
void addLeftRefNode(node *n)
{
    n->esquerda = &listaRefNodes[contAddRefNode];
    contAddRefNode++;
}
void addRigthRefNode(node *n)
{
    n->direita = &listaRefNodes[contAddRefNode];
    contAddRefNode++;
}
void addLeftRefFolha(node *n)
{
    n->esquerda = &listaRefFolhas[contRefFolhas-1];
}
void addRigthRefFolha(node *n)
{
    n->direita = &listaRefFolhas[contRefFolhas-1];
}
void addLists(node *esquerda, node *direita)
{
    node n = newNode(esquerda, direita);
    if(esquerda->caractere == 35){
        if(direita->caractere == 35){
            addLeftRefNode(&n);
            addRigthRefNode(&n);
        }
        else
        {
            addLeftRefNode(&n);
            addListaRefFolhas(*direita);
            addRigthRefFolha(&n); 
        }       
    }
    else if(direita->caractere == 35){
        addListaRefFolhas(*esquerda);
        addLeftRefFolha(&n);
        addRigthRefNode(&n);
    }
    else{
        addListaRefFolhas(*esquerda);
        addLeftRefFolha(&n);
        addListaRefFolhas(*direita);
        addRigthRefFolha(&n);    
    }
    printf("n: [ %c , %d ]\n", n.caractere, n.frequencia);
    printf("n.esquerda: [ %c , %d ]\n", n.esquerda->caractere, n.esquerda->frequencia);
    printf("n.direita: [ %c , %d ]\n", n.direita->caractere, n.direita->frequencia);
    addListaRefNodes(n);
    lista[tamanho] = n;
    tamanho++;
}

void insereOrdenado(node *list, int *tam){
    printf("\nENTROU NO INSERE ORDENADO\n");
    printf("Lista: ");
    print(list, *tam);
    printf("\n");
    if(*tam>1){
        addLists(&list[0], &list[1]);
        remove2(list, tam);
        ordena(list, *tam);        
        insereOrdenado(list, tam);
    }
}

/** ORDENA A LISTA */
void ordena(node *list, int tam)
{
    node aux;
    int alterou=0;
    int pos = 0;
    while(tam>1){
        if(list[pos].frequencia > list[pos+1].frequencia){
            aux.frequencia = list[pos].frequencia;
            aux.caractere = list[pos].caractere;
            list[pos].frequencia = list[pos+1].frequencia;
            list[pos].caractere = list[pos+1].caractere;
            list[pos+1].frequencia = aux.frequencia;
            list[pos+1].caractere = aux.caractere;
            alterou = 1;
        }
        else if(list[pos].frequencia == list[pos+1].frequencia){
            if (list[pos+1].caractere == 35)
            {
                aux.frequencia = list[pos].frequencia;
                aux.caractere = list[pos].caractere;
                list[pos].frequencia = list[pos+1].frequencia;
                list[pos].caractere = list[pos+1].caractere;
                list[pos+1].frequencia = aux.frequencia;
                list[pos+1].caractere = aux.caractere;
                alterou = 1;
            }
        }
        pos++;
        if(pos == (tam-1)){
            if(alterou == 1){
                pos = 0;
                alterou = 0;
                tam--;
            }
            else if(alterou == 0){
                break;
            }
        }
    }
}

/**REMOVE DA LISTA OS DOIS PRIMEIROS ELEMENTOS*/
void remove2(node *list, int *tam)
{
    int cont=0;
    for (int i = 0; i < *tam; i++)
    {
        if(i>1){
            list[cont] = list[i];
            cont++;
        }
        //printf("Cont: %d\n", cont);
    }
    *tam -= 2;
}

/** OBTEM A FREQUENCIA QUE DE CADA CARACTERE E OBTEM TAMANHO DA LISTA*/
void getFrequance(char *strIn)
{
    for(int i=0; i<strlen(strIn); i++){
        listaFrequencia[strIn[i]] += 1;
    }

    for(int i=0; i<256; i++){
        if(listaFrequencia[i]>0){
            tamanho++;
        }
    }
}

/** CRIA AS LISTA INICIAL E ALOCA LISTAS AUXILIARES  */
void createLists()
{    
    lista = calloc(tamanho, sizeof lista);
    int j=0;
    for(int i=0; i<256; i++){
        if(listaFrequencia[i]>0){
            lista[j].caractere = i;
            lista[j].frequencia = listaFrequencia[i];
            lista[j].internalNode = 0;
            j++;
        }
    }    
}

/** FUNCAO QUE COMPRIME UM ARQUIVO UTILIZANDO A COMPRESSAO DE HUFFMAN */
void CompressFile(char *listaEntrada)
{
    printf("Comprimindo...\n");
    getFrequance(listaEntrada);
    createLists();
    ordena(lista, tamanho);
    listaRefFolhas = calloc(tamanho, sizeof listaRefFolhas);
    listaRefNodes = calloc(tamanho, sizeof listaRefNodes);
    insereOrdenado(lista, &tamanho);
    printf("Arquivo comprimido!");
}

void print(node *list, int tamanhoLista)
{
    for(int i=0; i<tamanhoLista; i++){
        printf("[ %c , %d ] ", list[i].caractere, list[i].frequencia);
    }
}

int main()
{
    char entrada[] = "aaaaabbbbcccdde";
    CompressFile(entrada);

    free(listaRefFolhas);
    free(listaRefNodes);
    free(lista);

    return 0;
}