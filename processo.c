#include <stdio.h>
#include <stdlib.h>
#include "processo.h"

struct processo{
	int id;
	int idDisco;
	int idComputador;
	int tempoInicial;
	int Dcpu;
	int Ddisco;
	int Drede;
	int Despera;
	char dados;
};

Processo* cria_processo(){
	Processo *p = (Processo*)malloc(sizeof(Processo));
	return p;
}

void inserir_demandas(Processo *p, int *v, int id, int idComp){
	p->id = id;
	p->idComputador = idComp;
	p->tempoInicial = v[0];
	p->Dcpu = v[1];
	p->Ddisco = v[2];
	p->Drede = v[3];
}

int getIdProcesso(Processo *p){
	return p->id;
}

int getTempoInicial(Processo *p){
	return p->tempoInicial;
}

int getCpu(Processo *p){
	return p->Dcpu;
}

int getDisco(Processo *p){
	return p->Ddisco;
}

int getRede(Processo *p){
	return p->Drede;
}

int getEspera(Processo *p){
	return p->Despera;
}

int getIdDiscoUsado(Processo *p){
	return p->idDisco;
}

int getIdComputador(Processo *p){
	return p->idComputador;
}

char getDados(Processo *p){
	return p->dados;
}

void setIdDisco(Processo *p, int id){
	p->idDisco = id;
}

void setDado(Processo *p, char d){
	p->dados = d;
}

void setEspera(Processo *p, int espera){
	p->Despera = espera;
}

void setTempoInicial(Processo *p, int i){
	p->tempoInicial = i;
}

void destroi_processo(Processo *p){
	free(p);
}

void imprimir_processo(Processo *p){
	printf("id: %d\tTempo de execucao: %d\tDemanda de cpu: %d\tDemanda de Disco: %d\tDemanda de rede: %d\tEspera: %d\tDisco: %d\tComputador: %d\n", p->id, p->tempoInicial, p->Dcpu, p->Ddisco, p->Drede, p->Despera, p->idDisco, p->idComputador);
}

void imprimir_processo_espera(Processo *p){
	printf("%d\n", p->Despera);
}
