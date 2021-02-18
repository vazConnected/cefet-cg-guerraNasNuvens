#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "estruturas.h"
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

void jogo_desenhaCena(Jogador* jogador, bool* teclaEspecialApertada, bool* teclaComumApertada){

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
        glVertex3i((*jogador).posicao.x,                                (*jogador).posicao.y - (*jogador).dimensoes.altura,(*jogador).posicao.z);
        glVertex3i((*jogador).posicao.x + (*jogador).dimensoes.largura, (*jogador).posicao.y - (*jogador).dimensoes.altura,(*jogador).posicao.z);
        glVertex3i((*jogador).posicao.x + (*jogador).dimensoes.largura, (*jogador).posicao.y,                              (*jogador).posicao.z);
        glVertex3i((*jogador).posicao.x,                                (*jogador).posicao.y,                              (*jogador).posicao.z);
    glEnd();

    // Desenha inimigos

    
}

void fimDeJogo_desenhaCena(){}

