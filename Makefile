MAIN = ssres
SRCS =   ./getData.c ./dataGatherer.c ./main.c ./handleData.c ./itoa.c ./readData.c ./checkAvailable.c ./giveResult.c 
INCLUDES =  
LIBS = -lsqlite3 
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

getData.o: ssres.h
dataGatherer.o: ssres.h
main.o: ssres.h
handleData.o: ssres.h
readData.o: ssres.h
