CC = gcc
CFILES = *.c
HFILES = *.h
OBJETOS = lista.o lista_minipruebas.o
FILES = Enunciado README.md
EXEC = lista_se
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes 

$(EXEC): pruebas.c $(OBJETOS)
	$(CC) $^ $(CFLAGS) -o $(EXEC)

debug: $(EXEC)
	gdb $(EXEC)

test: $(EXEC)
	valgrind $(VFLAGS) ./$(EXEC) $(arg_1) $(arg_2) $(arg_3)

run: $(EXEC)
	./$(EXEC) $(arg_1) $(arg_2) $(arg_3)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

zip: 
	zip -r $(EXEC).zip $(CFILES) $(HFILES) $(FILES)

.PHONY: clean
clean:
	rm -f *.o $(EXEC)