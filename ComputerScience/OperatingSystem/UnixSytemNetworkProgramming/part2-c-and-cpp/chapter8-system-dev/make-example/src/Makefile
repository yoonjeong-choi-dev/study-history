CC	= cc
IDIR	= ../include
CFLAGS	= -c -g -O -I$(IDIR)
LFLAGS	= 

# Object File list
TARGET	= main
OBJS	= main.o subA.o subB.o subAa.o

.c.o:
		$(CC) $(CFLAGS) $<

# Target
all : $(OBJS)
		$(CC) -o $(TARGET) $(OBJS) $(LFLAGS)

clean:
		rm $(OBJS)
		rm $(TARGET)
