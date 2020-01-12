#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
  int fd = open("/dev/led",O_RDWR);
  char command;
  char buff;
  int tmp[3];
  printf("use 0~7(3bits) control 3 leds(2~4), and input q to quit\n");
while(1)
{
  printf("please input command: ");
  scanf("%c",&buff);
  printf("\n");
  if (buff=='q')
	break;
  printf("get %d\n",buff);
  write(fd,&buff,1);
  printf("write over\n");


    tmp[0]=((unsigned int)(buff-0x30))&1;
    tmp[1]=((unsigned int)(buff-0x30))&(1<<1);
    tmp[2]=((unsigned int)(buff-0x30))&(1<<2);
    printf("get %u,%u,%u\n",tmp[0],tmp[1],tmp[2]);
  
}
  close(fd);
  return 0;
}
