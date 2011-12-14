DEBUG=yes
ifeq ($(DEBUG),yes)
	CFLAGS=-W -Wall -ansi -pedantic -pg
else
	CFLAGS=
endif
CC=g++
LDFLAGS=

all: test dinic edmondskarp

dinic: bin/dinic_main.o bin/MatrixGraph.o bin/LevelGraph.o bin/graph.o bin/AdjacencyListGraph.o bin/flow.o bin/dinic.o bin/edmondskarp.o  bin/utils.o
	${CC} -o bin/$@ $^ ${CFLAGS} ${LDFLAGS}

edmondskarp: bin/edmondskarp_main.o bin/MatrixGraph.o bin/LevelGraph.o bin/graph.o bin/AdjacencyListGraph.o bin/flow.o bin/dinic.o bin/edmondskarp.o  bin/utils.o
	${CC} -o bin/$@ $^ ${CFLAGS} ${LDFLAGS}

test: bin/test.o bin/MatrixGraph.o bin/LevelGraph.o bin/graph.o bin/AdjacencyListGraph.o bin/flow.o bin/dinic.o bin/edmondskarp.o  bin/utils.o
	${CC} -o bin/$@ $^ ${CFLAGS} ${LDFLAGS}


bin/%.o : src/graph/flow/src/%.cpp
	${CC} -c -o $@ $< ${CFLAGS}

bin/%.o : src/graph/src/%.cpp
	${CC} -c -o $@ $< ${CFLAGS}

bin/%.o: src/%.cpp
	${CC} -c -o $@ $< ${CFLAGS}

clean:
	rm bin/*.o
