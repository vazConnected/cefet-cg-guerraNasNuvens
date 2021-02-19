#ifndef _FISICAS_H_
#define _FISICAS_H_

#include "estruturas.h"

void atualizarPosicaoJogador(Jogador *jogador, bool* teclaEspecialApertada, int margemDaTela);
void atualizarProjeteisInimigo(Projetil* inicioListaProjeteisInimigo, bool(*listaVazia)(void), void(*remover)(unsigned int) );
void atualizarProjeteisJogador(Projetil* inicioListaProjeteisJogador, bool(*listaVazia)(void), void(*remover)(unsigned int) );

#endif // _FISICAS_H_