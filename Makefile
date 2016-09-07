myping: myping.o error.o signal.o host_serv.o sock_ntop_host.o proc_v4.o readloop.o
	gcc myping.o signal.o host_serv.o error.o sock_ntop_host.o proc_v4.o readloop.o -o myping -Wall -ggdb

myping.o: myping.c
	gcc -c myping.c

error.o: error.c
	gcc -c error.c

signal.o: signal.c
	gcc -c signal.c

host_serv.o: host_serv.c
	gcc -c host_serv.c

sock_ntop_host.o: sock_ntop_host.c
	gcc -c sock_ntop_host.c

proc_v4.o: proc_v4.c
	gcc -c proc_v4.c 

readloop.o: readloop.c
	gcc -c readloop.c

clean:
	rm *.o core *~ myping
