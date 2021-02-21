#include <stdbool.h>
#include <stdlib.h>
//#include <stdio.h> // Debug

#include "estruturas.h"

#include "listasEncadeadas.h"

typedef struct{
    Inimigo* primeiroInimigo;
    Inimigo* ultimoInimigo;
    unsigned int tamanhoDaLista;
} ListaDeInimigos;

typedef struct{
    Projetil* primeiroProjetil;
    Projetil* ultimoProjetil;
    unsigned int tamanhoDaLista;
} ListaProjeteisDoInimigo;

typedef struct{
    Projetil* primeiroProjetil;
    Projetil* ultimoProjetil;
    unsigned int tamanhoDaLista;
} ProjeteisProjeteisDoJogador;

ListaDeInimigos listaDeInimigos;
ListaProjeteisDoInimigo listaProjeteisDosInimigos;
ListaProjeteisDoInimigo listaProjeteisDoJogador;

void inicializarListasEncadeadas(){
    listaDeInimigos.primeiroInimigo = NULL;
    listaDeInimigos.ultimoInimigo = NULL;
    listaDeInimigos.tamanhoDaLista = 0;

    listaProjeteisDosInimigos.primeiroProjetil = NULL;
    listaProjeteisDosInimigos.ultimoProjetil = NULL;
    listaProjeteisDosInimigos.tamanhoDaLista = 0;

    listaProjeteisDoJogador.primeiroProjetil = NULL;
    listaProjeteisDoJogador.ultimoProjetil = NULL;
    listaProjeteisDoJogador.tamanhoDaLista = 0;
}

// Lista de Inimigos
bool inimigos_listaVazia(){
    if(listaDeInimigos.tamanhoDaLista == 0){
        return true;
    }
    return false;
}

void inimigos_adicionar(Inimigo inimigo){
    if( inimigos_listaVazia() ){
        listaDeInimigos.primeiroInimigo = (Inimigo*) malloc(sizeof(Inimigo));
        listaDeInimigos.ultimoInimigo = listaDeInimigos.primeiroInimigo;
    }else{
        listaDeInimigos.ultimoInimigo->proximoInimigo = (Inimigo*) malloc(sizeof(Inimigo));
        listaDeInimigos.ultimoInimigo = listaDeInimigos.ultimoInimigo->proximoInimigo;
    }

    listaDeInimigos.ultimoInimigo->dimensoes.largura = inimigo.dimensoes.largura;
    listaDeInimigos.ultimoInimigo->dimensoes.altura = inimigo.dimensoes.altura;
    listaDeInimigos.ultimoInimigo->posicao.x = inimigo.posicao.x;
    listaDeInimigos.ultimoInimigo->posicao.y = inimigo.posicao.y;
    listaDeInimigos.ultimoInimigo->posicao.z = inimigo.posicao.z;
    listaDeInimigos.ultimoInimigo->velocidade = inimigo.velocidade;
    listaDeInimigos.ultimoInimigo->pontosDeVida = inimigo.pontosDeVida;

    listaDeInimigos.ultimoInimigo->proximoInimigo = NULL;

    listaDeInimigos.tamanhoDaLista++;
}

void inimigos_remover(unsigned int indice){
    if(!inimigos_listaVazia() && indice < listaDeInimigos.tamanhoDaLista){
        // Remove o unico inimigo da lista
        if(indice == 0 && listaDeInimigos.tamanhoDaLista == 1){
            free(listaDeInimigos.primeiroInimigo);
            listaDeInimigos.primeiroInimigo = NULL;
            listaDeInimigos.ultimoInimigo = NULL;
            listaDeInimigos.tamanhoDaLista = 0;
            return;
        }

        // Remove o primeiro inimigo de uma lista com tamanho > 1
        if(indice == 0 && listaDeInimigos.tamanhoDaLista > 1){
            Inimigo* novoPrimeiro = listaDeInimigos.primeiroInimigo->proximoInimigo;
            free(listaDeInimigos.primeiroInimigo);
            listaDeInimigos.primeiroInimigo = novoPrimeiro;
            listaDeInimigos.tamanhoDaLista--;
            return;
        }

        // Remove um inimigo no meio da lista
        if(indice > 0 && listaDeInimigos.tamanhoDaLista > 1){
            unsigned int indiceDoInimigoAtual = 0;
            Inimigo* inimigoAtual = listaDeInimigos.primeiroInimigo;
            while(indiceDoInimigoAtual < listaDeInimigos.tamanhoDaLista && inimigoAtual != NULL){
                if(indiceDoInimigoAtual == indice - 1){
                    if(inimigoAtual->proximoInimigo == listaDeInimigos.ultimoInimigo){
                        listaDeInimigos.ultimoInimigo = inimigoAtual->proximoInimigo->proximoInimigo;
                    }
                    Inimigo* inimigoEliminado = inimigoAtual->proximoInimigo;
                    inimigoAtual->proximoInimigo = inimigoAtual->proximoInimigo->proximoInimigo;
                    free(inimigoEliminado);
                    listaDeInimigos.tamanhoDaLista--;
                    return;
                }
                indiceDoInimigoAtual++;
                inimigoAtual = inimigoAtual->proximoInimigo;
            }
        }
    }
}

Inimigo* inimigos_inicioDaLista(){
    return listaDeInimigos.primeiroInimigo;
}

// Lista de Projeteis do Inimigo
bool projeteisDosInimigos_listaVazia(){
    if(listaProjeteisDosInimigos.tamanhoDaLista == 0){
        return true;
    }
    return false;
}

void projeteisDosInimigos_adicionar(Projetil projetil){
    if( projeteisDosInimigos_listaVazia() ){
        listaProjeteisDosInimigos.primeiroProjetil = (Projetil*) malloc(sizeof(Projetil));
        listaProjeteisDosInimigos.ultimoProjetil = listaProjeteisDosInimigos.primeiroProjetil;
    }else{
        listaProjeteisDosInimigos.ultimoProjetil->proximoProjetil= (Projetil*) malloc(sizeof(Projetil));
        listaProjeteisDosInimigos.ultimoProjetil = listaProjeteisDosInimigos.ultimoProjetil->proximoProjetil;
    }

    listaProjeteisDosInimigos.ultimoProjetil->dimensoes.largura = projetil.dimensoes.largura;
    listaProjeteisDosInimigos.ultimoProjetil->dimensoes.altura = projetil.dimensoes.altura;
    listaProjeteisDosInimigos.ultimoProjetil->posicao.x = projetil.posicao.x;
    listaProjeteisDosInimigos.ultimoProjetil->posicao.y = projetil.posicao.y;
    listaProjeteisDosInimigos.ultimoProjetil->posicao.z = projetil.posicao.z;

    listaProjeteisDosInimigos.ultimoProjetil->proximoProjetil = NULL;

    listaProjeteisDosInimigos.tamanhoDaLista++;
}

void projeteisDosInimigos_remover(unsigned int indice){
    if(!projeteisDosInimigos_listaVazia() && indice < listaProjeteisDosInimigos.tamanhoDaLista){
        // Remove o unico projetil da lista
        if(indice == 0 && listaProjeteisDosInimigos.tamanhoDaLista == 1){
            free(listaProjeteisDosInimigos.primeiroProjetil);
            listaProjeteisDosInimigos.primeiroProjetil = NULL;
            listaProjeteisDosInimigos.ultimoProjetil = NULL;
            listaProjeteisDosInimigos.tamanhoDaLista = 0;
            return;
        }

        // Remove o primeiro projetil de uma lista com tamanho > 1
        if(indice == 0 && listaProjeteisDosInimigos.tamanhoDaLista > 1){
            Projetil* novoPrimeiro = listaProjeteisDosInimigos.primeiroProjetil->proximoProjetil;
            free(listaProjeteisDosInimigos.primeiroProjetil);
            listaProjeteisDosInimigos.primeiroProjetil = novoPrimeiro;
            listaProjeteisDosInimigos.tamanhoDaLista--;
            return;
        }

        // Remove um projetil no meio da lista
        if(indice > 0 && listaProjeteisDosInimigos.tamanhoDaLista > 1){
            unsigned int indiceDoProjetilAtual = 0;
            Projetil* projetilAtual = listaProjeteisDosInimigos.primeiroProjetil;
            while(indiceDoProjetilAtual < listaProjeteisDosInimigos.tamanhoDaLista && projetilAtual != NULL){
                if(indiceDoProjetilAtual == indice - 1){
                    if(projetilAtual->proximoProjetil == listaProjeteisDosInimigos.ultimoProjetil){
                        listaProjeteisDosInimigos.ultimoProjetil = projetilAtual->proximoProjetil->proximoProjetil;
                    }
                    Projetil* projetilEliminado = projetilAtual->proximoProjetil;
                    projetilAtual->proximoProjetil = projetilAtual->proximoProjetil->proximoProjetil;
                    free(projetilEliminado);
                    listaProjeteisDosInimigos.tamanhoDaLista--;
                    return;
                }
                indiceDoProjetilAtual++;
                projetilAtual = projetilAtual->proximoProjetil;
            }
        }
    }
}

Projetil* projeteisDosInimigos_inicioDaLista(){
    return listaProjeteisDosInimigos.primeiroProjetil;
}

// Lista de Projeteis do Jogador
bool projeteisDoJogador_listaVazia(){
    if(listaProjeteisDoJogador.tamanhoDaLista == 0){
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
