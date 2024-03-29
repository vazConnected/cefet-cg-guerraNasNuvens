#ifndef _COMUNS_H_
#define _COMUNS_H_

#include <stdbool.h>

#include <GL/freeglut.h>

#define INIMIGO_ELIMINADO 400

enum telas {inicio = 1, jogo, fimDeJogo};

typedef struct{ // Topo superior esquerdo
    GLint x;
    GLint y;
    GLint z;
} Posicao;

typedef struct{
    GLint altura;
    GLint largura;
    GLint profundidade;
} Dimensoes;

typedef struct{
    unsigned int pontosDeVida;
    unsigned int pontosDeAtaque;
    Posicao posicao;
    Dimensoes dimensoes;
} Jogador;

typedef struct projetil{
    Posicao posicao;
    Dimensoes dimensoes;
    struct projetil* proximoProjetil;
} Projetil;

typedef struct projetilInimigo{ 
    bool valido;
    Posicao posicao;
    Dimensoes dimensoes;
} ProjetilInimigo;

typedef struct inimigo{
    unsigned int pontosDeVida, tempoInimigo;
    float velocidade;
    Posicao posicao;
    Dimensoes dimensoes;
} Inimigo;

#endif // _COMUNS_H_
