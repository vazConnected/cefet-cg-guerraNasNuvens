#ifndef _FISICAS_H_
#define _FISICAS_H_

#include <stdbool.h>

#include "comuns.h"
#include "listas.h"

void atualizarPosicaoJogador(Jogador* jogador, bool* teclaEspecialApertada, int margemDaTela);
void atualizarProjeteisJogador(Jogador* jogador);

void atualizarPosicaoDosInimigos();
void atualizarProjeteisInimigos();

void inimigoAtingido(Jogador* jogador, Inimigo* inimigo);
void jogadorAtingido(Jogador* jogador);

#endif // _FISICAS_H_
