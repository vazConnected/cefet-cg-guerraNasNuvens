#ifndef _ESTRUTURAS_H_
#define _ESTRUTURAS_H_

#include <GL/freeglut.h>

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

typedef struct inimigo{
    unsigned int pontosDeVida;
    float velocidade;
    Posicao posicao;
    Dimensoes dimensoes;
    struct inimigo* proximoInimigo;
} Inimigo;

#endif // _ESTRUTURAS_H_