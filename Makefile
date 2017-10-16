CC=gcc
CFLAGS=-g
TARGET=ScreenInfo
LIBS=-lX11 -lXrandr

$(TARGET):*.o
	$(CC) $(CFLAGS) -o $(TARGET) *.o $(LIBS)

*.o:*.c
	$(CC) -c *.c

clean:
	rm -rf *.o $(TARGET)
