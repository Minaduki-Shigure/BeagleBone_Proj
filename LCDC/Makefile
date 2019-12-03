CC = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g
CPPFLAGS = -fPIC
LFLAGS = -L. -lgraphics
target = main
object = LCDC.o mydraw.o
mainobj = main.o
lib = libgraphics.so

$(target): $(object) $(mainobj)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^

install: main.c $(lib) 
	$(CC) $(CFLAGS) -o $(target) $< $(LFLAGS)

$(lib): $(object)
	$(CC) $(CFLAGS) $(CPPFLAGS) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -rf $(target) *.o *.so