#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct lista{
	Processo *p;
	struct lista *prox;
	struct lista *ant;
};

Lista* lista_cria(){
	return NULL;
}

int lista_vazia(Lista *l){
	return l == NULL;
}

Lista* lista_insere_ini(Lista *l, Processo *processo){
	Lista *n = (Lista*)malloc(sizeof(Lista));
	n->p = processo;
	if(!lista_vazia(l)) l->ant = n;
	n->prox = l;
	n->ant = lista_cria();
	return n;
}

Lista* lista_insere_fim(Lista *l, Processo *processo){
	Lista *n = (Lista*)malloc(sizeof(Lista));
	l->prox = n;
	n->ant = l;
	n->prox = lista_cria();
	n->p = processo;
	return n;
}

Lista* lista_retira_ini(Lista *l){
	if(!lista_vazia(l)){
		Lista *aux = l;
		l = l->prox;
		free(aux);
		if(!lista_vazia(l))l->ant = lista_cria();
	}
	return l;
}

Lista* lista_retira_fim(Lista *l){
	Lista *ant = lista_cria(), *atual = l;
	while(!lista_vazia(atual)){
		ant = atual;
		atual = atual->prox;
	}
	if(lista_vazia(ant)) return l;
	else{
		Lista *aux = ant;
		ant = ant->ant;
		if(!lista_vazia(ant)) ant->prox = atual;
		free(aux);
		return l;
	}
}

int getInicioLista(Lista *l){
	return getTempoInicial(l->p);
}

int verificar_maior(Lista *l, Processo *p){
	if(getTempoInicial(l->p) < getTempoInicial(p)) return 1;
	else return 0;
}

Lista* lista_inserir_ordenado(Lista *l, Processo *p){
	Lista *aux = l, *ant = lista_cria();
	while(!lista_vazia(aux)){
		if(getInicioLista(aux) < getTempoInicial(p)){
			ant = aux;
			aux = aux->prox;
		}
		else break;
	}
	if(lista_vazia(ant)) return lista_insere_ini(aux, p);
	if(!lista_vazia(aux)){
		if(getInicioLista(aux) > getTempoInicial(p)){
			Lista *n = (Lista*)malloc(sizeof(Lista));
			n->p = p;
			n->prox = aux;
			aux->ant = n;
			ant->prox = n;
			n->ant = ant;
			return l;
		}
		if(getInicioLista(aux) == getTempoInicial(p)){
			Lista *n = (Lista*)malloc(sizeof(Lista));
			n->p = p;
			n->prox = aux;
			if(!lista_vazia(aux)) aux->ant = n;
			n->ant = ant;
			ant->prox = n;
			return l;
		}
	}
	/*else if(!lista_vazia(aux) && ){
		Lista *n = (Lista*)malloc(sizeof(Lista));
		n->p = p;
		n->prox = aux;
		if(!lista_vazia(aux)) aux->ant = n;
		n->ant = ant;
		ant->prox = n;
		return l;
	}*/
}

Processo* getProcesso(Lista *l){
	return l->p;
}

void lista_libera(Lista *l){
	while(!lista_vazia(l)){
		Lista *aux = l;
		l = l->prox;
		destroi_processo(aux->p);
		free(aux);
	}
}

void lista_imprimir(Lista *l){
	Lista *aux = l;
	while(!lista_vazia(aux)){
		imprimir_processo(aux->p);
		aux = aux->prox;
	}
}

void lista_imprimir_espera(Lista *l){
	Lista *aux = l;
	while(!lista_vazia(aux)){
		imprimir_processo_espera(aux->p);
		aux = aux->prox;
	}
}
