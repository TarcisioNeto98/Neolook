#include <stdio.h>
#include <stdlib.h>
#include "neolook.h"

int main(int argc, char *argv[]){
	int numComp;
	printf("Digite o numero de computadores:\n");
	scanf("%d", &numComp);
	neolook(argv[2], argv[1], numComp);
	return 0;
}
