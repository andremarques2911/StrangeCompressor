#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/** DEFINICAO DA ARVORE */
typedef struct Node
{
    char              caractere;
    int               frequencia;
    int               internalNode;
    struct Node       *esquerda;
    struct Node       *direita;

}Node;


int listaFrequencia[256] = {0};
int tamanho=0;
int contRefFolhas=0;
int contRefNodes=0;
int contAddRefNode=0;
Node *lista;
Node *listaRefFolhas;
Node *listaRefNodes;


/** PROTOTIPOS */
void CompressFile();
void createLists();
void print(Node *lisSt, int tamanhoLista);
void ordena(Node *list, int tam);
void remove2(Node *list, int *tam);
void insereOrdenado(Node *list, int *tam);
void addLists(Node *esquerda, Node *direita);
Node* addListaRefFolhas(Node folha);
void addListaRefNodes(Node node);
void lerArquivo(char *entrada);


Node* addListaRefFolhas(Node folha)
{
    listaRefFolhas[contRefFolhas] = folha;
    contRefFolhas++;
    return &listaRefFolhas[contRefFolhas-1];
}
void addListaRefNodes(Node n)
{    
    listaRefNodes[contRefNodes] = n;
    contRefNodes++;
}

void addCopy2List(Node n)
{
    lista[tamanho] = n;
    tamanho++;
}

void addLists(Node *esquerda, Node *direita)
{
    Node n;
    n.caractere = '#';
    n.frequencia = esquerda->frequencia + direita->frequencia;
    n.internalNode = 1;
    //printf("n: [ %c , %d ]\n", n.caractere, n.frequencia);
    if(esquerda->caractere == 35){
        if(direita->caractere == 35){
            n.esquerda = &listaRefNodes[contAddRefNode];
            contAddRefNode++;
            n.direita = &listaRefNodes[contAddRefNode];
            contAddRefNode++;
        }
        else{
            n.esquerda = &listaRefNodes[contAddRefNode];
            contAddRefNode++;
            addListaRefFolhas(*direita);
            n.direita = &listaRefFolhas[contRefFolhas-1];
        }
    }
    else if(direita->caractere == 35){
        addListaRefFolhas(*esquerda);
        n.esquerda = &listaRefFolhas[contRefFolhas-1];
        n.direita = &listaRefNodes[contAddRefNode];
        contAddRefNode++;
    }
    else{
        n.esquerda = addListaRefFolhas(*esquerda);
        n.direita = addListaRefFolhas(*direita);
    }   
    // printf("Memo folha1: [ %d , %d ]\n", &listaRefFolhas[0], &listaRefFolhas[1]);
    // printf("Memo folha2: [ %d , %d ]\n", &n.esquerda, &n.direita);
    addListaRefNodes(n);
    addCopy2List(n);
    
}

void insereOrdenado(Node *list, int *tam)
{
    if(*tam>1){
        
        addLists(&list[0], &list[1]);
        remove2(list, tam);
        ordena(list, *tam);   

        // printf("Lista: ");
        // print(list, *tam);
        // printf("\n");

        // printf("Lista Ref Folhas: ");
        // print(listaRefFolhas, contRefFolhas);
        // printf("\n");

        // printf("Lista Ref Nodes: ");
        // print(listaRefNodes, contRefNodes);
        // printf("\n");
        
        //printf("\n");

        insereOrdenado(list, tam);
    }
}

/** ORDENA A LISTA */
void ordena(Node *list, int tam)
{
    Node aux;
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
void remove2(Node *list, int *tam)
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

void createLists(){
    listaRefFolhas = malloc(tamanho * sizeof (Node));
    listaRefNodes = malloc(tamanho * sizeof (Node));
    lista = malloc(tamanho * sizeof (Node));
    int i, j=0;
    for(i=0; i<256; i++){
        if(listaFrequencia[i]>0){
            lista[j].caractere = i;
            lista[j].frequencia = listaFrequencia[i];
            lista[j].internalNode = 0;
            j++;
        }
    }
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

void print(Node *list, int tamanhoLista)
{
    for(int i=0; i<tamanhoLista; i++){
        printf("[ %c , %d ] ", list[i].caractere, list[i].frequencia);
    }
}

void lerArquivo(char *entrada)
{
    FILE *arq;
    arq = fopen("entrada.txt", "r");
    if(arq == NULL) {
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }
    else {
        while( (fscanf(arq,"%s\n", entrada))!=EOF );
    }
    fclose(arq);
}

int main()
{
    char *entrada = malloc(256);
    lerArquivo(entrada);

    printf("Comprimindo...\n");
    getFrequance(entrada);
    createLists();
    ordena(lista, tamanho);
    insereOrdenado(lista, &tamanho);
    Node raiz = listaRefNodes[contRefNodes-1];
    printf("Arquivo comprimido!\n");
    printf("\n");

    printf("Frequencia Raiz            [ %c , %d ]\n", raiz.caractere, raiz.frequencia);
    printf("Frequencia E raiz:         [ %c , %d ]\n", raiz.esquerda->caractere, raiz.esquerda->frequencia);
    printf("Frequencia D raiz:         [ %c , %d ]\n", raiz.direita->caractere, raiz.direita->frequencia);
    printf("Frequencia DE raiz:        [ %c , %d ]\n", raiz.direita->esquerda->caractere, raiz.direita->esquerda->frequencia);
    printf("Frequencia DD raiz:        [ %c , %d ]\n", raiz.direita->direita->caractere, raiz.direita->direita->frequencia);
    printf("Frequencia DDE raiz:       [ %c , %d ]\n", raiz.direita->direita->esquerda->caractere, raiz.direita->direita->esquerda->frequencia);
    printf("Frequencia DDEE raiz:      [ %c , %d ]\n", raiz.direita->direita->esquerda->esquerda->caractere, raiz.direita->direita->esquerda->esquerda->frequencia);
    printf("Frequencia DDED raiz:      [ %c , %d ]\n", raiz.direita->direita->esquerda->direita->caractere, raiz.direita->direita->esquerda->direita->frequencia);
    printf("Frequencia DDD raiz:       [ %c , %d ]\n", raiz.direita->direita->direita->caractere, raiz.direita->direita->direita->frequencia);


    free(entrada);
    free(lista);
    free(listaRefFolhas);
    free(listaRefNodes);
    return 0;
}

