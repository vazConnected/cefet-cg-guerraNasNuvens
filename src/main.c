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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "bibliotecas/comuns.h"
#include "bibliotecas/telas.h"
#include "bibliotecas/listas.h"
#include "bibliotecas/fisicas.h"

bool teclaComumApertada[256]; // Tabela ASCII
bool teclaEspecialApertada[21]; // https://www.opengl.org/resources/libraries/glut/spec3/node54.html

Jogador jogador;

enum telas telaAtual = inicio;
bool jogoPausado = false;

void inicializa(){
    srand(time(NULL));

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND ); 
    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_TEXTURE_2D); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glAlphaFunc(GL_GREATER, 0.5);
    glEnable(GL_ALPHA_TEST);

    inicializarlistas();
    
    
}

void callback_desenhaCena(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    switch(telaAtual){
        case(inicio):
            inicio_desenhaCena();
        break;
        case(jogo):
        
            jogo_desenhaCena(&jogador, projeteisDoJogador_inicioDaLista());
            
            if(jogador.pontosDeVida <= 0){ // Jogador morreu
				telaAtual = fimDeJogo;
			}
            unsigned int inimigosEliminados = 0;
			Inimigo* inimigos = inimigo_getLista();
			for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
				if(inimigos[i].posicao.x == INIMIGO_ELIMINADO){
					inimigosEliminados++;
				}
				if(inimigos[i].posicao.y <= jogador.posicao.y){ // Inimigos chegaram no jogador
					telaAtual = fimDeJogo;
					break;
				}
			}
			if(inimigosEliminados == QUANTIDADE_DE_INIMIGOS){ // Inimigos foram eliminados
                projeteisDoJogador_esvaziarLista();
				jogo_inicializarInimigos();
			}
		break;
        case(fimDeJogo):
            for(long int i=0; i<99999999; i++);// Tempo de explosao do jogador
            fimDeJogo_desenhaCena(&jogador);
        break;
    }
   
    glFlush();
}


void callback_redimensiona(int largura, int altura){
   /*
    * Descricao da tela:
    *   - Razao de proporcao: 3:4
    *   - Area util: (0, 0, -10) a (300, 400, 10)
    */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 300, 0, 400, -10, 10); // left, right, bottom, top, zNear, zFar)

    GLfloat razaoAspectoDaJanela = ((GLfloat)largura)/altura;
    GLfloat razaoAspectoDoJogo = 300.0 / 400.0; // larguraDoJogo / alturaDoJogo

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

    if(tecla == 27){
        exit(0);
    }
    else{
        switch(telaAtual){
            case(inicio):
                if(tecla == 'p' || tecla == 'P'){
                    telaAtual = jogo;
                    jogo_reiniciarJogo(&jogador);
                }
            break;
            case(jogo):
                if(tecla == 'p' || tecla == 'P'){
                    jogoPausado = !jogoPausado;
                }else if(tecla == ' '){
                    Projetil projetil;
                    projetil.dimensoes.altura = 8;
                    projetil.dimensoes.largura = 4;
                    projetil.posicao.x = jogador.posicao.x + jogador.dimensoes.largura / 2 - projetil.dimensoes.largura / 2;
                    projetil.posicao.y = jogador.posicao.y;
                    projetil.posicao.z = 4;
                    projeteisDoJogador_adicionar(projetil);
                }else if(tecla == 'r' || tecla == 'R'){
                    if(jogoPausado){
                        jogoPausado = false;
                    }
                    jogo_reiniciarJogo(&jogador);
                }
            break;
            case(fimDeJogo):
                if(tecla == 'r' || tecla == 'R'|| tecla == 'p' || tecla == 'P'){
                    telaAtual = jogo;
                    jogo_reiniciarJogo(&jogador);
                }
            break;
        }
    }
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
    if(telaAtual == jogo && !jogoPausado){
        atualizarPosicaoJogador(&jogador, teclaEspecialApertada, MARGEM_DA_TELA);
        atualizarProjeteisJogador(&jogador);
        atualizarPosicaoDosInimigos();
        atualizarProjeteisInimigos();
    }
    
    glutPostRedisplay();
    glutTimerFunc(periodo, callback_atualizaQuadros, periodo);
}


int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(300, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Guerra nas Nuvens");

    // Registro de callbacks
    glutDisplayFunc(callback_desenhaCena);
    glutReshapeFunc(callback_redimensiona);
    glutKeyboardFunc(callback_teclaAbaixada);
    glutKeyboardUpFunc(callback_teclaLevantada);
    glutSpecialFunc(callback_teclaEspecialAbaixada);
    glutSpecialUpFunc(callback_teclaEspecialLevantada);

    glutIgnoreKeyRepeat(GLUT_KEY_REPEAT_ON);

    glutTimerFunc(0, callback_atualizaQuadros, 30);

    inicializa();

    glutMainLoop();

    return 0;
}
