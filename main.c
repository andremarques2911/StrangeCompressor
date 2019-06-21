#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** DEFINICAO DA ARVORE */
typedef struct Node
{
    char              caractere;
    int               frequencia;
    struct Node       *esquerda;
    struct Node       *direita;

}Node;

/** DEFINICAO DA TABELA DE HUFFMAN */
typedef struct Table
{
    char caractere;
    char codigo[5];
}Table;

/** VARIAVEIS */
int listaFrequencia[256] = {0};
int TAMLISTA;
int tamanho=0;
int contRefFolhas=0;
int contRefNodes=0;
int contAddRefNode=0;
int contTable=0;
char *path;
Table *table;
Node *lista;
Node *listaRefFolhas;
Node *listaRefNodes;

/** PROTOTIPOS */
Node* addListaRefFolhas(Node folha);
void addListaRefNodes(Node n);
void addCopy2List(Node n);
void addLists(Node *esquerda, Node *direita);
void insereOrdenado(Node *list, int *tam);
void ordena(Node *list, int tam);
void remove2(Node *list, int *tam);
void createLists();
void getFrequance(char *strIn);
void lerArquivo(char *entrada);
void generateTable(Node *n, int cont);
void saveArq(char *huffman, int tam);
char* getCode(char carac);
void generateOut(char *entrada);
void print(Node *list, int tamanhoLista);

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
void createLists()
{
    listaRefFolhas = malloc(tamanho * sizeof (Node));
    listaRefNodes = malloc(tamanho * sizeof (Node));
    lista = malloc(tamanho * sizeof (Node));
    table = malloc(tamanho * sizeof (Table));
    int i, j=0;
    for(i=0; i<256; i++){
        if(listaFrequencia[i]>0){
            lista[j].caractere = i;
            lista[j].frequencia = listaFrequencia[i];
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
    TAMLISTA = tamanho;
}
/** LE O ARQUIVO DO DIRETORIO */
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
/** GERA A TABELA DE HUFFMAN */
void generateTable(Node *n, int cont)
{
    if(n->caractere != 35){
        table[contTable].caractere = n->caractere;
        strcpy(table[contTable].codigo, path);
        contTable++;
        path[cont] = '\0';
        cont--;
        return;
    }
    path[cont] = '0';
    generateTable(n->esquerda, cont + 1);
    path[cont] = '1';
    generateTable(n->direita, cont + 1);
    path[cont] = '\0';
    cont--;
}
/** SALVA O ARQUIVO NO DIRETORIO COM A TABELA E O ARQUIVO CODIFICADO */
void saveArq(char *huffman, int tam)
{
    char *out = malloc(200 * sizeof(out));

    for(int i=0; i<contTable; i++){
        strcat(out, &table[i].caractere);
        tam+=strlen(&table[i].caractere);
        //strcat(out, table[i].codigo);
        strcat(out, "\n");
        tam++;
    }
    strcat(out, "\n#");
    tam+=2;
    strcat(out, huffman);
    FILE *saida = fopen("saida.txt", "w");
    fwrite(out, tam, sizeof(out[0]), saida);
    //fclose(saida);
}
/** OBTEM CODIGO GUARDADO NA TABELA DE HUFFMAN DE UM CARACTERE */
char* getCode(char carac) 
{
    for (int i = 0; i < contTable; i++)
    {
        if(table[i].caractere == carac){
            
            return table[i].codigo;
        }
    }
}
/** GERA A CODIFICACAO DO ARQUIVO DE ENTRADA UTILIZADO O CODIGO NA TABELA DE HUFFMAN */
void generateOut(char *entrada)
{
    char huffman[300];
    int contUsado=0;
    for (int i = 0; i < strlen(entrada); i++)
    {
        contUsado += strlen(getCode(entrada[i]));
        strcat(huffman, getCode(entrada[i]));
    }
    saveArq(huffman, contUsado);
}
/** PRINTA NA TELA UMA LISTA DE NODES */
void print(Node *list, int tamanhoLista)
{
    for(int i=0; i<tamanhoLista; i++){
        printf("[ %c , %d ] ", list[i].caractere, list[i].frequencia);
    }
}
/** FUNCAO PRNCIPAL */
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
    path = calloc(TAMLISTA, sizeof path);
    generateTable(&raiz, 0);

    generateOut(entrada);

    printf("Arquivo comprimido!\n");
    printf("\n");

    free(entrada);
    free(lista);
    free(listaRefFolhas);
    free(listaRefNodes);
    free(path);
    
    return 0;
}

