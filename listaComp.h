#include "computador.h"

typedef struct listaComp ListaComp;

ListaComp* lista_comp_cria();
ListaComp* lista_comp_insere(ListaComp *lc, int id);
void adicionar_rede_lista(ListaComp *l, Rede *r);
int lista_comp_vazia(ListaComp* l);
void lista_comp_libera(ListaComp *lc);
Comp* busca_comp(ListaComp *lc, int x);
void setProx(ListaComp *l, ListaComp *p);
ListaComp* getProx(ListaComp *l);
