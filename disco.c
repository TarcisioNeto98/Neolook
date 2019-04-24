#include <stdio.h>
#include <stdlib.h>
#include "disco.h"
#include "fila.h"

struct disco{
	int id;
	char dado;
};

Disco* disco_cria(int i){
	Disco *d = (Disco*)malloc(sizeof(Disco));
	d->dado = 'd';
	d->id = i;
}

void disco_libera(Disco *d){
	free(d);
}

char getDadoDisco(Disco *d){
	return d->dado;
}

int getIdDisco(Disco *d){
	return d->id;
}
