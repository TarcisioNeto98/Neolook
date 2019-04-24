#include "processo.h"

typedef struct fila Fila;

Fila* fila_cria();
int fila_vazia(Fila *f);
void fila_inseri_fim(Fila *f, Processo *p);
void fila_inseri_ordenado(Fila *f, Processo *p);
Processo* fila_retira_ini(Fila *f);
void fila_libera(Fila *f);
void fila_imprimir(Fila *f);
void fila_imprimir_espera(Fila *f);
