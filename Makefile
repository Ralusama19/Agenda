COMPILACION_JUTGE = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++0x

practica.tar: agenda.* activitat.* rellotge.* program.* *.txt equip.pdf html.zip Makefile
	tar -cvf practica.tar agenda.* activitat.* rellotge.* program.* *.txt equip.pdf html.zip Makefile

program.exe: program.o agenda.o activitat.o rellotge.o comanda.o token.o
	g++ -o program.exe program.o agenda.o activitat.o rellotge.o comanda.o token.o

program.o: program.cc
	g++ -c  $(COMPILACION_JUTGE) program.cc

agenda.o: agenda.hh agenda.cc
	g++ -c  $(COMPILACION_JUTGE) agenda.cc

activitat.o: activitat.hh activitat.cc
	g++ -c  $(COMPILACION_JUTGE) activitat.cc

rellotge.o: rellotge.hh rellotge.cc
	g++ -c  $(COMPILACION_JUTGE) rellotge.cc

comanda.o: comanda.hh comanda.cc
	g++ -c  $(COMPILACION_JUTGE) comanda.cc

token.o: token.hh token.cc
	g++ -c  $(COMPILACION_JUTGE) token.cc

clean: 
	rm *.o
	rm *.exe
	rm *.tar


