all: menu.o conf.o io.o logger.o
	gcc menu.c conf.o io.o logger.c -o ./app

menu.o: menu.c menu.h
	gcc -c menu.c

conf.o: conf.c conf.h
	gcc -c conf.c

io.o: io.c io.h
	gcc -c io.c

logger.o: logger.c logger.h
	gcc -c logger.c

clean:
	rm -f ./*.o

