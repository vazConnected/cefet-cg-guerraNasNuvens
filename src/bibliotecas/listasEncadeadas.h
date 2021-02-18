#ifndef _LISTAS_ENCADESDAS_H
#define _LISTAS_ENCADEADAS_H

#include "estruturas.h"

bool inimigo_listaVazia();
void inimigo_adicionar(Inimigo *inimigo);
void inimigo_remover(unsigned int indice);

bool projeteisInimigo_listaVazia();
void projeteisInimigo_adicionar(Projetil *projetil);
void projeteisInimigo_remover(unsigned int indice);

bool projeteisJogador_listaVazia();
void projeteisJogador_adicionar(Projetil *projetil);
void projeteisJogador_remover(unsigned int indice);

#endif // _LISTAS_ENCADEADAS_H