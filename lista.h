#include "processo.h"

typedef struct lista Lista;

Lista* lista_cria();
int lista_vazia(Lista *l);
Lista* lista_insere_ini(Lista *l, Processo *processo);
Lista* lista_insere_fim(Lista *l, Processo *processo);
Lista* lista_retira_ini(Lista *l);
Lista* lista_retira_fim(Lista *l);
int getInicioLista(Lista *l);
int verificar_maior(Lista *l, Processo *p);
Lista* lista_inserir_ordenado(Lista *l, Processo *p);
Processo* getProcesso(Lista *l);
void lista_libera(Lista *l);
void lista_imprimir(Lista *l);
void lista_imprimir_espera(Lista *l);
