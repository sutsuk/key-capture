CC     = gcc -g
MAIN_C = main.c
MAIN_O = main.o
KEY_C  = keyboard.c
KEY_O  = keyboard.o
DEST   = key-logger

all:	$(DEST)

$(DEST):		$(MAIN_O) $(KEY_O)
			$(CC) $(MAIN_O) $(KEY_O) -o $(DEST)

$(MAIN_O):	$(MAIN_C)
			$(CC) -c $(MAIN_C)

$(KEY_O):	  $(KEY_C)
			$(CC) -c $(KEY_C)

run:				$(DEST)
			./$(DEST)

clean:;			rm -rf *.o $(DEST)
