CC = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g
CPPFLAGS = -fPIC
target = main
source = main.c LCDC.c mydraw.c

$(target): $(source)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^

clean:
	rm -rf $(target)