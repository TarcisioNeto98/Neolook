#include "processo.h"
typedef struct rede Rede;

Rede* cria_rede();
int rede_vazia(Rede *r);
void inserir_fila_rede(Rede *r, Processo *p);
void inserir_fila_rede_ordenado(Rede *r, Processo *p);
Processo* retira_fila_rede(Rede *r);
Processo* retira_menor_demanda_rede(Rede *c);
int rede_cheia(Rede *r);
void rede_push(Rede *r, char c);
char rede_pop(Rede *r);
void libera_rede(Rede *r);
void imprimir_rede(Rede *r);
