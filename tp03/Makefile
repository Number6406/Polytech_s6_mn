CC = gcc
EXEC = res_diag res_inf res_sup vectorisation
CFLAGS = -Wall
SRCS = res_diag.c res_inf.c res_sup.c resolution.c vectorisation.c
OBJS = $(SRCS:.c=.o)

all : $(EXEC)

#.c.o :
#  $(CC) $(CFLAGS) -c $<

res_diag : res_diag.o resolution.o
	-@echo Creation de "l'executable" $@
	$(CC) res_diag.o -o res_diag

res_inf : res_inf.o resolution.o
	-@echo Creation de "l'executable" $@
	$(CC) res_inf.o -o res_inf

res_sup : res_sup.o resolution.o
	-@echo Creation de "l'executable" $@
	$(CC) res_sup.o -o res_sup

vectorisation : vectorisation.c
	-@echo Création de "l'exécutable" $@
	$(CC) vectorisation.c -o vectorisation

clean :
	@echo "Suppression des objets"
	-rm $(OBJS)
