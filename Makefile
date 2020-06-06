MAIN = ssres
SRCS =   ./getData.c ./dataGatherer.c ./main.c ./handleData.c ./itoa.c ./qsort.c ./readData.c ./htoi.c
INCLUDES =  
LIBS =  
CFLAGS = -Wall -g 
LFLAGS =  
CC = gcc-9
OBJS = $(SRCS:.c=.o)
.PHONY: depend clean
all:	$(MAIN)
	@echo  $(MAIN) has been compiled
$(MAIN):	$(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@
clean:
	$(RM) *.o *~ $(MAIN)
run :	$(MAIN)
	./$(MAIN)
depend:	$(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

