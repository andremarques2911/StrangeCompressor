#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char carac;
    int freq;
    struct Freqs *esquerda;
    struct Freqs *direita;
}Freqs;

int tamanho = 0;

// PROTIPOS
void ordena(Freqs *caracFreq, int tam);
void remove2(Freqs *caracFreq, int *tam);

void insereOrdenado(Freqs *vet, int *tam){
     /**
    * Pega os dois menores da lista
    * Soma as frequencias
    * Cria um novo nodo com a soma deles
    * Coloca o menor dos dois selecionados como filho da esquerda
    * e o maior como filho da direita
    * Remove os dois menores da lista
    * Decrementa tamanho lista
    * Insere o novo nodo na lista
    * Incrementa o tamanho da lista
    * Ordena a lista
    **/
    if(*tam>1){

        Freqs *menor = &vet[0];
        Freqs *maior = &vet[1];
        Freqs novoNodo;
        novoNodo.freq = menor->freq + maior->freq;
        printf("\n\n");
        for(int i=0; i<tamanho; i++){
            printf(" [ %c, %d ] ", vet[i].carac, vet[i].freq);
        }
        printf("\nSoma dos valores: %d\n", novoNodo.freq);
        novoNodo.esquerda = (struct Freqs*)menor;
        novoNodo.direita = (struct Freqs*)maior;
        novoNodo.carac = '@';
        printf("Tamanho inicial: %d\n", *tam);
        remove2(vet, tam);
        printf("Tamanho apos remove: %d\n", *tam);
        vet[*tam] = novoNodo;
        *tam += 1;
        printf("Tamanho apos insere: %d\n", *tam);
        ordena(vet,*tam);
        
        insereOrdenado(vet, tam);
    }
    else{

    }
    /**
        Freqs *menor = &vet[0];
        Freqs *maior = &vet[1];
        Freqs novoNodo;
        novoNodo.freq = menor->freq + maior->freq;
        novoNodo.esquerda = menor;
        novoNodo.direita = maior;
        vet[*tam] = novoNodo;
        tam++;
        remove2(&vet, &tam);
        ordena(&vet,&tam);
        insereOrdenado(&vet, &tam);
    **/
}

void ordena(Freqs *caracFreq, int tam){
    Freqs aux;
    int alterou=0;
    int pos = 0;
    while(tam>1){
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

void remove2(Freqs *caracFreq, int *tam){
    int cont=0;
    for (int i = 0; i < *tam; i++)
    {
        if(i>1){
            caracFreq[cont] = caracFreq[i];
            cont++;
        }
        //printf("Cont: %d\n", cont);
    }
    *tam -= 2;
}

int main() {
    //char* entrada = calloc(300, sizeof entrada);
    char entrada[] = "aaaaabbbbcccdde";
    // Vetor criado para controlar numero de ocorrencias de caracteres
    int* numeroCaracteres = calloc(256, sizeof numeroCaracteres);
    // Controla tamanho da lista
    //int tamanho = 0;
    // Percorre os caracteres e soma uma unidade na posicao do vetor de controle de ocorrencias
    // na posicao com o mesmo valor do caractere em decimal
    printf("Caracteres da mensagem em decimal:\n");
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
    // Busca tamanho da lista de caracteres e frequencia
    for(int i=0; i<256; i++){
        if(numeroCaracteres[i] != 0) {
            tamanho++;
        }
    }
    printf("\n\nTamanho: %d\n\n", tamanho);
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
    ordena(caracFreq, tamanho);

    for(int i=0; i<tamanho; i++){
        printf(" [ %c, %d ] ", caracFreq[i].carac, caracFreq[i].freq);
    }

    printf("\n\n");
    insereOrdenado(caracFreq, &tamanho);

    for(int i=0; i<tamanho; i++){
        printf(" [ %c, %d ] ", caracFreq[i].carac, caracFreq[i].freq);
    }

    printf("\n\nTamanho: %d\n\n", tamanho);

    printf("\n\n######################################################################\n\n");

    


    //printf("\nHello world!\n");
    free(numeroCaracteres);
    return 0;
}
