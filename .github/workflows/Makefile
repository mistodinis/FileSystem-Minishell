

CC = gcc
CFLAGS = -g -Wall
TG = fsminishell
build: $(TG) 

$(TG): main.c list.c file.c
	$(CC) $(CFLAGS) -o $(TG) main.c list.c file.c

run: $(TG) 
	./$(TG)
clean: 
	rm $(TG)	
