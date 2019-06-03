#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char carac;
    int freq;
    struct Freqs *esquerda;
    struct Freqs *direita;
}Freqs;

Freqs* insereOrdenado(Freqs *caracFreg, int numeroCaracteres, char carac){
    printf("Carac: %c\n", caracFreg->carac);
    printf("Freg: %d\n", caracFreg->freq);
    printf("Num Carac: %d\n", numeroCaracteres);
    printf("CaracAdicionado: %c\n", carac);
}

void ordena(Freqs *caracFreq, int tam){
    // Ordena o vetor
    Freqs aux;
    int alterou=0;
    int pos = 0;

    while(tam>0){
        if(caracFreq[pos].freq > caracFreq[pos+1].freq){
            aux.freq = caracFreq[pos].freq;
            aux.carac = caracFreq[pos].carac;
            caracFreq[pos].freq = caracFreq[pos+1].freq;
            caracFreq[pos].carac = caracFreq[pos+1].carac;
            caracFreq[pos+1].freq = aux.freq;
            caracFreq[pos+1].carac = aux.carac;
            alterou = 1;
        }
        pos++;
        if(pos == tam){
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

    for(int i=0; i<5; i++){
        printf(" [ %c, %d ] ", caracFreq[i].carac, caracFreq[i].freq);
    }
    printf("\n\n");

}


int main()
{
    //char* entrada = calloc(300, sizeof entrada);
    char entrada[] = "aaaaabbbbcccdde";
    // Vetor criado para controlar numero de ocorrencias de caracteres
    int* numeroCaracteres = calloc(256, sizeof numeroCaracteres);
    // Controla tamanho da lista
    int tamanho = 0;
    // Struct armazena caracteres e frequencia



    // Percorre os caracteres e soma uma unidade na posicao do vetor de controle de ocorrencias
    // na posicao com o mesmo valor do caractere em decimal
    printf("Caracteres da mensagem em decmal:\n");
    for(int i=0; i<strlen(entrada); i++){
        printf(" [%d] ", entrada[i]);
        numeroCaracteres[(int)entrada[i]] += 1;
    }
    printf("\n\nVezes que cada caractere apreceu:\n");
    // Percorre todo vetor de controle de ocorrencias e mostra quantas vezes cada caractere
    // apareceu
    for(int i=0; i<256; i++){
        printf(" [%d] ", numeroCaracteres[i]);
    }
    //char* listaCaracteres = calloc()
    /**
    */

    // Busca tamanho da lista de caracteres e frequencia
    for(int i=0; i<256; i++){
        if(numeroCaracteres[i] != 0) {
            tamanho++;
        }
    }

    printf("\nTamanho: %d\n", tamanho);

    // Struct que armazena caracteres e suas respectivas frequencias
    Freqs caracFreq[tamanho];
    int contCaracFreq=0;
    for(int i=0; i<256; i++){
        if(numeroCaracteres[i] > 0) {
            if(i==32){
                caracFreq[contCaracFreq].carac = 95;
                caracFreq[contCaracFreq].freq = numeroCaracteres[i];
                contCaracFreq++;
            }
            else{
                caracFreq[contCaracFreq].carac = i;
                caracFreq[contCaracFreq].freq = numeroCaracteres[i];
                contCaracFreq++;
            }
        }
    }

    for(int i=0; i<tamanho; i++){
        printf(" [ %c, %d ] ", caracFreq[i].carac, caracFreq[i].freq);
    }
    printf("\n\n");
/*
    // Ordena o vetor
    Freqs aux;
    int contAlt=tamanho;
    int alterou=0;
    int pos = 0;

    while(contAlt>0){
        if(caracFreq[pos].freq > caracFreq[pos+1].freq){
            aux.freq = caracFreq[pos].freq;
            aux.carac = caracFreq[pos].carac;
            caracFreq[pos].freq = caracFreq[pos+1].freq;
            caracFreq[pos].carac = caracFreq[pos+1].carac;
            caracFreq[pos+1].freq = aux.freq;
            caracFreq[pos+1].carac = aux.carac;
            alterou = 1;
        }
        pos++;
        if(pos == contAlt){
            if(alterou == 1){
                pos = 0;
                alterou = 0;
                contAlt--;
            }
            else if(alterou == 0){
                break;
            }
        }
    }
*/
    ordena(caracFreq, tamanho);

    for(int i=0; i<tamanho; i++){
        printf(" [ %c, %d ] ", caracFreq[i].carac, caracFreq[i].freq);
    }


    //int controleLaco = tamanho;
   // while(controleLaco > 1){

        /**
        * Pega os dois menores da lista
        * Soma as frequencias
        * Cria um novo nodo com a soma deles
        * Coloca o menor dos dois selecionados como filho da esquerda
        * e o maior como filho da direita
        * Remove os dois menores da lista
        * Decrementa tamanho lista
        * Insere o novo nodo na lista
        * Ordena a lista
        **/
/*
        Freqs menor = caracFreq[0];
        Freqs maior = caracFreq[1];
        int somaFrequencia = menor->freq + maior->freq;
        Freqs novoNodo;
        novoNodo->freq = somaFrequencia;
        novoNodo->esquerda = menor;
        novoNodo->direita = maior;
        remove();
        insere(novoNodo);
        ordena();


    }

*/


    //printf("\nHello world!\n");
    free(numeroCaracteres);
    return 0;
}
