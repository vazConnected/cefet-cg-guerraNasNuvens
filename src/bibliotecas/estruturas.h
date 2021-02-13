#ifndef _ESTRUTURAS_H_
#define _ESTRUTURAS_H_

typedef struct{
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

typedef struct{
    unsigned int pontosDeVida;
    float velocidade;
    Posicao posicao;
    Dimensoes dimensoes;
} Inimigo;

#endif // _ESTRUTURAS_H_