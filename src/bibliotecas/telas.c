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
            glColor3f(0.5, 0.0, 0.0); // RGB: 102 195 154
            glBegin(GL_TRIANGLE_FAN);
                glVertex3i(projeteisInimigos[i].posicao.x,                                          projeteisInimigos[i].posicao.y - projeteisInimigos[i].dimensoes.altura, projeteisInimigos[i].posicao.z);
                glVertex3i(projeteisInimigos[i].posicao.x + projeteisInimigos[i].dimensoes.largura, projeteisInimigos[i].posicao.y - projeteisInimigos[i].dimensoes.altura, projeteisInimigos[i].posicao.z);
                glVertex3i(projeteisInimigos[i].posicao.x + projeteisInimigos[i].dimensoes.largura, projeteisInimigos[i].posicao.y,                                         projeteisInimigos[i].posicao.z);
                glVertex3i(projeteisInimigos[i].posicao.x,                                          projeteisInimigos[i].posicao.y,                                         projeteisInimigos[i].posicao.z);
            glEnd();
        }
    }
    
}

void fimDeJogo_desenhaCena(){}

void jogo_inicializarInimigos(){
    Inimigo *inimigos = inimigo_getLista();
    ProjetilInimigo* projeteisInimigos = projeteisDosInimigos_getLista();
    int dimensoes = 15;
    int y = 350, x = 10;

    // Iniciando inimigos (valores nao definitivas)
    for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++, x += 5 + dimensoes){
        projeteisInimigos[i].valido = false;
        inimigos[i].dimensoes.largura = dimensoes;
        inimigos[i].dimensoes.altura = dimensoes;
        inimigos[i].pontosDeVida = 1;
        inimigos[i].posicao.y = y;
        inimigos[i].posicao.x = x;
        inimigos[i].posicao.z = 5;
    }

}

void jogo_reiniciarJogo(Jogador* jogador){
    jogo_inicializarInimigos();

    // Iniciando jogador (valores nao definitivos)
    jogador->dimensoes.largura = 30;
    jogador->dimensoes.altura = 30;
    jogador->posicao.x = 150 - jogador->dimensoes.largura / 2;
    jogador->posicao.y = 40;
    jogador->posicao.z = 5;
    jogador->pontosDeVida = 5;

    projeteisDoJogador_esvaziarLista();
}
