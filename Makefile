CC=g++
CFLAGS=-Wall -I.
DEPS=trie.h parser.h lexer.h interpreter.h
OBJS=main.o lexer.o parser.o interpreter.o token.o states/blockcomment.o states/id.o states/linecomment.o states/number.o states/string.o states/symbol.o
ODIR=obj

OBJ = $(patsubst %,$(ODIR)/%,$(OBJS))

obj/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

avlang: $(OBJ)
	gcc -o bin/$@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f obj/*.o
	rm -f obj/states/*.o

