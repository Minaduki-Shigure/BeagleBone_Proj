#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		if (argc != 4)
		{
			printf("Usage: %s <LED0> <LED1> <LED2>\n", argv[0]);
			return -1;
		}
		int fd = open("/dev/led", O_RDWR);
		char buf = 0;
		for (int i = 0; i < 3; ++i)
		{
			buf |= (argv[i + 1][0] - 0x30) << i;
		}
		printf("Writing %d to device\n", (int)buf);
		write(fd, &buf, 1);
		close(fd);
		return 0;
	}
	int fd = open("/dev/led", O_RDWR);
	int input = 0;
	char buf;
	while (input != 8)
	{
		printf("Please input 0 to 7 to change status of 3 leds, an input of 8 or larger will be considered as exiting\n");
		printf("Please input:");
		scanf("%d", &input);
		if (input > 7)
		{
			close(fd);
			return 0;
		}
		buf = input;
		write(fd, &buf, 1);
	}
	close(fd);
	return 0;
}