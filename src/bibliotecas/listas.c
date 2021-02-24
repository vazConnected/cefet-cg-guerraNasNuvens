#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "comuns.h"

#include "listas.h"

Inimigo listaDeInimigos[QUANTIDADE_DE_INIMIGOS];
ProjetilInimigo listaDeProjeteisInimigos[QUANTIDADE_DE_INIMIGOS];

typedef struct{
    Projetil* primeiroProjetil;
    Projetil* ultimoProjetil;
    unsigned int tamanhoDaLista;
} ListaProjeteis;

ListaProjeteis listaProjeteisDoJogador;

void inicializarlistas(){
    listaProjeteisDoJogador.primeiroProjetil = NULL;
    listaProjeteisDoJogador.ultimoProjetil = NULL;
    listaProjeteisDoJogador.tamanhoDaLista = 0;
}

// Lista de Projeteis do Jogador
bool projeteisDoJogador_listaVazia(){
    if(listaProjeteisDoJogador.primeiroProjetil == NULL){
        return true;
    }
    return false;
}

void projeteisDoJogador_adicionar(Projetil projetil){
    if( projeteisDoJogador_listaVazia() ){
        listaProjeteisDoJogador.primeiroProjetil = (Projetil*) malloc(sizeof(Projetil));
        listaProjeteisDoJogador.ultimoProjetil = listaProjeteisDoJogador.primeiroProjetil;
    }else{
        listaProjeteisDoJogador.ultimoProjetil->proximoProjetil= (Projetil*) malloc(sizeof(Projetil));
        listaProjeteisDoJogador.ultimoProjetil = listaProjeteisDoJogador.ultimoProjetil->proximoProjetil;
    }

    listaProjeteisDoJogador.ultimoProjetil->dimensoes.largura = projetil.dimensoes.largura;
    listaProjeteisDoJogador.ultimoProjetil->dimensoes.altura = projetil.dimensoes.altura;
    listaProjeteisDoJogador.ultimoProjetil->posicao.x = projetil.posicao.x;
    listaProjeteisDoJogador.ultimoProjetil->posicao.y = projetil.posicao.y;
    listaProjeteisDoJogador.ultimoProjetil->posicao.z = projetil.posicao.z;

    listaProjeteisDoJogador.ultimoProjetil->proximoProjetil = NULL;

    listaProjeteisDoJogador.tamanhoDaLista++;
}

void projeteisDoJogador_remover(unsigned int indice){
    if(!projeteisDoJogador_listaVazia() && indice < listaProjeteisDoJogador.tamanhoDaLista){
        // Remove o unico projetil da lista
        if(indice == 0 && listaProjeteisDoJogador.tamanhoDaLista == 1){
            //printf("\nremove o unico elemento da lista\n"); //Debug
            free(listaProjeteisDoJogador.primeiroProjetil);
            listaProjeteisDoJogador.primeiroProjetil = NULL;
            listaProjeteisDoJogador.ultimoProjetil = NULL;
            listaProjeteisDoJogador.tamanhoDaLista = 0;
            return;
        }

        // Remove o primeiro projetil de uma lista com tamanho > 1
        if(indice == 0 && listaProjeteisDoJogador.tamanhoDaLista > 1){
            //printf("\nremove o primeiro projetil da lista\n"); //Debug
            Projetil* novoPrimeiro = listaProjeteisDoJogador.primeiroProjetil->proximoProjetil;
            free(listaProjeteisDoJogador.primeiroProjetil);
            listaProjeteisDoJogador.primeiroProjetil = novoPrimeiro;
            listaProjeteisDoJogador.tamanhoDaLista--;
            return;
        }

        // Remove um projetil no meio da lista
        if(indice > 0 && listaProjeteisDoJogador.tamanhoDaLista > 1){
            //printf("\nremove um projetil do meio da lista\n"); // Debug
            unsigned int indiceDoProjetilAtual = 0;
            Projetil* projetilAtual = listaProjeteisDoJogador.primeiroProjetil;
            while(indiceDoProjetilAtual < listaProjeteisDoJogador.tamanhoDaLista && projetilAtual != NULL){
                if(indiceDoProjetilAtual == indice - 1){
                    if(projetilAtual->proximoProjetil == listaProjeteisDoJogador.ultimoProjetil){
                        listaProjeteisDoJogador.ultimoProjetil = projetilAtual->proximoProjetil->proximoProjetil;
                    }
                    Projetil* projetilEliminado = projetilAtual->proximoProjetil;
                    projetilAtual->proximoProjetil = projetilAtual->proximoProjetil->proximoProjetil;
                    free(projetilEliminado);
                    listaProjeteisDoJogador.tamanhoDaLista--;
                    return;
                }
                indiceDoProjetilAtual++;
                projetilAtual = projetilAtual->proximoProjetil;
            }
        }
    }
}

Projetil* projeteisDoJogador_inicioDaLista(){
    return listaProjeteisDoJogador.primeiroProjetil;
}

Inimigo* inimigo_getLista(){
    return listaDeInimigos;
}

void projeteisDoJogador_esvaziarLista(){
    while(listaProjeteisDoJogador.primeiroProjetil != NULL){
        projeteisDoJogador_remover(0);
    }
}

ProjetilInimigo* projeteisDosInimigos_getLista(){
    return listaDeProjeteisInimigos;
}
