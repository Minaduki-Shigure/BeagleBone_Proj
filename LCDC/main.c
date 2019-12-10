#include "LCDC.h"
#include "mydraw.h"

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        if (EXIT_SUCCESS != fb_open(1, atoi(argv[1]), atoi(argv[2])))
        {
            return EXIT_FAILURE;
        }
    }
    else
    {
        if (EXIT_SUCCESS != fb_open(0, 0, 0))
        {
            return EXIT_FAILURE;
        }
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
    DrawLine(0, 0, 1023, 577, BLUE);

    fb_close();

    return EXIT_SUCCESS;
}