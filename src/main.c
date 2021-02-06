/*
 * Trabalho Pratico 1
 * Disciplina: Computacao Grafica
 * 
 * Devs:  Luisa Oliveira;
 *        Pedro Vaz;
 *        Stephanie Fonseca.
 *
 */

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#include <stdio.h>
#include <stdlib.h>

#include "bibliotecas/estruturas.h"

Jogador jogador;
Inimigo *inimigos;

void inicializa();
void callback_desenhaCena();
void callback_redimensiona(int largura, int altura);
void callback_teclaAbaixada(unsigned char tecla, GLint x, GLint y);
void callback_teclaLevantada(unsigned char tecla, GLint x, GLint y);
void callback_teclaEspecialLevantada(unsigned char tecla, GLint x, GLint y);
void callback_teclaEspecialAbaixada(unsigned char tecla, GLint x, GLint y);
void callback_atualizaQuadros();

int main(int argc, char** argv){
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("CG - Galaxian - TP1");

    // Registro de callbacks
    glutDisplayFunc(callback_desenhaCena);
    glutReshapeFunc(callback_redimensiona);
    glutKeyboardFunc(callback_teclaAbaixada);
    glutKeyboardUpFunc(callback_teclaLevantada);
    glutSpecialFunc(callback_teclaEspecialAbaixada);
    glutSpecialUpFunc(callback_teclaEspecialLevantada);

    glutIgnoreKeyRepeat(GLUT_KEY_REPEAT_ON);

    glutTimerFunc(0, callback_atualizaQuadros, 60); // 60 FPS

    inicializa();

    glutMainLoop();

    return 0;
}

