#include <stdio.h>
#include <stdint.h>

#include <raylib.h>
#include "entity.h"
#include "render.h"

int main()
{
    InitRender();
    InitEntities();

    while (!WindowShouldClose())
    {
        Render();
        HandleEntities(1/(float)16);
    }

    CloseWindow();
}
