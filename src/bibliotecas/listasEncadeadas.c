#include <stdbool.h>
#include <stdlib.h>

#include "estruturas.h"

#include "listasEncadeadas.h"

Inimigo *inicioListaInimigos = NULL;
Inimigo *fimListaInimigos = NULL;

Projetil *inicioListaProjeteisInimigos = NULL;
Projetil *fimListaProjeteisInimigos = NULL;

Projetil *inicioListaProjeteisJogador = NULL;
Projetil *fimListaProjeteisJogador = NULL;

bool inimigo_listaVazia(){
    if(inicioListaInimigos == NULL){
        return true;
    }
    return false;
}

void inimigo_adicionar(Inimigo *inimigo){
    fimListaInimigos->proximoInimigo = inimigo;
    inimigo->proximoInimigo = NULL;
    fimListaInimigos = inimigo;
}

void inimigo_remover(unsigned int indice){
    Inimigo *inimigoAtual = inicioListaInimigos;
    unsigned int indiceAtual = 0;
    while(inimigoAtual != NULL){
        if(indiceAtual == indice - 1){
            Inimigo* inimigoEliminado = inimigoAtual->proximoInimigo;
            Inimigo* inimigoSubsequente = inimigoEliminado->proximoInimigo;
            inimigoAtual->proximoInimigo = inimigoSubsequente;
            free(inimigoEliminado);
            break;
        }
        indiceAtual++;
        inimigoAtual = inimigoAtual->proximoInimigo;
    }
}

bool projeteisInimigo_listaVazia(){
    if(inicioListaProjeteisInimigos == NULL){
        return true;
    }
    return false;
}

void projeteisInimigo_adicionar(Projetil *projetil){
    fimListaProjeteisInimigos->proximoProjetil = projetil;
    projetil->proximoProjetil = NULL;
    fimListaProjeteisInimigos = projetil;
}

void projeteisInimigo_remover(unsigned int indice){
    Projetil *projetilAtual = inicioListaProjeteisInimigos;
    unsigned int indiceAtual = 0;
    while(projetilAtual != NULL){
        if(indiceAtual == indice - 1){
            Projetil* projetilEliminado = projetilAtual->proximoProjetil;
            Projetil* projetilSubsequente = projetilEliminado->proximoProjetil;
            projetilAtual->proximoProjetil = projetilSubsequente;
            free(projetilEliminado);
            break;
        }
        indiceAtual++;
        projetilAtual = projetilAtual->proximoProjetil;
    }
}

bool projeteisJogador_listaVazia(){
    if(inicioListaProjeteisJogador == NULL){
        return true;
    }
    return false;
}

void projeteisJogador_adicionar(Projetil *projetil){
    fimListaProjeteisJogador->proximoProjetil = projetil;
    projetil->proximoProjetil = NULL;
    fimListaProjeteisJogador = projetil;
}

void projeteisJogador_remover(unsigned int indice){
    Projetil *projetilAtual = inicioListaProjeteisJogador;
    unsigned int indiceAtual = 0;
    while(projetilAtual != NULL){
        if(indiceAtual == indice - 1){
            Projetil* projetilEliminado = projetilAtual->proximoProjetil;
            Projetil* projetilSubsequente = projetilEliminado->proximoProjetil;
            projetilAtual->proximoProjetil = projetilSubsequente;
            free(projetilEliminado);
            break;
        }
        indiceAtual++;
        projetilAtual = projetilAtual->proximoProjetil;
    }
}
