#include "LCDC.h"
#include "mydraw.h"

int main(int argc, char* argv[])
{
    if (EXIT_SUCCESS != fb_open())
    {
        return EXIT_FAILURE;
    }

    Clear(WHITE);
    DrawLine(300, 300, 600, 600, BLUE);
    DrawLine(0, 0, 200, 200, RED);
    DrawRectangle(50, 50, 80, 80, BLUE);
    DrawCircle(460, 460, 50, YELLOW);
    ShowChar(160, 160, 'M', 32, RED);
    ShowChar(180, 160, 'S', 32, RED);
    ShowNum(320, 320, 4396, 4, 32, BLACK);
    ShowFloat(450, 450, 2200.28, 3, 8, 32, BLACK);
    ShowString(240, 240, 500, 50, 32, "Hello world!", RED);
    DrawCircle(600, 600, 80, RED);
    ShowString(480, 360, 500, 50, 32, "By Minaduki Shigure.", BLUE);
    //DrawPoint(300, 200, BLUE);

    fb_close();

    return EXIT_SUCCESS;
}