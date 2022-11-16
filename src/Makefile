# liste des fichiers source
SRC = main.c hash-tables.c generic-linked-lists.c
#SRC = $(wildcard *.c)

# liste des fichiers .o et des dependances (mis dans le repertoire build/)
OBJ = $(addprefix build/,$(SRC:.c=.o))
DEP = $(addprefix build/,$(SRC:.c=.d))

# nom du compilateur
CC = gcc

# nom de l'executable
EXE = main

# flags de compilation (CFLAGS) et d'edition de liens (LDFLAGS)
CFLAGS += -Wall  -MMD -g -O2
LDFLAGS= #-lm

# regle principale: generer l'executable
all: $(OBJ)
	$(CC) -o $(EXE) $^ $(LDFLAGS)

# regle generique pour produire un fichier .o a partir d'un fichier .c
build/%.o: %.c
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ -c $<

# regle generique pour faire du nettoyage
clean:
	rm -rf build core *.gch

# inclusion automatique du fichier de dependances
-include $(DEP)
