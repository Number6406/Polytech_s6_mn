CC = gcc
EXEC = res_diag res_inf res_sup vectorisation tri_inf_v
CFLAGS = -Wall
SRCS = res_diag.c res_inf.c res_sup.c resolution.c vectorisation.c tri_inf_v.c
OBJS = $(SRCS:.c=.o)

all : $(EXEC)

#.c.o :
#  $(CC) $(CFLAGS) -c $<

res_diag : res_diag.o resolution.o
	-@echo // Creation de "l'executable" $@
	$(CC) res_diag.o -o bin/res_diag

res_inf : res_inf.o resolution.o
	-@echo // Creation de "l'executable" $@
	$(CC) res_inf.o -o bin/res_inf

res_sup : res_sup.o resolution.o
	-@echo // Creation de "l'executable" $@
	$(CC) res_sup.o -o bin/res_sup

vectorisation : vectorisation.c
	-@echo Création de "l'exécutable" $@
	$(CC) -msse4.1 vectorisation.c -o bin/vectorisation

tri_inf_v : tri_inf_v.c
	-@echo Création de "l'exécutable" $@
	$(CC) -msse4.1 tri_inf_v.c -o tri_inf_v

clean :
	@echo "Suppression des objets"
	-rm $(OBJS)
