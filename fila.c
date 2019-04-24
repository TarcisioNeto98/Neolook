#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "lista.h"

struct fila{
	Lista *ini;
	Lista *fim;
};

Fila* fila_cria(){
	Fila *f = (Fila*)malloc(sizeof(Fila));
	f->ini = lista_cria();
	f->fim = lista_cria();
	return f;
}

int fila_vazia(Fila *f){
	return lista_vazia(f->ini);
}

void fila_inseri_fim(Fila *f, Processo *p){
	if(fila_vazia(f)){
		f->ini = lista_insere_ini(f->ini, p);
		f->fim = f->ini;
	}
	else f->fim = lista_insere_fim(f->fim, p);
}

void fila_inseri_ordenado(Fila *f, Processo *p){
	if(fila_vazia(f)){
		f->ini = lista_insere_ini(f->ini, p);
		f->fim = f->ini;
	}
	else if(verificar_maior(f->fim, p)) f->fim = lista_insere_fim(f->fim, p);
	else f->ini = lista_inserir_ordenado(f->ini, p);
}

Processo* fila_retira_ini(Fila *f){
	if(fila_vazia(f)){
		printf("Fila Vazia!");
		exit(1);
	}
	Processo *p = getProcesso(f->ini);
	f->ini = lista_retira_ini(f->ini);
	return p;
}

void fila_libera(Fila *f){
	lista_libera(f->ini);
	free(f);
}

void fila_imprimir(Fila *f){
	lista_imprimir(f->ini);
}

void fila_imprimir_espera(Fila *f){
	lista_imprimir_espera(f->ini);
}
