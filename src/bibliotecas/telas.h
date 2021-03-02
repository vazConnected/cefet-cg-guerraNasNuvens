#ifndef _TELAS_H_
#define _TELAS_H_

#define MARGEM_DA_TELA 10

GLuint carregaTextura(const char* arquivo);
void inicio_desenhaCena();
void jogo_desenhaCena(Jogador* jogador, Projetil* listaProjeteisJogador);
void fimDeJogo_desenhaCena(Jogador* jogador);

void jogo_inicializarInimigos();
void jogo_reiniciarJogo(Jogador* jogador);

#endif // _TELAS_H_


