#include <linux/fb.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>

// draw a red point at (x, y) of color (Red/ Green /Blue)

static unsigned int *fbp;
static int fd;

void fb_draw_back(struct fb_var_screeninfo vinfo, int x, int y, char Red, char Green, char Blue){
        int offset;
        short color;
        offset = (y * vinfo.xres + x) * vinfo.bits_per_pixel / 8;
        color = (Red << 11) | (( Green << 5) & 0x07E0 ) | (Blue & 0x1F );
        *( unsigned char *)( fbp + offset + 0) = color & 0xFF;
        *( unsigned char *)( fbp + offset + 1) = ( color >> 8) & 0xFF;
}


int fb_open(){
        int fd;
	int ret;

        fd = open("/dev/fb0",O_RDWR);
        if (fd < 0)
        {
          perror("open");
          return -1;
        }

        struct fb_var_screeninfo vinfo;
        memset(&vinfo, 0, sizeof(vinfo));

        ret = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
        if (ret < 0)
        {
          perror("ioctl");
          return -1;
        }


        unsigned long screensize = vinfo.xres * vinfo.yres* vinfo.bits_per_pixel / 8;
	fbp = (unsigned char *) mmap (0, screensize , PROT_READ | PROT_WRITE , MAP_SHARED , fd , 0);
        if(fbp==NULL)                                
        {                                
                perror("mmap");          
                return -1;                           
        }                                                                            
      fb_draw_back( vinfo, 20, 20, 128, 0, 0);                                                     
//        memset(fbp, 255, screensize);                                                                 
        sleep(10);
	munmap(fbp,screensize);                                                                      
        return 0;                                                                                    
}                                                                                                    
                               
int main(){                                                                          
        fb_open();                                                                                   
        return 0;                                                                                    
}      
