all: WireTacos.x

format.o: headers/format.h format.c
	gcc -Wall -g -c format.c

lecture.o: headers/lecture.h lecture.c
	gcc -Wall -g -c lecture.c

liste.o: headers/liste.h liste.c
	gcc -Wall -g -c liste.c

ethernet.o: headers/ethernet.h ethernet.c
	gcc -Wall -g -c ethernet.c

IP.o: headers/IP.h IP.c
	gcc -Wall -g -c IP.c

ARP.o: headers/ARP.h ARP.c
	gcc -Wall -g -c ARP.c

ICMP.o: headers/ICMP.h ICMP.c
	gcc -Wall -g -c ICMP.c

TCP.o: headers/TCP.h TCP.c
	gcc -Wall -g -c TCP.c

HTTP.o: headers/HTTP.h HTTP.c
	gcc -Wall -g -c HTTP.c

menu.o: headers/menu.h menu.c
	gcc -Wall -g -c menu.c

main.o: headers/lecture.h headers/format.h headers/ethernet.h headers/IP.h headers/ARP.h headers/ICMP.h headers/TCP.h headers/HTTP.h headers/menu.h ethernet.c lecture.c IP.c ARP.c ICMP.c TCP.c main.c
	gcc -g -o main.o -c main.c
#ethernet.o IP.o ARP.o ICMP.o

WireTacos.x: lecture.o format.o liste.o ethernet.o IP.o ARP.o ICMP.o TCP.o HTTP.o menu.o main.o 
	gcc -o WireTacos.x lecture.o format.o liste.o ethernet.o IP.o ARP.o ICMP.o TCP.o HTTP.o menu.o main.o
	rm -f *.o 

clean:
	rm -f *.o WireTacos.x