#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "fila.h"
#include "disco.h"
#include "computador.h"
#include "processo.h"

struct comp{
	int id;
	Disco *d1;
	Disco *d2;
	Fila *f;
	Fila *fd1;
	Fila *fd2;
	Rede *r;
};

Comp* comp_cria(int i){
	Comp *c = (Comp*)malloc(sizeof(Comp));
	c->d1 = disco_cria(0);
	c->d2 = disco_cria(1);
	c->f = fila_cria();
	c->fd1 = fila_cria();
	c->fd2 = fila_cria();
	c->id = i;
	return c;
}

int comp_fila_vazia(Comp *c){
	return fila_vazia(c->f);
}

int comp_fila_disco_vazia(Comp *c, int id){
	if(id == 0) return fila_vazia(c->fd1);
	else return fila_vazia(c->fd2);
}

void comp_insere_fila_rede(Comp *c, Processo *p){
	inserir_fila_rede(c->r, p);
}

void comp_insere_fila_rede_ordenado(Comp *c, Processo *p){
	inserir_fila_rede_ordenado(c->r, p);
}

void comp_insere_filaD1(Comp *c, Processo *p){
	fila_inseri_fim(c->fd1, p);
}

void comp_insere_filaD2(Comp *c, Processo *p){
	fila_inseri_fim(c->fd2, p);
}

void comp_fila_insere(Comp *c, Processo *p){
	fila_inseri_fim(c->f, p);
}

Processo* retira_processo_filaD1(Comp *c){
	return fila_retira_ini(c->fd1);
}

Processo* retira_processo_filaD2(Comp *c){
	return fila_retira_ini(c->fd2);
}

Processo* retira_processo_fila_rede(Comp *c){
	return retira_fila_rede(c->r);
}

Processo* retira_processo_fila(Comp *c){
	return fila_retira_ini(c->f);
}

Processo* retira_menor_demanda_cpu(Comp *c){
	int menor = INT_MAX;
	int id;
	Processo *p, *p2;
	Fila *f = fila_cria();
	int i = 0;
	while(!comp_fila_vazia(c)){
		p = retira_processo_fila(c);
		if(menor > getCpu(p)){
			menor = getCpu(p);
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
			comp_fila_insere(c, p);
		if(i == 1) i--;
	}
	fila_libera(f);
	return p2;
}

Processo* retira_menor_demanda_disco(Comp *c, int idDisco){
	int menor = INT_MAX;
	int id;
	Processo *p, *p2;
	Fila *f = fila_cria();
	int i = 0;
	while(!comp_fila_disco_vazia(c, idDisco)){
		if(idDisco == 0) p = retira_processo_filaD1(c);
		else p = retira_processo_filaD2(c);
		if(menor > getDisco(p)){
			menor = getDisco(p);
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
		else if(i == 0){
			if(idDisco == 0) comp_insere_filaD1(c, p);
			else comp_insere_filaD2(c, p);
		}
		if(i == 1) i--;
	}
	fila_libera(f);
	return p2;
}

void comp_imprimi_fila(Comp *c){
	fila_imprimir(c->f);
}

void comp_imprimi_fila_discos(Comp *c){
	fila_imprimir(c->fd1);
	fila_imprimir(c->fd2);
}

void setRede(Comp *c, Rede *rede){
	c->r = rede;
}

void libera_comp(Comp *c, int i){
	fila_libera(c->f);
	fila_libera(c->fd1);
	fila_libera(c->fd2);
	disco_libera(c->d1);
	disco_libera(c->d2);
	//libera_cpu(c->cpu);
	if(i == 0)libera_rede(c->r);
	free(c);
}

int getIdComp(Comp *c){
	return c->id;
}

char getDadoCompD1(Comp *c){
	return getDadoDisco(c->d1);
}

char getDadoCompD2(Comp *c){
	return getDadoDisco(c->d2);
}

int getIdDiscoD1(Comp *c){
	return getIdDisco(c->d1);
}

int getIdDiscoD2(Comp *c){
	return getIdDisco(c->d2);
}

/*Fila* getFilaComp(Comp *c){
	return c->f;
}*/

Rede* getRedeComp(Comp *c){
	return c->r;
}
