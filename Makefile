# Yuval Szwarcbord
# yszwarcb@ucsc.ued
# PA1

EXECUTABLE     = Words
OBJECT         = Words.o List.o
SOURCE         = Words.c List.c 
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
INFILE         = Holmes
OUTFILE        = $(INFILE)-out
MEMCHECK       = valgrind --leak-check=full 


$(EXECUTABLE) : $(OBJECT)
	$(LINK) $(EXECUTABLE) $(OBJECT)

Words.o : Words.c List.h
	$(COMPILE) Words.c

List.o : List.c List.h
	$(COMPILE) List.c

test : $(EXECUTABLE)
	./$(EXECUTABLE) $(INFILE) $(OUTFILE)

clean :
	$(REMOVE) ./$(EXECUTABLE) $(OBJECT)

check : $(EXECUTABLE)
	$(MEMCHECK) ./$(EXECUTABLE) $(INFILE) $(OUTFILE)
