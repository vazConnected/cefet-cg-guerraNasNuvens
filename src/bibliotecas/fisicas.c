#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "comuns.h"

#include "fisicas.h"
#include "listas.h"

const int VALOR_MOVIMENTACAO_JOGADOR = 5;
const int VALOR_MOVIMENTACAO_INIMIGO = 1;
const int VALOR_MOVIMENTACAO_PROJETEIS = 8;

void atualizarPosicaoJogador(Jogador* jogador, bool* teclaEspecialApertada, int margemDaTela){
    // Largura da tela: 300

    if(teclaEspecialApertada[12] && !teclaEspecialApertada[14]){ // Seta esquerda
        if(jogador->posicao.x > margemDaTela){
            jogador->posicao.x -= VALOR_MOVIMENTACAO_JOGADOR;
            if( jogador->posicao.x < margemDaTela){
                jogador->posicao.x = margemDaTela;
            }
        }
    }else if(teclaEspecialApertada[14] && !teclaEspecialApertada[12]){ // Seta direita
        if( jogador->posicao.x + jogador->dimensoes.largura < 300 - margemDaTela){
            jogador->posicao.x += VALOR_MOVIMENTACAO_JOGADOR;
            if(jogador->posicao.x + jogador->dimensoes.largura > 300 - margemDaTela){
                jogador->posicao.x = 300 - margemDaTela - jogador->dimensoes.largura;
            }
        }
    }
}

void atualizarProjeteisJogador(){
    if(!projeteisDoJogador_listaVazia()){
        Projetil* projetilAtual = projeteisDoJogador_inicioDaLista();
        unsigned int indiceListaProjeteisJogador = 0;

        while(projetilAtual != NULL){
            projetilAtual->posicao.y += VALOR_MOVIMENTACAO_PROJETEIS;
            if( projetilAtual->posicao.y - projetilAtual->dimensoes.altura > 400 ){
                projeteisDoJogador_remover(indiceListaProjeteisJogador);
            }
            projetilAtual = projetilAtual->proximoProjetil;
            indiceListaProjeteisJogador++;
        }
    }
}

void atualizarPosicaoDosInimigos(){
    Inimigo* inimigos = inimigo_getLista();
    for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
        if(inimigos[i].pontosDeVida > 0){
            inimigos[i].posicao.y -= VALOR_MOVIMENTACAO_INIMIGO;
            if(inimigos[i].posicao.y < 0){
                inimigos[i].posicao.y = 400 - inimigos[i].dimensoes.altura;
            }
        }
    }
}

void atualizarProjeteisInimigos(Jogador* jogador){
    Inimigo* inimigos = inimigo_getLista();
    ProjetilInimigo* projeteisInimigos = projeteisDosInimigos_getLista();

    // Possibilidade de atirar
    for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
        if(inimigos[i].pontosDeVida > 0 && projeteisInimigos[i].valido == false){
            if(rand() % 100 < 2){ // 2% de chance de atirar 
                projeteisInimigos[i].valido = true;
                projeteisInimigos[i].dimensoes.largura = 4;
                projeteisInimigos[i].dimensoes.altura = 10;
                projeteisInimigos[i].posicao.x = inimigos[i].posicao.x + inimigos[i].dimensoes.largura / 2  - projeteisInimigos[i].dimensoes.largura / 2;
                projeteisInimigos[i].posicao.y = inimigos[i].posicao.y - inimigos[i].dimensoes.altura;
                projeteisInimigos[i].posicao.z = 5;
            }
        }
    }
    // Atualizar posicao
    for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
        if(projeteisInimigos[i].valido == true){
            projeteisInimigos[i].posicao.y = projeteisInimigos[i].posicao.y - VALOR_MOVIMENTACAO_PROJETEIS;
            if(projeteisInimigos[i].posicao.y <= 0){
                projeteisInimigos[i].valido = false;  
            }
        }
    }
}

bool inimigoAtingido(Inimigo inimigo){
    if(!projeteisDoJogador_listaVazia()){
        Projetil* projetilAtual = projeteisDoJogador_inicioDaLista();
        unsigned int indiceListaProjeteisJogador = 0;

        while(projetilAtual != NULL){
            if(projetilAtual->posicao.y >= inimigo.posicao.y - inimigo.dimensoes.altura){
                if(projetilAtual->posicao.x >= inimigo.posicao.x || projetilAtual->posicao.x + projetilAtual->dimensoes.largura >= inimigo.posicao.x){
                    if(projetilAtual->posicao.x < inimigo.posicao.x + inimigo.dimensoes.largura){
                        return true;
                    }
                }
            }
            projetilAtual = projetilAtual->proximoProjetil;
            indiceListaProjeteisJogador++;
        }
    }
    return false;
}

bool jogadorAtingido(Jogador jogador){
    ProjetilInimigo* projeteisInimigos = projeteisDosInimigos_getLista();
    for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
        if(projeteisInimigos[i].valido){
            if(projeteisInimigos[i].posicao.y >= jogador.posicao.y - jogador.dimensoes.altura){
                if(projeteisInimigos[i].posicao.x >= jogador.posicao.x || projeteisInimigos[i].posicao.x + projeteisInimigos[i].dimensoes.largura >= jogador.posicao.x){
                    if(projeteisInimigos[i].posicao.x < jogador.posicao.x + jogador.dimensoes.largura){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
