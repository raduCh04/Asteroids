#include <stdio.h>

#include <raylib.h>

int main(void)
{
    InitWindow(1024, 800, "raylib [core] example - basic window");
    Texture2D background = LoadTexture("../../assets/sprites/Background_space.png");

    while (!WindowShouldClose())
    {
        Rectangle src = {.x = 0, .y = 0, .width = background.width, .height = background.height };
        Rectangle dest = {.x = 0, .y = 0, .width = 1024, .height = 800};
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexturePro(background, src, dest, (Vector2){0, 0}, 0, WHITE);
        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();
}
