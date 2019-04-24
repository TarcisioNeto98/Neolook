all: exe

main.o: main.c
	gcc -c main.c

neolook.o: neolook.c
	gcc -c neolook.c

computador.o: computador.c
	gcc -c computador.c

listaComp.o: listaComp.c
	gcc -c listaComp.c

fila.o: fila.c
	gcc -c fila.c

disco.o: disco.c
	gcc -c disco.c

lista.o: lista.c
	gcc -c lista.c

processo.o: processo.c
	gcc -c processo.c

rede.o: rede.c
	gcc -c rede.c

exe: main.o lista.o processo.o rede.o disco.o fila.o listaComp.o computador.o neolook.o
	gcc -o exe.x main.o lista.o processo.o rede.o disco.o fila.o listaComp.o computador.o neolook.o

clean:
	rm -f *.x *.o
