#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rede.h"
#include "disco.h"
#include "computador.h"
#include "listaComp.h"
#include "processo.h"
#include "fila.h"
#include "neolook.h"
#include "lista.h"

static int escalonador_fcfs(char *s){
	char c[4] = "FCFS";
	int i = 0;
	while(i < 4){
		if(s[i] != c[i])
			return 0;
		i++;
	}
	return 1;
}

static int escalonador_sjf(char *s){
	char c[3] = "SJF";
	int i = 0;
	while(i < 3){
		if(s[i] != c[i])
			return 0;
		i++;
	}
	return 1;
}

static void fila_cpu(Comp *c, int n){
	Fila *aux = fila_cria();
	Processo *p;
	int ant = 0, i = 0;
	while(!comp_fila_vazia(c)){
		if(n) p = retira_processo_fila(c);
		else p = retira_menor_demanda_cpu(c);
		if(i == 0){
			setEspera(p, 0);
			ant = getTempoInicial(p)+getCpu(p)+getEspera(p);
			setTempoInicial(p, (getTempoInicial(p)+getCpu(p)+getEspera(p)));
		}
		/*if(getIdProcesso(p) == 0 && n == 1){
			setEspera(p, 0);
			ant = getTempoInicial(p)+getCpu(p)+getEspera(p);
			setTempoInicial(p, (getTempoInicial(p)+getCpu(p)+getEspera(p)));
		}*/
		else{
			int espera = ant-getTempoInicial(p);
			if(espera >= 0) setEspera(p, espera);
			else setEspera(p, 0);
			ant = getTempoInicial(p)+getCpu(p)+getEspera(p);
			setTempoInicial(p, (getTempoInicial(p)+getCpu(p)+getEspera(p)));
		}
		i++;
		fila_inseri_fim(aux, p);
	}
	while(!fila_vazia(aux)){
		int prob = (rand()%2);
		Processo *p2 = fila_retira_ini(aux);
		if(prob == 0){
			setIdDisco(p2, 0);
			comp_insere_filaD1(c, p2);
		}
		else{
			setIdDisco(p2, 1);
			comp_insere_filaD2(c, p2);
		}
	}
}

static void fila_disco_auxiliar(Comp *c, int n, int idDisco){
	Fila *aux = fila_cria();
	Processo *p;
	int ant = 0, i = 0;
	while(!comp_fila_disco_vazia(c, idDisco)){
		if(n){
			if(idDisco == 0) p = retira_processo_filaD1(c);
			else p = retira_processo_filaD2(c);
		}
		else p = retira_menor_demanda_disco(c, idDisco);
		if(i == 0){
			int x = getEspera(p);
			setEspera(p, 0);
			ant = getTempoInicial(p)+getDisco(p)+getEspera(p);
			setTempoInicial(p, (getTempoInicial(p)+getDisco(p)+getEspera(p)));
			setEspera(p, x);
		}
		else{
			int espera = ant-getTempoInicial(p);
			int esperaAnt = getEspera(p);
			if(espera >= 0) setEspera(p, espera);
			else setEspera(p, 0);
			ant = getTempoInicial(p)+getDisco(p)+getEspera(p);
			setTempoInicial(p, (getTempoInicial(p)+getDisco(p)+getEspera(p)));
			setEspera(p, getEspera(p)+esperaAnt);
		}
		char d;
		if(getIdDiscoUsado(p) == 0) d = getDadoCompD1(c);
		else d = getDadoCompD2(c);
		setDado(p, d);
		i++;
		fila_inseri_fim(aux, p);
	}
	while(!fila_vazia(aux))
		comp_insere_fila_rede_ordenado(c, fila_retira_ini(aux));
	fila_libera(aux);
}

static void fila_disco(Comp *c, int n){
	if(!comp_fila_disco_vazia(c, getIdDiscoD1(c))) fila_disco_auxiliar(c, n, getIdDiscoD1(c));
	if(!comp_fila_disco_vazia(c, getIdDiscoD2(c))) fila_disco_auxiliar(c, n, getIdDiscoD2(c));
}

static Fila* fila_rede(Comp *c, int n){
	Rede *r = getRedeComp(c);
	Fila *aux = fila_cria();
	Processo *p;
	int ant = 0, i = 0;
	while(!fila_rede_vazia(r)){
		if(n) p = retira_fila_rede(r);
		else p = retira_menor_demanda_rede(r);
		if(i == 0){
			int x = getEspera(p);
			setEspera(p, 0);
			ant = getTempoInicial(p)+getRede(p)+getEspera(p);
			setTempoInicial(p, (getTempoInicial(p)+getRede(p)+getEspera(p)));
			setEspera(p, x);
		}
		else{
			int espera = ant-getTempoInicial(p);
			int esperaAnt = getEspera(p);
			if(espera >= 0) setEspera(p, espera);
			else setEspera(p, 0);
			ant = getTempoInicial(p)+getRede(p)+getEspera(p);
			setTempoInicial(p, (getTempoInicial(p)+getRede(p)+getEspera(p)));
			setEspera(p, getEspera(p)+esperaAnt);
		}
		rede_push(r ,getDados(p));
		fila_inseri_fim(aux, p);
		i++;
	}
	return aux;
}

static void informacoes_processo(Fila *f1, Fila *f2){
	Processo *p;
	while(!fila_vazia(f1)){
		p = fila_retira_ini(f1);
		fila_inseri_fim(f2, p);
		imprimir_processo(p);
	}
	fila_libera(f1);
}

static ListaComp* cria_computadores(ListaComp *l, int num_comp, Rede *r){
	int i = 0;
	while(i < num_comp){
		l = lista_comp_insere(l, i);
		adicionar_rede_lista(l, r);
		i++;
	}
	return l;
}

static float qtd_processos(Fila *f, int *tempoMaximo){
	Fila *aux = fila_cria();
	float i = 0;
	Processo *p;
	while(!fila_vazia(f)){
		p = fila_retira_ini(f);
		if(*tempoMaximo < getTempoInicial(p)) *tempoMaximo = getTempoInicial(p);
		fila_inseri_fim(aux, p);
		i++;
	}
	while(!fila_vazia(aux)) fila_inseri_fim(f, fila_retira_ini(aux));
	fila_libera(aux);
	return i;
}

static void informacoes(float x1, float x2, int p1, int tempoMaximo, float qtdProcesso){
	printf("O tempo medio de execucao: %.2f\n", x1);
	printf("O tempo medio de espera: %.2f\n", x2);
	printf("A taxa de processamento: %.2f\n", qtdProcesso/(tempoMaximo-p1));
}

static void taxas_processamento(Fila *f, int p1){
	Fila *aux = fila_cria();
	int tempoMaximo = 0;
	float tempo_medio_execucao = 0, tempo_medio_espera;
	Processo *p;
	while(!fila_vazia(f)){
		p = fila_retira_ini(f);
		tempo_medio_execucao += (getCpu(p)+getDisco(p)+getRede(p)+getEspera(p));
		tempo_medio_espera += getEspera(p);
		fila_inseri_fim(aux, p);
	}
	float qtdP = qtd_processos(aux, &tempoMaximo);
	informacoes(tempo_medio_execucao/qtdP, tempo_medio_espera/qtdP, p1, tempoMaximo, qtdP);
	while(!fila_vazia(aux)) fila_inseri_fim(f, fila_retira_ini(aux));
	fila_libera(aux);
}

static void libera_memoria_neolook(ListaComp *l, Fila *f){
	lista_comp_libera(l);
	fila_libera(f);
}

static void falha(){
	printf("Modelo de escalonador invalido!\n");
	exit(1);
}

static void neolook_escalonador(ListaComp *lc, Comp *c, int num_comp, char *escalonador, Fila *f1){
	Fila *f2;
	if(escalonador_fcfs(escalonador)){
		int n = escalonador_fcfs(escalonador);
		int i = 0;
		while(i < num_comp){
			c = busca_comp(lc, i);
			if(!comp_fila_vazia(c)){
				fila_cpu(c, n);
				fila_disco(c, n);
			}
			i++;
		}
		c = busca_comp(lc, 0);
		f2 = fila_rede(c, n);
		informacoes_processo(f2, f1);
	}
	else if(escalonador_sjf(escalonador)){
		int i = 0, n = escalonador_fcfs(escalonador);
		while(i < num_comp){
			c = busca_comp(lc, i);
			if(!comp_fila_vazia(c)){
				fila_cpu(c, n);
				fila_disco(c, n);
			}
			i++;
		}
		c = busca_comp(lc, 0);
		f2 = fila_rede(c, n);
		informacoes_processo(f2, f1);
	}
	else falha();
}

void neolook(char *text, char *escalonador, int num_comp){
	int j = 0, v[4], i = 0, computador, z = 0, cont  = 0, primeiroProcesso;
	Rede *r = cria_rede();
	ListaComp *lc = lista_comp_cria();
	lc = cria_computadores(lc, num_comp, r);
	Comp *c;
	FILE *arq = fopen(text, "r");
	Processo *aux;
	srand(time(NULL));
	while(fscanf(arq, "%d", &i) == 1){
		if(j == 4){
			aux = cria_processo();
			computador = (rand()%num_comp);
			inserir_demandas(aux, v, z, computador);
			if(cont == 0) primeiroProcesso = getTempoInicial(aux);
			c = busca_comp(lc, computador);
			comp_fila_insere(c, aux);
			j = 0;
			z++;
			cont++;
		}
		v[j] = i;
		j++;
	}
	fclose(arq);
	aux = cria_processo();
	computador = (rand()%num_comp);
	inserir_demandas(aux, v, z, computador);
	c = busca_comp(lc, computador);
	comp_fila_insere(c, aux);
	Fila *f = fila_cria();
	neolook_escalonador(lc, c, num_comp, escalonador, f);
	taxas_processamento(f, primeiroProcesso);
	libera_memoria_neolook(lc, f);
}
