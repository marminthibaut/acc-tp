DEBUG=yes
ifeq ($(DEBUG),yes)
	CFLAGS=-pg
else
	CFLAGS=
endif
CC=g++
LDFLAGS=

main: main.o graph.o VertexListGraph.o graphGenerator.o algo.o flow.o
	${CC} -o ../bin/$@ ../bin/*.o ${CFLAGS} ${LDFLAGS}

%.o: %.cpp
	${CC} -c -o ../bin/$@ $< ${CFLAGS}


clean:
	rm ../bin/*.o
