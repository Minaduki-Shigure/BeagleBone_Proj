#include "mydraw.h"

void Clear(u_int16_t color)
{
    fb_clear_565(color);
}

void Clear_RGB(char red, char green, char blue)
{
    fb_clear_888(red, green, blue);
}

void DrawPoint(int x, int y, u_int16_t color)
{
    fb_draw_back_565(x, y, color);
    return;
}

void DrawPoint_RGB(int x, int y, char red, char green, char blue)
{
    fb_draw_back_888(x, y, red, green, blue);
    return;
}

void DrawLine(int x1, int y1, int x2, int y2, u_int16_t color)
{
	int t; 
	int xerr = 0, yerr = 0, delta_x, delta_y, distance; 
	int incx, incy, uRow, uCol; 
	delta_x = x2 - x1; //计算坐标增量 
	delta_y = y2 - y1; 
	uRow = x1; 
	uCol = y1; 
	if (delta_x > 0)
    {
        incx = 1; //设置单步方向 
    }
    else if (delta_x == 0)
    {
        incx = 0;//垂直线 
    }
    else
    {
        incx = -1;
        delta_x = -delta_x;
    } 
	if (delta_y > 0)
    {
        incy = 1;
    } 
	else if (delta_y == 0)
    {
        incy = 0;//水平线
    }
	else
    {
        incy = -1;
        delta_y = -delta_y;
    } 
	if (delta_x > delta_y)
    {
        distance = delta_x; //选取基本增量坐标轴 
    }
    else
    {
        distance = delta_y;
    }
	for (t = 0; t <= distance + 1; ++t)//画线输出 
	{  
		DrawPoint(uRow, uCol, color);//画点 
		xerr += delta_x; 
		yerr += delta_y; 
		if (xerr > distance) 
		{ 
			xerr -= distance; 
			uRow += incx; 
		} 
		if (yerr > distance) 
		{ 
			yerr -= distance; 
			uCol += incy; 
		} 
	}  
}    

void DrawLine_RGB(int x1, int y1, int x2, int y2, char red, char green, char blue)
{
	int t; 
	int xerr = 0, yerr = 0, delta_x, delta_y, distance; 
	int incx, incy, uRow, uCol; 
	delta_x = x2 - x1; //计算坐标增量 
	delta_y = y2 - y1; 
	uRow = x1; 
	uCol = y1; 
	if (delta_x > 0)
    {
        incx = 1; //设置单步方向 
    }
    else if (delta_x == 0)
    {
        incx = 0;//垂直线 
    }
    else
    {
        incx = -1;
        delta_x = -delta_x;
    } 
	if (delta_y > 0)
    {
        incy = 1;
    } 
	else if (delta_y == 0)
    {
        incy = 0;//水平线
    }
	else
    {
        incy = -1;
        delta_y = -delta_y;
    } 
	if (delta_x > delta_y)
    {
        distance = delta_x; //选取基本增量坐标轴 
    }
    else
    {
        distance = delta_y;
    }
	for (t = 0; t <= distance + 1; ++t)//画线输出 
	{  
		DrawPoint_RGB(uRow, uCol, red, green, blue);//画点 
		xerr += delta_x; 
		yerr += delta_y; 
		if (xerr > distance) 
		{ 
			xerr -= distance; 
			uRow += incx; 
		} 
		if (yerr > distance) 
		{ 
			yerr -= distance; 
			uCol += incy; 
		} 
	}  
}    

void DrawRectangle(int x1, int y1, int x2, int y2, u_int16_t color)
{
	DrawLine(x1, y1, x2, y1, color);
	DrawLine(x1, y1, x1, y2, color);
	DrawLine(x1, y2, x2, y2, color);
	DrawLine(x2, y1, x2, y2, color);
}

void DrawRectangle_RGB(int x1, int y1, int x2, int y2, char red, char green, char blue)
{
	DrawLine_RGB(x1, y1, x2, y1, red, green, blue);
	DrawLine_RGB(x1, y1, x1, y2, red, green, blue);
	DrawLine_RGB(x1, y2, x2, y2, red, green, blue);
	DrawLine_RGB(x2, y1, x2, y2, red, green, blue);
}

void DrawCircle(int x0, int y0, int r, u_int16_t color)
{
	int a, b;
	int di;
	a = 0;
    b = r;	  
	di = 3 - (r << 1);             //判断下个点位置的标志
	while (a <= b)
	{
		DrawPoint(x0 + a, y0 - b, color);             //5
 		DrawPoint(x0 + b, y0 - a, color);             //0           
		DrawPoint(x0 + b, y0 + a, color);             //4               
		DrawPoint(x0 + a, y0 + b, color);             //6 
		DrawPoint(x0 - a, y0 + b, color);             //1       
 		DrawPoint(x0 - b, y0 + a, color);             
		DrawPoint(x0 - a, y0 - b, color);             //2             
  		DrawPoint(x0 - b, y0 - a, color);             //7     	         
		++a;
		//使用Bresenham算法画圆     
		if (di < 0)
        {
            di += 4 * a + 6;
        }	  
		else
		{
			di += 10 + 4 * (a - b);   
			--b;
		} 						    
	}
} 	
