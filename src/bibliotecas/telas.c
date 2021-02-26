#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "comuns.h"
#include "fisicas.h"

#include "telas.h"

void inicio_desenhaCena(){
    glColor3f(0.4, 0.7647, 0.996); // RGB: 102 195 154
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(  0,   0, 0);
        glVertex3f(300,   0, 0);
        glVertex3f(300, 400, 0);
        glVertex3f(  0, 400, 0);
    glEnd();
}

void jogo_desenhaCena(Jogador jogador, Projetil* listaProjeteisDoJogador){
    
    // Desenha fundo azul
    glColor3f(0.4, 0.7647, 0.996); // RGB: 102 195 154
    glBegin(GL_TRIANGLE_FAN);
        glVertex3i(  0,   0, 0);
        glVertex3i(300,   0, 0);
        glVertex3i(300, 400, 0);
        glVertex3i(  0, 400, 0);
    glEnd();

    // Desenha jogador
    glColor3f(1.0, 0.0, 0.0); // RGB: 102 195 154
    glBegin(GL_TRIANGLE_FAN);
        glVertex3i(jogador.posicao.x,                             jogador.posicao.y - jogador.dimensoes.altura,jogador.posicao.z);
        glVertex3i(jogador.posicao.x + jogador.dimensoes.largura, jogador.posicao.y - jogador.dimensoes.altura,jogador.posicao.z);
        glVertex3i(jogador.posicao.x + jogador.dimensoes.largura, jogador.posicao.y,                           jogador.posicao.z);
        glVertex3i(jogador.posicao.x,                             jogador.posicao.y,                           jogador.posicao.z);
    glEnd();

    // Desenha projeteis do jogador
    glColor3f(0.0, 0.0, 0.0);
    Projetil* projetilAtual = listaProjeteisDoJogador;
    while(projetilAtual != NULL){
        glBegin(GL_TRIANGLE_FAN);
            glVertex3i(projetilAtual->posicao.x,                                    projetilAtual->posicao.y - projetilAtual->dimensoes.altura, projetilAtual->posicao.z);
            glVertex3i(projetilAtual->posicao.x + projetilAtual->dimensoes.largura, projetilAtual->posicao.y - projetilAtual->dimensoes.altura, projetilAtual->posicao.z);
            glVertex3i(projetilAtual->posicao.x + projetilAtual->dimensoes.largura, projetilAtual->posicao.y,                                   projetilAtual->posicao.z);
            glVertex3i(projetilAtual->posicao.x,                                    projetilAtual->posicao.y,                                   projetilAtual->posicao.z);
        glEnd();
        projetilAtual = projetilAtual->proximoProjetil;
    }

    // Desenha Inimigos
    Inimigo* inimigos = inimigo_getLista();
    for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
        if(inimigos[i].pontosDeVida > 0){
            glColor3f(0.5, 0.0, 0.0); // RGB: 102 195 154
            glBegin(GL_TRIANGLE_FAN);
                glVertex3i(inimigos[i].posicao.x,                                   inimigos[i].posicao.y - inimigos[i].dimensoes.altura,   inimigos[i].posicao.z);
                glVertex3i(inimigos[i].posicao.x + inimigos[i].dimensoes.largura,   inimigos[i].posicao.y - inimigos[i].dimensoes.altura,   inimigos[i].posicao.z);
                glVertex3i(inimigos[i].posicao.x + inimigos[i].dimensoes.largura,   inimigos[i].posicao.y,                                  inimigos[i].posicao.z);
                glVertex3i(inimigos[i].posicao.x,                                   inimigos[i].posicao.y,                                  inimigos[i].posicao.z);
            glEnd();
        }
    }

    // Desenha projeteis dos inimigos
    ProjetilInimigo* projeteisInimigos = projeteisDosInimigos_getLista();
    for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
        if(projeteisInimigos[i].valido){
            glColor3f(0.5, 0.0, 0.0);
            glBegin(GL_TRIANGLE_FAN);
                glVertex3i(projeteisInimigos[i].posicao.x,                                          projeteisInimigos[i].posicao.y - projeteisInimigos[i].dimensoes.altura, projeteisInimigos[i].posicao.z);
                glVertex3i(projeteisInimigos[i].posicao.x + projeteisInimigos[i].dimensoes.largura, projeteisInimigos[i].posicao.y - projeteisInimigos[i].dimensoes.altura, projeteisInimigos[i].posicao.z);
                glVertex3i(projeteisInimigos[i].posicao.x + projeteisInimigos[i].dimensoes.largura, projeteisInimigos[i].posicao.y,                                         projeteisInimigos[i].posicao.z);
                glVertex3i(projeteisInimigos[i].posicao.x,                                          projeteisInimigos[i].posicao.y,                                         projeteisInimigos[i].posicao.z);
            glEnd();
        }
    }
    
}

void fimDeJogo_desenhaCena(){
	
	glColor3f(1, 0.7647, 0.996); 
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(  0,   0, 0);
        glVertex3f(300,   0, 0);
        glVertex3f(300, 400, 0);
        glVertex3f(  0, 400, 0);
    glEnd();
}

void jogo_inicializarInimigos(){
    unsigned int x = 120; // Valor x do inimigo mais no topo
    unsigned int y = 350; // Valor y do inimigo mais no topo
    unsigned int linhaInimigos = 30; // Espaçamento entre as fileiras dos inimigos
    unsigned int colunaInimigos = 30; // Espaçamento do eixo x dos inimigos
    unsigned int alinhamento = 15; //  Deixa inimigos alinhados
    unsigned int i = 0; 
    unsigned int qtInimigos, pos_x, pos_y, auxInimigo;
    Inimigo* inimigo = inimigo_getLista();
    for(qtInimigos = 2; qtInimigos <= 5; qtInimigos++, x -= alinhamento, y -= linhaInimigos){
        for(auxInimigo = qtInimigos, pos_x = x, pos_y = y; auxInimigo > 0; auxInimigo--, pos_x += colunaInimigos, i++){
		    inimigo[i].dimensoes.largura = 15;
		    inimigo[i].dimensoes.altura = 15;
		    inimigo[i].posicao.x = pos_x;
		    inimigo[i].posicao.y = pos_y;
		    inimigo[i].posicao.z = 5;
		    inimigo[i].velocidade = 20;
		    inimigo[i].pontosDeVida = 6 - qtInimigos;
   		}
    }

}

void jogo_limparProjeteisInimigos(){
    ProjetilInimigo* listaProjeteisInimigos = projeteisDosInimigos_getLista();
    for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
        listaProjeteisInimigos[i].valido = false;
    }
}

void jogo_reiniciarJogo(Jogador* jogador){
    jogo_inicializarInimigos();
    jogo_limparProjeteisInimigos();

    // Iniciando jogador (valores nao definitivos)
    jogador->dimensoes.largura = 30;
    jogador->dimensoes.altura = 30;
    jogador->posicao.x = 150 - jogador->dimensoes.largura / 2;
    jogador->posicao.y = 40;
    jogador->posicao.z = 5;
    jogador->pontosDeVida = 5;
    jogador->pontosDeAtaque = 0;

    projeteisDoJogador_esvaziarLista();
    
}
