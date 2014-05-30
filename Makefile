EXEC=simsched
OBJS=randsim.o sched.o main.o

simsched: ${OBJS}

default: ${EXEC}

clean:
	rm -f ${OBJS} ${EXEC}

${EXEC}: ${OBJS}
	g++ -ggdb -o $@ $^

# need the c++11 for convenience wrt the use of random
%.o: %.cpp
	g++ -ggdb -std=c++11 -c $<
