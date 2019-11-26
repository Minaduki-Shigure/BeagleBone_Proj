CC = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g
target = main
source = main.c LCDC.c mydraw.c

$(target): $(source)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(target)