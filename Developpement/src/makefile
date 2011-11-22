DEBUG=yes
ifeq ($(DEBUG),yes)
	CFLAGS=-funittest
else
	CFLAGS=
endif
CC=gdc-4.6
LDFLAGS=

main: main.o IGraph.o VertexListGraph.o
	${CC} -o ../bin/$@ ../bin/*.o ${LDFLAGS}

IGraph.o: graph/IGraph.d
	${CC} -o ../bin/$@ -c $< ${CFLAGS}

VertexListGraph.o: graph/VertexListGraph.d
	${CC} -o ../bin/$@ -c $< ${CFLAGS}


%.o: %.d
	${CC} -o ../bin/$@ -c $< ${CFLAGS}


clean:
	rm ../bin/*.o
