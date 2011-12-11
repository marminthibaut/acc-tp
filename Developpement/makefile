DEBUG=yes
ifeq ($(DEBUG),yes)
	CFLAGS=-W -Wall -ansi -pedantic -g
else
	CFLAGS=
endif
CC=g++
LDFLAGS=

main: bin/main.o bin/MatrixGraph.o bin/LevelGraph.o bin/graph.o bin/AdjacencyListGraph.o bin/flow.o bin/utils.o
	${CC} -o bin/$@ bin/*.o ${CFLAGS} ${LDFLAGS}



bin/%.o : src/graph/src/%.cpp
	${CC} -c -o $@ $< ${CFLAGS}

bin/%.o: src/%.cpp
	${CC} -c -o $@ $< ${CFLAGS}

clean:
	rm bin/*.o
