#include "mydraw.h"
#include "FONT.H"

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

void DrawCircle_RGB(int x0, int y0, int r, char red, char green, char blue)
{
	int a, b;
	int di;
	a = 0;
    b = r;
	di = 3 - (r << 1);             //判断下个点位置的标志
	while (a <= b)
	{
		DrawPoint_RGB(x0 + a, y0 - b, red, green, blue);             //5
 		DrawPoint_RGB(x0 + b, y0 - a, red, green, blue);             //0           
		DrawPoint_RGB(x0 + b, y0 + a, red, green, blue);             //4               
		DrawPoint_RGB(x0 + a, y0 + b, red, green, blue);             //6 
		DrawPoint_RGB(x0 - a, y0 + b, red, green, blue);             //1       
 		DrawPoint_RGB(x0 - b, y0 + a, red, green, blue);             
		DrawPoint_RGB(x0 - a, y0 - b, red, green, blue);             //2             
  		DrawPoint_RGB(x0 - b, y0 - a, red, green, blue);             //7 	         
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

void ShowChar(int x, int y, char content, int size, u_int16_t color)
{  							  
    unsigned char temp, t1, t;
	int y0 = y;
	u_int8_t csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);		//得到字体一个字符对应点阵集所占的字节数	
 	content = content - ' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for (t = 0; t < csize; ++t)
	{   
		if (size == 12)
        {
            temp = asc2_1206[content][t]; 	 	//调用1206字体
        }
        else if (size == 16)
        {
            temp = asc2_1608[content][t];	//调用1608字体
        }
		else if (size == 24)
        {
            temp = asc2_2412[content][t];	//调用2412字体
        }
		else if (size == 32)
        {
            temp = asc2_3216[content][t];  //调用3216字体
        }
		else
        {
            return;								//没有的字库
        }
		for (t1 = 0; t1 < 8; ++t1)
		{			    
			if (temp & 0x80)
            {
                DrawPoint(x, y, color);
            }
			temp <<= 1;
			++y;
			if (y >= vinfo.yres)
            {
                return;		//超区域了
            }
			if ((y - y0) == size)
			{
				y = y0;
				++x;
				if (x >= vinfo.xres)
                {
                    return;	//超区域了
                }
				break;
			}
		}
	}  	 	  
}

void ShowChar_RGB(int x, int y, char content, int size, char red, char green, char blue)
{  							  
    unsigned char temp, t1, t;
	int y0 = y;
	u_int8_t csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);		//得到字体一个字符对应点阵集所占的字节数	
 	content = content - ' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for (t = 0; t < csize; ++t)
	{   
		if (size == 12)
        {
            temp = asc2_1206[content][t]; 	 	//调用1206字体
        }
        else if (size == 16)
        {
            temp = asc2_1608[content][t];	//调用1608字体
        }
		else if (size == 24)
        {
            temp = asc2_2412[content][t];	//调用2412字体
        }
		else if (size == 32)
        {
            temp = asc2_3216[content][t];  //调用3216字体
        }
		else
        {
            return;								//没有的字库
        }
		for (t1 = 0; t1 < 8; ++t1)
		{			    
			if (temp & 0x80)
            {
                DrawPoint_RGB(x, y, red, green, blue);
            }
			temp <<= 1;
			++y;
			if (y >= vinfo.yres)
            {
                return;		//超区域了
            }
			if ((y - y0) == size)
			{
				y = y0;
				++x;
				if (x >= vinfo.xres)
                {
                    return;	//超区域了
                }
				break;
			}
		}
	}  	 	  
}

long Pow(int m, int n)
{
	long result = 1;	 
	while (n--)
    {
        result *= m; 
    }   
	return result;
}	

void ShowNum(int x, int y, long num, u_int8_t len, int size, u_int16_t color)
{         	
	u_int8_t t, temp;
	u_int8_t enshow = 0;						   
	for (t = 0; t < len; ++t)
	{
		temp = (num / Pow(10, len - t - 1)) % 10;
		if ((enshow == 0) && t < (len - 1))
		{
			if (temp == 0)
			{
				ShowChar(x + (size / 2) * t, y, ' ', size, color);
				continue;
			}
            else
            {
                enshow = 1;
            }
		 	 
		}
	 	ShowChar(x + (size / 2) * t, y, temp + '0', size, color); 
	}
}

void ShowNum_RGB(int x, int y, long num, u_int8_t len, int size, char red, char green, char blue)
{         	
	u_int8_t t, temp;
	u_int8_t enshow = 0;						   
	for (t = 0; t < len; ++t)
	{
		temp = (num / Pow(10, len - t - 1)) % 10;
		if ((enshow == 0) && t < (len - 1))
		{
			if (temp == 0)
			{
				ShowChar_RGB(x + (size / 2) * t, y, ' ', size, red, green, blue);
				continue;
			}
            else
            {
                enshow = 1;
            }
		 	 
		}
	 	ShowChar_RGB(x + (size / 2) * t, y, temp + '0', size, red, green, blue); 
	}
} 

void ShowFloat(int x, int y, double num, u_int8_t precision, u_int8_t len, u_int8_t size, u_int16_t color)
{
	u_int8_t t, psign = 0, pint = 0, pdec = 0;
	u_int8_t interger[DEF_SIZE], decimal[DEF_SIZE];
	u_int64_t tempint, tempdec;
	if (num < 0)
	{
		psign = 1;
		tempint = -num;
		tempdec = (-num - tempint * 1.0) * Pow(10, precision);
	}
	else
	{
		tempint = num;
		tempdec = (num - tempint * 1.0) * Pow(10, precision);
	}
	do
	{
		interger[pint++] = tempint % 10;
		tempint /= 10;
	}while (tempint != 0);
	
	for (pdec = 0; pdec < precision; ++pdec)
	{
		decimal[pdec] = tempdec % 10;
		tempdec /= 10;
	}
	
	if (psign)
    {
		ShowChar(x, y, '-', size, color);
    }
	for (t = psign; t < len; ++t)
	{
		if (t < pint + psign)
        {
			ShowChar(x + (size / 2) * t, y, interger[pint - 1 - (t - psign)] + '0', size, color);
        }
		else if (t == pint + psign)
        {
			ShowChar(x + (size / 2) * t, y, '.', size, color);
        }
        else if (t < (pint + pdec + 1 + psign))
        {
			ShowChar(x + (size / 2) * t, y, decimal[pint + pdec - (t - psign)] + '0', size, color);	
        }
        else
        {
			ShowChar(x + (size / 2) * t, y, ' ', size, color);
        }
	}
}

void ShowFloat_RGB(int x, int y, double num, u_int8_t precision, u_int8_t len, u_int8_t size, char red, char green, char blue)
{
	u_int8_t t, psign = 0, pint = 0, pdec = 0;
	u_int8_t interger[DEF_SIZE], decimal[DEF_SIZE];
	u_int64_t tempint, tempdec;
	if (num < 0)
	{
		psign = 1;
		tempint = -num;
		tempdec = (-num - tempint * 1.0) * Pow(10, precision);
	}
	else
	{
		tempint = num;
		tempdec = (num - tempint * 1.0) * Pow(10, precision);
	}
	do
	{
		interger[pint++] = tempint % 10;
		tempint /= 10;
	}while (tempint != 0);
	
	for (pdec = 0; pdec < precision; ++pdec)
	{
		decimal[pdec] = tempdec % 10;
		tempdec /= 10;
	}
	
	if (psign)
    {
		ShowChar_RGB(x, y, '-', size, red, green, blue);
    }
	for (t = psign; t < len; ++t)
	{
		if (t < pint + psign)
        {
			ShowChar_RGB(x + (size / 2) * t, y, interger[pint - 1 - (t - psign)] + '0', size, red, green, blue);
        }
		else if (t == pint + psign)
        {
			ShowChar_RGB(x + (size / 2) * t, y, '.', size, red, green, blue);
        }
        else if (t < (pint + pdec + 1 + psign))
        {
			ShowChar_RGB(x + (size / 2) * t, y, decimal[pint + pdec - (t - psign)] + '0', size, red, green, blue);	
        }
        else
        {
			ShowChar_RGB(x + (size / 2) * t, y, ' ', size, red, green, blue);
        }
	}
}

void ShowString(int x, int y, int width, int height, u_int8_t size, char *p, u_int16_t color)
{         
	u_int8_t x0 = x;
	width += x;
	height += y;
    while ((*p <= '~') && (*p >= ' '))//判断是不是非法字符!
    {       
        if (x>=width)
        {
            x = x0;
            y += size;
        }
        if (y >= height)
        {
            break;//退出
        }
        ShowChar(x, y, *p, size, color);
        x += size / 2;
        p++;
    }  
}

void ShowString_RGB(int x, int y, int width, int height, u_int8_t size, char *p, char red, char green, char blue)
{         
	u_int8_t x0 = x;
	width += x;
	height += y;
    while ((*p <= '~') && (*p >= ' '))//判断是不是非法字符!
    {       
        if (x>=width)
        {
            x = x0;
            y += size;
        }
        if (y >= height)
        {
            break;//退出
        }
        ShowChar_RGB(x, y, *p, size, red, green, blue);
        x += size / 2;
        p++;
    }  
}