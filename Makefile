CFLAGS=-Wall -Wextra -pedantic -Werror -std=c++14 -O3
#CFLAGS=-Wall -Wextra -pedantic -Werror -std=c++14 -g -pg -O3


a.out: main.o command.o list.o record.o print.o  groupm.o
	g++ $(CFLAGS) main.o command.o list.o record.o print.o groupm.o -o a.out
main.o: main.cpp command.h list.h groupm.h
	g++ -c $(CFLAGS)  main.cpp
groupm.o: groupm.cpp groupm.h list.h record.h command.h
	g++ -c $(CFLAGS)  groupm.cpp
list.o: list.cpp list.h list_node.h command.h
	g++ -c $(CFLAGS)  list.cpp
command.o: command.cpp command.h list.h list_node.h groupm.h
	g++ -c $(CFLAGS)  command.cpp
record.o: record.cpp record.h 
	g++ -c $(CFLAGS)  record.cpp
print.o: print.cpp command.h
	g++ -c $(CFLAGS)  print.cpp
	
clean:
	rm -rf *.o *.out *.exe *.txt 