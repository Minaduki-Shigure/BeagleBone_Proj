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
    //DrawPoint(300, 200, BLUE);

    fb_close();

    return EXIT_SUCCESS;
}