#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "rede.h"
#include "fila.h"
#define N 10000

struct rede{
	Fila *fRede;
	char v[N];
	int topo;
};

Rede* cria_rede(){
	Rede *r = (Rede*)malloc(sizeof(Rede));
	r->topo = 0;
	r->fRede = fila_cria();
	return r;
}

int rede_vazia(Rede *r){
	return r->topo == 0;
}

int fila_rede_vazia(Rede *r){
	return fila_vazia(r->fRede);
}

int rede_cheia(Rede *r){
	return r->topo == N;
}

void inserir_fila_rede(Rede *r, Processo *p){
	fila_inseri_fim(r->fRede, p);
}

void inserir_fila_rede_ordenado(Rede *r, Processo *p){
	fila_inseri_ordenado(r->fRede, p);
}

Processo* retira_fila_rede(Rede *r){
	return fila_retira_ini(r->fRede);
}

Processo* retira_menor_demanda_rede(Rede *c){
	int menor = INT_MAX;
	int id;
	Processo *p, *p2;
	Fila *f = fila_cria();
	int i = 0;
	while(!fila_rede_vazia(c)){
		p = retira_fila_rede(c);
		if(menor > getRede(p)){
			menor = getRede(p);
			id = getIdProcesso(p);
		}
		fila_inseri_fim(f, p);
	}
	while(!fila_vazia(f)){
		p = fila_retira_ini(f);
		if(getIdProcesso(p) == id && i == 0){
			p2 = p;
			i++;
		}
		else if(i == 0)
			inserir_fila_rede(c, p);
		if(i == 1) i--;
	}
	fila_libera(f);
	return p2;
}

void rede_push(Rede *r, char c){
	if(rede_cheia(r)){
		printf("Rede Cheia!");
		exit(1);
	}
	r->v[r->topo] = c;
	r->topo++;
}

char rede_pop(Rede *r){
	if(rede_vazia(r)){
		printf("Rede Vazia");
		exit(1);
	}
	char c = r->v[r->topo-1];
	r->topo--;
	return c;
}

void libera_rede(Rede *r){
	fila_libera(r->fRede);
	free(r);
}

void imprimir_rede(Rede *r){
	Rede *r2 = cria_rede();
	while(!rede_vazia(r)){
		char c = rede_pop(r);
		printf("%c\n", c);
		rede_push(r2, c);
	}
	while(!rede_vazia(r2))
		rede_push(r, rede_pop(r2));
	libera_rede(r2);
}
