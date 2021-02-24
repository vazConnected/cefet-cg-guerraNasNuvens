#ifndef _FISICAS_H_
#define _FISICAS_H_

#include <stdbool.h>

#include "comuns.h"
#include "listas.h"

void atualizarPosicaoJogador(Jogador *jogador, bool* teclaEspecialApertada, int margemDaTela);
void atualizarProjeteisJogador();

void atualizarPosicaoDosInimigos();
void atualizarProjeteisInimigos();
/*
bool inimigoAtingido(Inimigo inimigo);
bool jogadorAtingido();*/

#endif // _FISICAS_H_