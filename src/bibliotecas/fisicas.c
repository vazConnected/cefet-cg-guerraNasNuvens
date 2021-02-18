#include <stdbool.h>
#include <stdio.h>

#include "estruturas.h"

#include "fisicas.h"

const int VALOR_MOVIMENTACAO_JOGADOR = 5;

void atualizarPosicaoJogador(Jogador* jogador, bool* teclaEspecialApertada, int margemDaTela){
    // Largura da tela: 300
    
    if(teclaEspecialApertada[12] && !teclaEspecialApertada[14]){ // Seta esquerda
        if((*jogador).posicao.x > margemDaTela){
            (*jogador).posicao.x -= VALOR_MOVIMENTACAO_JOGADOR;
            if( (*jogador).posicao.x < margemDaTela){
                (*jogador).posicao.x = margemDaTela;
            }
        }
    }else if(teclaEspecialApertada[14] && !teclaEspecialApertada[12]){ // Seta direita
        if( (*jogador).posicao.x + (*jogador).dimensoes.largura < 300 - margemDaTela){
            (*jogador).posicao.x += VALOR_MOVIMENTACAO_JOGADOR;
            if((*jogador).posicao.x + (*jogador).dimensoes.largura > 300 - margemDaTela){
                (*jogador).posicao.x = 300 - margemDaTela - (*jogador).dimensoes.largura;
            }
        }
    }
}
