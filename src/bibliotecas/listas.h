#ifndef _LISTAS_H_
#define _LISTAS_H_

#include "comuns.h"

#define QUANTIDADE_DE_INIMIGOS 14

void inicializarlistas();

// Lista de Projeteis do Jogador
bool projeteisDoJogador_listaVazia();
void projeteisDoJogador_adicionar(Projetil projetil);
void projeteisDoJogador_remover(unsigned int indice);
void projeteisDoJogador_esvaziarLista();
Projetil* projeteisDoJogador_inicioDaLista();

// Inimigo
Inimigo* inimigo_getLista();
ProjetilInimigo* projeteisDosInimigos_getLista();

#endif // _LISTAS_H_