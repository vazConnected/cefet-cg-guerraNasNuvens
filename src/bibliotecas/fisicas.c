#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "comuns.h"

#include "fisicas.h"
#include "listas.h"

const int VALOR_MOVIMENTACAO_JOGADOR = 5;
const int VALOR_MOVIMENTACAO_INIMIGO = 5;
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
    jogadorAtingido(jogador);
}

void atualizarProjeteisJogador(Jogador* jogador){
    if(!projeteisDoJogador_listaVazia()){
        Projetil* projetilAtual = projeteisDoJogador_inicioDaLista();
        unsigned int indiceListaProjeteisJogador = 0;

        while(projetilAtual != NULL){
            projetilAtual->posicao.y += VALOR_MOVIMENTACAO_PROJETEIS;
            if( projetilAtual->posicao.y - projetilAtual->dimensoes.altura > 400 ){
                //projeteisDoJogador_remover(indiceListaProjeteisJogador);
            }
            projetilAtual = projetilAtual->proximoProjetil;
            indiceListaProjeteisJogador++;
        }
        
        Inimigo* inimigos = inimigo_getLista();
   		for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
        	if(inimigos[i].posicao.z!=7){
                inimigoAtingido(jogador, &inimigos[i]);
                if(inimigos[i].pontosDeVida <= 0) inimigos[i].posicao.z = 7;
            }
    	}   
    }
}

void atualizarPosicaoDosInimigos(){
	Inimigo* inimigos = inimigo_getLista();	
	bool andar = false;
	if(rand() % 100 < 2){
		andar = true;
	}
	for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
		if(andar && inimigos[i].pontosDeVida > 0 && inimigos[i].posicao.x != INIMIGO_ELIMINADO){
			inimigos[i].posicao.y -= VALOR_MOVIMENTACAO_INIMIGO;
		}
    	
	}
}

void atualizarProjeteisInimigos(){
    Inimigo* inimigos = inimigo_getLista();
    ProjetilInimigo* projeteisInimigos = projeteisDosInimigos_getLista();
    // Possibilidade de atirar
    for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
        if(inimigos[i].pontosDeVida > 0 && projeteisInimigos[i].valido == false){
            if(rand() % 1000 < 2){ // 2% de chance de atirar 
                projeteisInimigos[i].valido = true;
                projeteisInimigos[i].dimensoes.largura = 5;
                projeteisInimigos[i].dimensoes.altura = 5;
                projeteisInimigos[i].posicao.x = inimigos[i].posicao.x + inimigos[i].dimensoes.largura / 2  - projeteisInimigos[i].dimensoes.largura / 2;
                projeteisInimigos[i].posicao.y = inimigos[i].posicao.y - inimigos[i].dimensoes.altura;
                projeteisInimigos[i].posicao.z = 5;
            }
        }
    }
    // Atualizar posicao
    for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
        if(projeteisInimigos[i].valido){
            projeteisInimigos[i].posicao.y = projeteisInimigos[i].posicao.y - VALOR_MOVIMENTACAO_PROJETEIS;
            if(projeteisInimigos[i].posicao.y < 0){
            	projeteisInimigos[i].valido = false;
            }
        }
    }
}

void inimigoAtingido(Jogador* jogador, Inimigo* inimigo){
    if(!projeteisDoJogador_listaVazia()){
        Projetil* projetilAtual = projeteisDoJogador_inicioDaLista();
        while(projetilAtual != NULL){
            if(projetilAtual->posicao.y < inimigo->posicao.y - inimigo->dimensoes.altura){} // Tiro de baixo
            else if(projetilAtual->posicao.y - projetilAtual->dimensoes.altura > inimigo->posicao.y){} // Tiro de cima
			else if(projetilAtual->posicao.x + projetilAtual->dimensoes.largura < inimigo->posicao.x){} // Tiro na esquerda
			else if(projetilAtual->posicao.x > inimigo->posicao.x + inimigo->dimensoes.largura){} // Tiro na direita
			else{ // Tiro atingiu alvo
				projetilAtual->posicao.y = 401 +  projetilAtual->dimensoes.altura;
				inimigo->pontosDeVida--;
                inimigo->posicao.z = 6;
				jogador->pontosDeAtaque += 10;
			}
            projetilAtual = projetilAtual->proximoProjetil;
        }
    }
}

void jogadorAtingido(Jogador* jogador){
    ProjetilInimigo* projeteisInimigos = projeteisDosInimigos_getLista();
    for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
        if(projeteisInimigos[i].valido){
            if(projeteisInimigos[i].posicao.y < jogador->posicao.y - jogador->dimensoes.altura){} // Tiro em baixo
			else if(projeteisInimigos[i].posicao.y - projeteisInimigos[i].dimensoes.altura > jogador->posicao.y){} // Tiro em cima
			else if(projeteisInimigos[i].posicao.x + projeteisInimigos[i].dimensoes.largura < jogador->posicao.x){} // Tiro na esquerda
			else if(projeteisInimigos[i].posicao.x > jogador->posicao.x + jogador->dimensoes.largura){} // Tiro na direita
			else{ // Tiro atingiu alvo
				projeteisInimigos[i].valido = false;
				jogador->pontosDeVida--;
                jogador->posicao.z = 7;
			}
        }
    }
}
