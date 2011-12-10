DEBUG=yes
ifeq ($(DEBUG),yes)
	CFLAGS=-W -Wall -ansi -pedantic -g
else
	CFLAGS=
endif
CC=g++
LDFLAGS=

main: main.o MatrixGraph.o LevelGraph.o graph.o AdjacencyListGraph.o algo.o flow.o utils.o
	${CC} -o ../bin/$@ ../bin/*.o ${CFLAGS} ${LDFLAGS}

%.o: %.cpp
	${CC} -c -o ../bin/$@ $< ${CFLAGS}


clean:
	rm ../bin/*.o
