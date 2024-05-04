#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <math.h>

float vet[10000][10000];

struct sCoordenada {
    int init;
    int end;
    int i;
};

void preencherColuna(struct sCoordenada *coord) {
    int init = coord->init;
    int end = coord->end;
    int i = coord->i;

    for (int j = init; j < end; j++) {
        int value = (float) ((i * (j*j*j)) * (i*i*i*i)) / (i*i);
        vet[i][j] = value;
        printf("i: %d | j: %d | value: %d\n\n", i, j, value);
    }
}

void preencherColunaGeral(int i){
    int j = 0;
    while(j < 10000){
        struct sCoordenada *coord;
        coord = (struct sCoordenada *) malloc(sizeof(struct sCoordenada));
        coord->init = j;
        coord->end = j + 1000;
        coord->i = i;
        _beginthread(preencherColuna, NULL, coord);
        j = j + 1000;
    }
}

void preencherLinha(struct sCoordenada *coord) {
    int init = coord->init;
    int end = coord->end;

    for (int i = init; i < end; i++) {
        _beginthread(preencherColunaGeral, NULL, i);
    }
}

void preencherLinhaGeral(){
    int i = 0;
    while(i < 10000){
        struct sCoordenada *coord;
        coord = (struct sCoordenada *) malloc(sizeof(struct sCoordenada));
        coord->init = i;
        coord->end = i + 1000;
        coord-> i = NULL;
        _beginthread(preencherLinha, NULL, coord);
        i = i + 1000;
    }
}

int main() {
    _beginthread(preencherLinhaGeral, NULL, NULL);

    getchar();
    return 0;
}