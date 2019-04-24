#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "rede.h"
#include "processo.h"

typedef struct comp Comp;
Comp* comp_cria(int i);
int comp_fila_vazia(Comp *c);
int comp_fila_disco_vazia(Comp *c, int id);
void comp_insere_fila_rede(Comp *c, Processo *p);
void comp_insere_fila_rede_ordenado(Comp *c, Processo *p);
void comp_insere_filaD1(Comp *c, Processo *p);
void comp_insere_filaD2(Comp *c, Processo *p);
void comp_insere_fila(Comp *c, Processo *p);
Processo* retira_processo_filaD1(Comp *c);
Processo* retira_processo_filaD2(Comp *c);
Processo* retira_processo_fila_rede(Comp *c);
Processo* retira_processo_fila(Comp *c);
Processo* retira_menor_demanda_cpu(Comp *c);
Processo* retira_menor_demanda_disco(Comp *c, int idDisco);
//Processo* retira_menor_demanda_rede(Comp *c);
void comp_imprimi_fila(Comp *c);
void comp_imprimi_fila_discos(Comp *c);
void setRede(Comp *c, Rede *rede);
void libera_comp(Comp *c, int i);
int getIdComp(Comp *c);
char getDadoCompD1(Comp *c);
char getDadoCompD2(Comp *c);
int getIdDiscoD1(Comp *c);
int getIdDiscoD2(Comp *c);
//Fila* getFilaComp(Comp *c);
Rede* getRedeComp(Comp *c);
