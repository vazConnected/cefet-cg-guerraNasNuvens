#include <stdbool.h>
#include <stdio.h>

#include "estruturas.h"

#include "fisicas.h"

const int VALOR_MOVIMENTACAO_JOGADOR = 5;
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

void atualizarProjeteisInimigo(Projetil* inicioListaProjeteisInimigo, bool(*listaVazia)(void), void(*remover)(unsigned int) ){
    if(!listaVazia()){
        Projetil* projetilAtual = inicioListaProjeteisInimigo;
        unsigned int indiceListaInimigo = 0;

        while(projetilAtual != NULL){
            if( projetilAtual->posicao.y - projetilAtual->dimensoes.altura > 0 ){
                projetilAtual->posicao.y -= VALOR_MOVIMENTACAO_PROJETEIS;
                if( projetilAtual->posicao.y < 0 ){
                    remover(indiceListaInimigo);
                }
            }
            projetilAtual = projetilAtual->proximoProjetil;
        }
    }
}

void atualizarProjeteisJogador(Projetil* inicioListaProjeteisJogador, bool(*listaVazia)(void), void(*remover)(unsigned int) ){
    if(!listaVazia()){
        Projetil* projetilAtual = inicioListaProjeteisJogador;
        unsigned int indiceListaInimigo = 0;

        while(projetilAtual != NULL){
            if( projetilAtual->posicao.y - projetilAtual->dimensoes.altura < 400 ){
                projetilAtual->posicao.y += VALOR_MOVIMENTACAO_PROJETEIS;
                if( projetilAtual->posicao.y - projetilAtual->dimensoes.altura > 400 ){
                    remover(indiceListaInimigo);
                }
            }
            projetilAtual = projetilAtual->proximoProjetil;
        }
    }
}
