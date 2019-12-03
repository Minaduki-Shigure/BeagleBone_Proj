#ifndef __MYDRAW_H_
#define __MYDRAW_H_

#include "LCDC.h"

#define DEF_SIZE 64

#define WHITE           0xFFFF
#define BLACK         	0x0000	  
#define BLUE         	0x001F
#define BRED            0XF81F
#define GRED 			0XFFE0
#define GBLUE			0X07FF
#define RED           	0xF800
#define MAGENTA       	0xF81F
#define GREEN         	0x07E0
#define CYAN          	0x7FFF
#define YELLOW        	0xFFE0
#define BROWN 			0XBC40 //棕色
#define BRRED 			0XFC07 //棕红色
#define GRAY  			0X8430 //灰色

#define DARKBLUE      	0X01CF	//深蓝色
#define LIGHTBLUE      	0X7D7C	//浅蓝色
#define GRAYBLUE       	0X5458 //灰蓝色
 
#define LIGHTGREEN     	0X841F //浅绿色
#define LIGHTGRAY       0XEF5B //浅灰色(PANNEL)
#define LGRAY 			0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE       0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE          0X2B12 //浅棕蓝色(选择条目的反色)

extern struct fb_var_screeninfo vinfo;

//m^n函数
//返回值:m^n次方.
long Pow(int m, int n);

void Clear(u_int16_t color);
void DrawPoint(int x, int y, u_int16_t color);
void DrawLine(int x1, int y1, int x2, int y2, u_int16_t color);
void DrawRectangle(int x1, int y1, int x2, int y2, u_int16_t color);
void DrawCircle(int x0, int y0, int r, u_int16_t color);

//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16/24/32
void ShowChar(int x, int y, char content, int size, u_int16_t color);
//显示数字,高位为0,则不显示
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//color:颜色 
//num:数值(0~4294967295);	
void ShowNum(int x, int y, long num, u_int8_t len, int size, u_int16_t color);
void ShowFloat(int x, int y, double num, u_int8_t precision, u_int8_t len, u_int8_t size, u_int16_t color);
//显示字符串
//x,y:起点坐标
//width,height:区域大小  
//size:字体大小
//*p:字符串起始地址	
void ShowString(int x, int y, int width, int height, u_int8_t size, char *p, u_int16_t color);

void Clear_RGB(char red, char green, char blue);
void DrawPoint_RGB(int x, int y, char red, char green, char blue);
void DrawLine_RGB(int x1, int y1, int x2, int y2, char red, char green, char blue);
void DrawRectangle_RGB(int x1, int y1, int x2, int y2, char red, char green, char blue);
void DrawCircle_RGB(int x0, int y0, int r, char red, char green, char blue);

//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16/24/32
void ShowChar_RGB(int x, int y, char content, int size, char red, char green, char blue);
//显示数字,高位为0,则不显示
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//color:颜色 
//num:数值(0~4294967295);	
void ShowNum_RGB(int x, int y, long num, u_int8_t len, int size, char red, char green, char blue);
void ShowFloat_RGB(int x, int y, double num, u_int8_t precision, u_int8_t len, u_int8_t size, char red, char green, char blue);
//显示字符串
//x,y:起点坐标
//width,height:区域大小  
//size:字体大小
//*p:字符串起始地址	
void ShowString_RGB(int x, int y, int width, int height, u_int8_t size, char *p, char red, char green, char blue);

#endif