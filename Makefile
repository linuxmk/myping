myping: myping.o error.o signal.o host_serv.o sock_ntop_host.o proc_v4.o readloop.o wrapthread.o
	gcc myping.o signal.o host_serv.o error.o sock_ntop_host.o proc_v4.o readloop.o wrapthread.o -o myping -Wall -ggdb -pthread

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

wrapthread.o: wrapthread.c
	gcc -c wrapthread.c

clean:
	rm *.o core *~ myping
