#include "LCDC.h"

static int fd;
static struct fb_var_screeninfo vinfo;
static char* fbp;
unsigned long screen_size;

int fb_open(void)
{

    fd = open("/dev/fb0", O_RDWR);
    if (fd < 0)
    {
        perror("open");
        return FD_OPEN_FAILED;
    }

    memset(&vinfo, 0, sizeof(vinfo));
        
    if (ioctl(fd, FBIOGET_VSCREENINFO, &vinfo) < 0)
    {
        perror("ioctl");
        return VINFO_READ_FAILED;
    }

	//printf("xres=%d\nyres=%d\nbit=%d\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);
    printInfo();

    screen_size = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
	
    fbp = (unsigned char*)mmap(0, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    //printf("%p\n", fbp);
    
    if(NULL == fbp)                                
    {                                
        perror("mmap");          
        return MMAP_FAILED;                           
    }
    
    return EXIT_SUCCESS;                                                                               
}

int fb_close(void)
{
    munmap(fbp, screen_size);
    screen_size = 0;
    fbp = NULL;
    memset(&vinfo, 0, sizeof(vinfo));
    close(fd);
    return EXIT_SUCCESS;
}

void printInfo(void)
{
   printf ("Screen info:\n"
                        " xres:%d\n"
                        " yres:%d\n"
                        " xres_virtual:%d\n"
                        " yres_virtual:%d\n"
                        " yoffset:%d\n"
                        " xoffset:%d\n"
                        " bits_per_pixel:%d\n"
                        " grayscale:%d\n"
                        " red: offset:%2d, length: %2d, msb_right: %2d\n"
                        " green: offset:%2d, length: %2d, msb_right: %2d\n"
                        " blue: offset:%2d, length: %2d, msb_right: %2d\n"
                        " transp: offset:%2d, length: %2d, msb_right: %2d\n"
                        " nonstd:%d\n"
                        " activate:%d\n"
                        " height:%d\n"
                        " width:%d\n"
                        " accel_flags:0x%x\n"
                        " pixclock:%d\n"
                        " left_margin:%d\n"
                        " right_margin: %d\n"
                        " upper_margin:%d\n"
                        " lower_margin:%d\n"
                        " hsync_len:%d\n"
                        " vsync_len:%d\n"
                        " sync:%d\n"
                        " vmode:%d\n"
           "\n",
        vinfo.xres, vinfo.yres, vinfo.xres_virtual, vinfo.yres_virtual,
        vinfo.xoffset, vinfo.yoffset, vinfo.bits_per_pixel,
        vinfo.grayscale, vinfo.red.offset, vinfo.red.length,
        vinfo.red.msb_right,vinfo.green.offset, vinfo.green.length,
        vinfo.green.msb_right, vinfo.blue.offset, vinfo.blue.length,
        vinfo.blue.msb_right, vinfo.transp.offset, vinfo.transp.length,
        vinfo.transp.msb_right, vinfo.nonstd, vinfo.activate,
        vinfo.height, vinfo.width, vinfo.accel_flags, vinfo.pixclock,
        vinfo.left_margin, vinfo.right_margin, vinfo.upper_margin,
        vinfo.lower_margin, vinfo.hsync_len, vinfo.vsync_len,
        vinfo.sync, vinfo.vmode);
}


int fb_draw_back_888(int x, int y, char Red, char Green, char Blue)
{
    long offset;
    short color;
    offset = (y * vinfo.xres + x) * vinfo.bits_per_pixel / 8;
    color = ((Red << 8) & 0xF800) | ((Green << 3) & 0x07E0) | ((Blue >> 3) & 0x1F);
    *(unsigned char*)(fbp + offset + 0) = color & 0xFF;
    *(unsigned char*)(fbp + offset + 1) = (color >> 8) & 0xFF;
    return EXIT_SUCCESS;
}

int fb_draw_back_565(int x, int y, u_int16_t color)
{
    long offset;
    offset = (y * vinfo.xres + x) * vinfo.bits_per_pixel / 8;
    //printf("offset%ld x%d y%d xres%d bit%d size%ld\n", offset, x, y, vinfo.xres, vinfo.bits_per_pixel, screen_size);
    //printf("fbp%p\n", fbp);
    *(unsigned char*)(fbp + offset + 0) = color & 0xFF;
    *(unsigned char*)(fbp + offset + 1) = (color >> 8) & 0xFF;
    //printf("Success\n");
    return EXIT_SUCCESS;
}

int fb_clear_888(char Red, char Green, char Blue)
{
    short color;
    color = ((Red << 8) & 0xF800) | ((Green << 3) & 0x07E0) | ((Blue >> 3) & 0x1F);
    memset(fbp, color, screen_size);
    return EXIT_SUCCESS;
}

int fb_clear_565(u_int16_t color)
{
    memset(fbp, color, screen_size);
    return EXIT_SUCCESS;
}