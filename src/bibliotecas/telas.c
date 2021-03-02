#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "comuns.h"
#include "fisicas.h"

#include "telas.h"

unsigned int tempojogador = 0, tempotela, contfundo=0;

GLuint inicial, painel, final, vida, telajogo[4], nave[2];


GLuint carregaTextura(const char* arquivo) {
    GLuint idTextura = SOIL_load_OGL_texture( arquivo, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y );

    if (idTextura == 0) {
        printf("Erro carregando a textura: '%s'\n", SOIL_last_result());
    }

    return idTextura;
}   


void inicio_desenhaCena(){

    glBindTexture(GL_TEXTURE_2D, inicial);
  
    inicial = carregaTextura("textures/inicial.png");
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(0, 0,  5); //bottom left
        glTexCoord2f(1, 0); glVertex3f( 300, 0,  5); //bottom right
        glTexCoord2f(1, 1); glVertex3f( 300,  400,  5); //up right
        glTexCoord2f(0, 1); glVertex3f( 0,  400,  5); //up left
    glEnd();
    glDisable(GL_TEXTURE_2D);

}


void jogo_desenhaCena(Jogador* jogador, Projetil* listaProjeteisDoJogador){

    // Desenha painel
    
    glBindTexture(GL_TEXTURE_2D, painel);
    painel = carregaTextura("textures/painel.png");
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(0, 0,  5); //bottom left
        glTexCoord2f(1, 0); glVertex3f( 300, 0,  5); //bottom right
        glTexCoord2f(1, 1); glVertex3f( 300,  34,  5); //up right
        glTexCoord2f(0, 1); glVertex3f( 0,  34,  5); //up left
    glEnd();
    glDisable(GL_TEXTURE_2D);
    


    // Desenha vida
    glBindTexture(GL_TEXTURE_2D, vida);
    vida = carregaTextura("textures/vida.png");
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glEnable(GL_TEXTURE_2D);
    for(int i=0, x=0; i<jogador->pontosDeVida; i++, x+=21 ){
        glColor3f(1, 1, 1);
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0); glVertex3f(2+x, 3,  6); //bottom left
            glTexCoord2f(1, 0); glVertex3f( 22+x, 3,  6); //bottom right
            glTexCoord2f(1, 1); glVertex3f( 22+x,  21,  6); //up right
            glTexCoord2f(0, 1); glVertex3f( 2+x,  21,  6); //up left
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);


    // Desenha fundo animado    
    telajogo[0] = carregaTextura("textures/jogo.png");
    telajogo[1] = carregaTextura("textures/jogo2.png");
    telajogo[2] = carregaTextura("textures/jogo3.png");
    telajogo[3] = carregaTextura("textures/jogo4.png");
    telajogo[4] = carregaTextura("textures/jogo5.png");
    if(contfundo<5){
        glBindTexture(GL_TEXTURE_2D, telajogo[contfundo]);
        tempotela++;
            if(tempotela>30){
                contfundo++;
                tempotela=0;
            }
    }
    else{contfundo=0;}
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0); glVertex3f(0, 0,  1); //bottom left
            glTexCoord2f(1, 0); glVertex3f( 300, 0,  1); //bottom right
            glTexCoord2f(1, 1); glVertex3f( 300,  400, 1); //up right
            glTexCoord2f(0, 1); glVertex3f( 0,  400, 1); //up left
        glEnd();
    glDisable(GL_TEXTURE_2D);
    

    // Desenha jogador
    GLuint naveexplosao;
    nave[0] = carregaTextura("textures/nave.png");
    nave[1] = carregaTextura("textures/navefrontal.png");
    naveexplosao = carregaTextura("textures/naveexplosao.png");
     glBindTexture(GL_TEXTURE_2D, nave[0]);
    if(jogador->posicao.z==7){
        glBindTexture(GL_TEXTURE_2D, nave[1]);
        tempojogador++;
            if(tempojogador>5){
                tempojogador=0;
                jogador->posicao.z=6;
            }
    }
    if(jogador->pontosDeVida<1){
        glBindTexture(GL_TEXTURE_2D, naveexplosao);
    }
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);glVertex3i(jogador->posicao.x,                             jogador->posicao.y - jogador->dimensoes.altura,jogador->posicao.z);
        glTexCoord2f(1, 0);glVertex3i(jogador->posicao.x + jogador->dimensoes.largura, jogador->posicao.y - jogador->dimensoes.altura,jogador->posicao.z);
        glTexCoord2f(1, 1);glVertex3i(jogador->posicao.x + jogador->dimensoes.largura, jogador->posicao.y,                           jogador->posicao.z);
        glTexCoord2f(0, 1);glVertex3i(jogador->posicao.x,                             jogador->posicao.y,                           jogador->posicao.z);
    glEnd();
    glDisable(GL_TEXTURE_2D);   
    

    // Desenha projeteis do jogador
    glColor3f(0.55, 0.0, 0.0);
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
    GLuint inimigosTex[4], inimigosDanoTex[3];
    inimigosTex[0] = carregaTextura("textures/verde.png");//inimigo entre 0 e 4 eh verde
    inimigosTex[1] = carregaTextura("textures/amarelo.png");//inimigo entre 5 e 8 eh amarelo
    inimigosTex[2] = carregaTextura("textures/laranja.png");//inimigo entre 9 e 11 eh laranja
    inimigosTex[3] = carregaTextura("textures/rosa.png");//inimigo entre 12 e  13 eh verde
    inimigosDanoTex[0] = carregaTextura("textures/amarelot.png");
    inimigosDanoTex[1] = carregaTextura("textures/laranjat.png");
    inimigosDanoTex[2] = carregaTextura("textures/rosat.png");
    int qtInimigosLinha = 2, posVecTex = 3, proxLinha = 3;
    Inimigo* inimigos = inimigo_getLista(); 
    for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
        if(inimigos[i].pontosDeVida > 0){
            glBindTexture(GL_TEXTURE_2D, inimigosTex[posVecTex]);
            if(inimigos[i].posicao.z==6){
                glBindTexture(GL_TEXTURE_2D, inimigosDanoTex[posVecTex-1]);
                inimigos[i].tempoInimigo++;
                if(inimigos[i].tempoInimigo>10){
                    inimigos[i].tempoInimigo = 0;
                    inimigos[i].posicao.z = 5;
                }
            }
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glEnable(GL_TEXTURE_2D);
            glColor3f(1, 1, 1); 
            glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(0, 0); glVertex3i(inimigos[i].posicao.x,                                   inimigos[i].posicao.y - inimigos[i].dimensoes.altura,   inimigos[i].posicao.z);
                glTexCoord2f(1, 0); glVertex3i(inimigos[i].posicao.x + inimigos[i].dimensoes.largura,   inimigos[i].posicao.y - inimigos[i].dimensoes.altura,   inimigos[i].posicao.z);
                glTexCoord2f(1, 1); glVertex3i(inimigos[i].posicao.x + inimigos[i].dimensoes.largura,   inimigos[i].posicao.y,                                  inimigos[i].posicao.z);
                glTexCoord2f(0, 1); glVertex3i(inimigos[i].posicao.x,                                   inimigos[i].posicao.y,                                  inimigos[i].posicao.z);
            glEnd();
            glDisable(GL_TEXTURE_2D);  
        }
        qtInimigosLinha--;
        if(qtInimigosLinha==0){
            qtInimigosLinha=proxLinha;
            proxLinha++;
            posVecTex--;
        }
        
    }


    // Desenha explosão dos iniigos
    GLuint inimigosExplosaoTex[4];
    inimigosExplosaoTex[0] = carregaTextura("textures/explosaoverde.png");
    inimigosExplosaoTex[1] = carregaTextura("textures/explosaoamarela.png");
    inimigosExplosaoTex[2] = carregaTextura("textures/explosaolaranja.png");
    inimigosExplosaoTex[3] = carregaTextura("textures/explosaorosa.png");
    int qtInimigosLinha2 = 2, posVecTex2 = 3, proxLinha2 = 3;
    inimigos = inimigo_getLista(); 
    for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
        if(inimigos[i].pontosDeVida <= 0 && inimigos[i].posicao.x != INIMIGO_ELIMINADO){
            glBindTexture(GL_TEXTURE_2D, inimigosExplosaoTex[posVecTex2]);
                inimigos[i].tempoInimigo++;
                if(inimigos[i].tempoInimigo>10){
                    inimigos[i].tempoInimigo = 0;
                    inimigos[i].posicao.x = INIMIGO_ELIMINADO;
                }
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glEnable(GL_TEXTURE_2D);
            glColor3f(1, 1, 1); 
            glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(0, 0); glVertex3i(inimigos[i].posicao.x,                                   inimigos[i].posicao.y - inimigos[i].dimensoes.altura,   inimigos[i].posicao.z);
                glTexCoord2f(1, 0); glVertex3i(inimigos[i].posicao.x + inimigos[i].dimensoes.largura,   inimigos[i].posicao.y - inimigos[i].dimensoes.altura,   inimigos[i].posicao.z);
                glTexCoord2f(1, 1); glVertex3i(inimigos[i].posicao.x + inimigos[i].dimensoes.largura,   inimigos[i].posicao.y,                                  inimigos[i].posicao.z);
                glTexCoord2f(0, 1); glVertex3i(inimigos[i].posicao.x,                                   inimigos[i].posicao.y,                                  inimigos[i].posicao.z);
            glEnd();
            glDisable(GL_TEXTURE_2D);  
        }
        qtInimigosLinha2--;
        if(qtInimigosLinha2==0){
            qtInimigosLinha2=proxLinha2;
            proxLinha2++;
            posVecTex2--;
        }
        
    }
   

    // Desenha projeteis dos inimigos
    ProjetilInimigo* projeteisInimigos = projeteisDosInimigos_getLista();
    for(int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++){
        if(projeteisInimigos[i].valido){
            glColor3f(0.702, 0.3, 0.925);
            glBegin(GL_TRIANGLE_FAN);
                glVertex3i(projeteisInimigos[i].posicao.x,                                          projeteisInimigos[i].posicao.y - projeteisInimigos[i].dimensoes.altura, projeteisInimigos[i].posicao.z);
                glVertex3i(projeteisInimigos[i].posicao.x + projeteisInimigos[i].dimensoes.largura, projeteisInimigos[i].posicao.y - projeteisInimigos[i].dimensoes.altura, projeteisInimigos[i].posicao.z);
                glVertex3i(projeteisInimigos[i].posicao.x + projeteisInimigos[i].dimensoes.largura, projeteisInimigos[i].posicao.y,                                         projeteisInimigos[i].posicao.z);
                glVertex3i(projeteisInimigos[i].posicao.x,                                          projeteisInimigos[i].posicao.y,                                         projeteisInimigos[i].posicao.z);
            glEnd();
        }
    }


    //Desenha pontuacao
    GLuint numeros[10];
    numeros[0] = carregaTextura("textures/0.png");
    numeros[1] = carregaTextura("textures/1.png");
    numeros[2] = carregaTextura("textures/2.png");
    numeros[3] = carregaTextura("textures/3.png");
    numeros[4] = carregaTextura("textures/4.png");
    numeros[5] = carregaTextura("textures/5.png");
    numeros[6] = carregaTextura("textures/6.png");
    numeros[7] = carregaTextura("textures/7.png");
    numeros[8] = carregaTextura("textures/8.png");
    numeros[9] = carregaTextura("textures/9.png");
    
    if(jogador->pontosDeAtaque>99999) jogador->pontosDeAtaque = 99999;
    for(int i = jogador->pontosDeAtaque, x=0; i>=1; i/=10, x+=11 ){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, numeros[i%10]);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glColor3f(1, 1, 1);
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0); glVertex3f(289-x, 5,  6); //bottom left
            glTexCoord2f(1, 0); glVertex3f( 299-x, 5,  6); //bottom right
            glTexCoord2f(1, 1); glVertex3f( 299-x,  19,  6); //up right
            glTexCoord2f(0, 1); glVertex3f( 289-x,  19,  6); //up left
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    if(jogador->pontosDeAtaque == 0){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, numeros[0]);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glColor3f(1, 1, 1);
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0); glVertex3f(289, 5,  6); //bottom left
            glTexCoord2f(1, 0); glVertex3f( 299, 5,  6); //bottom right
            glTexCoord2f(1, 1); glVertex3f( 299,  19,  6); //up right
            glTexCoord2f(0, 1); glVertex3f( 289,  19,  6); //up left
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    
}


void fimDeJogo_desenhaCena(Jogador* jogador){

    glBindTexture(GL_TEXTURE_2D, final);
  
    final = carregaTextura("textures/final.png");
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(0, 0,  5); //bottom left
        glTexCoord2f(1, 0); glVertex3f( 300, 0,  5); //bottom right
        glTexCoord2f(1, 1); glVertex3f( 300,  400,  5); //up right
        glTexCoord2f(0, 1); glVertex3f( 0,  400,  5); //up left
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Desenha pontuacao
    GLuint numeros[10];
    numeros[0] = carregaTextura("textures/0.png");
    numeros[1] = carregaTextura("textures/1.png");
    numeros[2] = carregaTextura("textures/2.png");
    numeros[3] = carregaTextura("textures/3.png");
    numeros[4] = carregaTextura("textures/4.png");
    numeros[5] = carregaTextura("textures/5.png");
    numeros[6] = carregaTextura("textures/6.png");
    numeros[7] = carregaTextura("textures/7.png");
    numeros[8] = carregaTextura("textures/8.png");
    numeros[9] = carregaTextura("textures/9.png");
    int posx = 160-300/jogador->pontosDeAtaque;
    if(jogador->pontosDeAtaque>99999) jogador->pontosDeAtaque = 99999;
    for(int i = jogador->pontosDeAtaque, x=0; i>=1; i/=10, x+=21 ){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, numeros[i%10]);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glColor3f(1, 1, 1);
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0); glVertex3f(posx-x, 188,  6); //bottom left
            glTexCoord2f(1, 0); glVertex3f( posx + 20 - x, 188,  6); //bottom right
            glTexCoord2f(1, 1); glVertex3f( posx + 20 -x,  212,  6); //up right
            glTexCoord2f(0, 1); glVertex3f( posx - x,  212,  6); //up left
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    if(jogador->pontosDeAtaque == 0){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, numeros[0]);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glColor3f(1, 1, 1);
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0); glVertex3f(289, 5,  6); //bottom left
            glTexCoord2f(1, 0); glVertex3f( 299, 5,  6); //bottom right
            glTexCoord2f(1, 1); glVertex3f( 299,  19,  6); //up right
            glTexCoord2f(0, 1); glVertex3f( 289,  19,  6); //up left
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    

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
		    inimigo[i].dimensoes.largura = 16;
		    inimigo[i].dimensoes.altura = 15;
		    inimigo[i].posicao.x = pos_x;
		    inimigo[i].posicao.y = pos_y;
		    inimigo[i].posicao.z = 5;
		    inimigo[i].velocidade = 20;
		    inimigo[i].pontosDeVida = 6 - qtInimigos;
            inimigo[i].tempoInimigo = 0;
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
    jogador->dimensoes.largura = 25;
    jogador->dimensoes.altura = 30;
    jogador->posicao.x = 150 - jogador->dimensoes.largura / 2;
    jogador->posicao.y = 64;
    jogador->posicao.z = 6;
    jogador->pontosDeVida = 5;
    jogador->pontosDeAtaque = 0;
    projeteisDoJogador_esvaziarLista();
    
}
