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
#include <stdbool.h>
#include <math.h>

#include "bibliotecas/estruturas.h"

Dimensoes dimensoesDoJogo;

bool teclaComumApertada[256]; // Tabela ASCII
bool teclaEspecialApertada[21]; // https://www.opengl.org/resources/libraries/glut/spec3/node54.html

Jogador jogador;
Inimigo *inimigos;

void inicializa(){
    glClearColor(0.0, 0.0, 0.0, 1);

    glEnable(GL_DEPTH_TEST); // Habilita profundidade (z)
    glEnable(GL_TEXTURE_2D); // Habilita texturas
    glEnable(GL_BLEND ); // Habilita transparencia

    dimensoesDoJogo.altura = 400;
    dimensoesDoJogo.largura = 300;
    dimensoesDoJogo.profundidade = 10;

    // Mapear spritesheet
    // Carregar texturas

    // Definir jogador
    // Definir inimigo

}

void callback_desenhaCena(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.4, 0.7647, 0.996); // RGB: 102 195 154
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(  0,   0, 0);
        glVertex3f(300,   0, 0);
        glVertex3f(300, 400, 0);
        glVertex3f(  0, 400, 0);
    glEnd();

    glFlush();
}

void callback_redimensiona(int largura, int altura){
   /*
    * Descricao da tela:
    *   - Razao de proporcao: 3:4
    *   - Area util: (0, 0, 0) a (300, 400, 10)
    */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, dimensoesDoJogo.largura, 0, dimensoesDoJogo.altura, 0, dimensoesDoJogo.profundidade);

    GLfloat razaoAspectoDaJanela = ((GLfloat)largura)/altura;
    GLfloat razaoAspectoDoJogo = ((GLfloat) dimensoesDoJogo.largura) / dimensoesDoJogo.altura;

    if(razaoAspectoDaJanela == razaoAspectoDoJogo){ // Janela na proporcao adequada
        glViewport(0, 0, largura, altura);
    }else if(razaoAspectoDaJanela < razaoAspectoDoJogo) { // Janela mais fina do que deveria
        GLfloat alturaViewport = largura / razaoAspectoDoJogo;
        GLfloat yViewport = (altura - alturaViewport)/2;
        glViewport(0, yViewport, largura, alturaViewport);
    }else if (razaoAspectoDaJanela > razaoAspectoDoJogo) { // Janela mais larga do que deveria
        GLfloat larguraViewport = ((GLfloat)altura) * razaoAspectoDoJogo;
        GLfloat xViewport = (largura - larguraViewport) / 2;
        glViewport(xViewport, 0, larguraViewport, altura);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void callback_teclaAbaixada(unsigned char tecla, int x, int y){
    teclaComumApertada[tecla] = true;
}
    
void callback_teclaLevantada(unsigned char tecla, int x, int y){
    teclaComumApertada[tecla] = false;
}

void callback_teclaEspecialLevantada(int tecla, int x, int y){
    /*  Tecla               Hex     Dec  Posicao  Intervalos
    *   GLUT_KEY_F1         0x0001  001  00       inicio 1
    *   GLUT_KEY_F2         0x0002  002  01       -
    *   GLUT_KEY_F3         0x0003  003  02       -
    *   GLUT_KEY_F4         0x0004  004  03       -
    *   GLUT_KEY_F5         0x0005  005  04       -
    *   GLUT_KEY_F6         0x0006  006  05       -
    *   GLUT_KEY_F7         0x0007  007  06       -
    *   GLUT_KEY_F8         0x0008  008  07       -
    *   GLUT_KEY_F9         0x0009  009  08       -
    *   GLUT_KEY_F10        0x000A  010  09       -
    *   GLUT_KEY_F11        0x000B  011  10       -
    *   GLUT_KEY_F12        0x000C  012  11       fim 1
    *   GLUT_KEY_LEFT       0x0064  100  12       inicio 2
    *   GLUT_KEY_UP         0x0065  101  13       -
    *   GLUT_KEY_RIGHT      0x0066  102  14       -
    *   GLUT_KEY_DOWN       0x0067  103  15       -
    *   GLUT_KEY_PAGE_UP    0x0068  104  16       -
    *   GLUT_KEY_PAGE_DOWN  0x0069  105  17       -
    *   GLUT_KEY_HOME       0x006A  106  18       -
    *   GLUT_KEY_END        0x006B  107  19       -
    *   GLUT_KEY_INSERT     0x006C  108  20       fim 2
    */

    if(tecla >= 1 && tecla <= 12){
        tecla--;
    }else if(tecla >= 100 && tecla <= 108){
        tecla = tecla - 88;
    }

    teclaEspecialApertada[tecla] = false;
}

void callback_teclaEspecialAbaixada(int tecla, int x, int y){
    /*  Tecla               Hex     Dec  Posicao  Intervalos
    *   GLUT_KEY_F1         0x0001  001  00       inicio 1
    *   GLUT_KEY_F2         0x0002  002  01       -
    *   GLUT_KEY_F3         0x0003  003  02       -
    *   GLUT_KEY_F4         0x0004  004  03       -
    *   GLUT_KEY_F5         0x0005  005  04       -
    *   GLUT_KEY_F6         0x0006  006  05       -
    *   GLUT_KEY_F7         0x0007  007  06       -
    *   GLUT_KEY_F8         0x0008  008  07       -
    *   GLUT_KEY_F9         0x0009  009  08       -
    *   GLUT_KEY_F10        0x000A  010  09       -
    *   GLUT_KEY_F11        0x000B  011  10       -
    *   GLUT_KEY_F12        0x000C  012  11       fim 1
    *   GLUT_KEY_LEFT       0x0064  100  12       inicio 2
    *   GLUT_KEY_UP         0x0065  101  13       -
    *   GLUT_KEY_RIGHT      0x0066  102  14       -
    *   GLUT_KEY_DOWN       0x0067  103  15       -
    *   GLUT_KEY_PAGE_UP    0x0068  104  16       -
    *   GLUT_KEY_PAGE_DOWN  0x0069  105  17       -
    *   GLUT_KEY_HOME       0x006A  106  18       -
    *   GLUT_KEY_END        0x006B  107  19       -
    *   GLUT_KEY_INSERT     0x006C  108  20       fim 2
    */

    if(tecla >= 1 && tecla <= 12){
        tecla--;
    }else if(tecla >= 100 && tecla <= 108){
        tecla = tecla - 88;
    }
    teclaEspecialApertada[tecla] = true;
}

void callback_atualizaQuadros(int periodo){
    glutPostRedisplay();
    glutTimerFunc(periodo, callback_atualizaQuadros, periodo);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(300, 400);
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

    glutTimerFunc(0, callback_atualizaQuadros, 33);

    inicializa();

    glutMainLoop();

    return 0;
}
