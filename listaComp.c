#include <stdio.h>
#include <stdlib.h>
#include "listaComp.h"

struct listaComp{
	Comp *c;
	struct listaComp *prox;
};

ListaComp* lista_comp_cria(){
	return NULL;
}

ListaComp* lista_comp_insere(ListaComp *lc, int id){
	ListaComp *n = (ListaComp*)malloc(sizeof(ListaComp));
	n->c = comp_cria(id);
	n->prox = lc;
	return n;
}

void adicionar_rede_lista(ListaComp *l, Rede *r){
	setRede(l->c, r);
}

int lista_comp_vazia(ListaComp* l){
	return l == NULL;
}

void lista_comp_libera(ListaComp *lc){
	int i = 0;
	while(!lista_comp_vazia(lc)){
		ListaComp *aux = lc;
		lc = lc->prox;
		libera_comp(aux->c, i);
		free(aux);
		i++;
	}
}

Comp* busca_comp(ListaComp *lc, int x){
	ListaComp *aux = lc;
	while(!lista_comp_vazia(aux)){
		if(getIdComp(aux->c) == x)
			return aux->c;
		aux = aux->prox;
	}
	return NULL;
}

void setProx(ListaComp *l, ListaComp *p){
	l->prox = p;	
}

ListaComp* getProx(ListaComp *l){
	return l->prox;
}
