all: 
	(gcc -pthread -c ./src/naive.c -o ./obj/naive.o)
	(gcc -pthread -c ./src/loadb.c -o ./obj/loadb.o)
	(gcc -pthread obj/naive.o -o bin/naive -lm)
	(gcc -pthread obj/loadb.o -o bin/loadb -lm)
	(./bin/naive $(N) $(t))
	(./bin/loadb $(N) $(t))
	(gcc -c ./src/plot.c -o ./obj/plot.o)
	(gcc obj/plot.o -o bin/plot)
	(cd bin; sudo ./plot)

clean:
	(cd obj; rm *)
	(cd bin; rm *)