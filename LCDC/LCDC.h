#ifndef __LCDC_H_
#define __LCDC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>

#define FD_OPEN_FAILED -10
#define VINFO_READ_FAILED -11
#define MMAP_FAILED -12

int fb_open(void);
int fb_close(void);
int fb_draw_back_888(int x, int y, char Red, char Green, char Blue);
int fb_draw_back_565(int x, int y, u_int16_t color);
int fb_clear_888(char Red, char Green, char Blue);
int fb_clear_565(u_int16_t color);

#endif