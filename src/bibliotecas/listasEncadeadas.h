#ifndef _LISTAS_ENCADESDAS_H
#define _LISTAS_ENCADEADAS_H

#include "estruturas.h"

void inicializarListasEncadeadas();

// Lista de Inimigos
bool inimigos_listaVazia();
void inimigos_adicionar(Inimigo inimigo);
void inimigos_remover(unsigned int indice);
Inimigo* inimigos_inicioDaLista();

// Lista de Projeteis do Inimigo
bool projeteisDosInimigos_listaVazia();
void projeteisDosInimigos_adicionar(Projetil projetil);
void projeteisDosInimigos_remover(unsigned int indice);
Projetil* projeteisDosInimigos_inicioDaLista();

// Lista de Projeteis do Jogador
bool projeteisDoJogador_listaVazia();
void projeteisDoJogador_adicionar(Projetil projetil);
void projeteisDoJogador_remover(unsigned int indice);
Projetil* projeteisDoJogador_inicioDaLista();

#endif // _LISTAS_ENCADEADAS_H