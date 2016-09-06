myping: error.o signal.o
	gcc myping.c signal.o error.o  -o myping

error.o: error.c
	gcc -c error.c

signal.o: signal.c
	gcc -c signal.c

clean:
	rm *.o core *~
