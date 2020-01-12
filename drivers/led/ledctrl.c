#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  int fd = open("/dev/led",O_RDWR);
  int sign=0;
  char buff;
while(sign!=8)
{
  printf("use 0 till 7 to indicate different status of 3 leds, and input 8 to quit\n");

  if(sign ==8)
	break;
  printf("please input sign: ");
  scanf("%d",&sign);

  buff=sign;//二进制在那，根据读的方式不同显示不同的数据
  sleep(1);
  write(fd,&buff,1);
sleep(1);
}
  close(fd);
  return 0;
}

