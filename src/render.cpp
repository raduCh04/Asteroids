#include <raylib.h>
#include "render.h"

#include "game.h"
#include "entity.h"

#include <assert.h>

static Texture2D g_Background;

static void RenderEntities()
{
    for (uint32_t i = 0; i < kMaxEntities; i++) //TODO: Add active entities array
    {
        if (g_Entities->m_Health[i] <= 0)
            continue;

        DrawTexturePro(g_Entities->m_Texture[i],
            g_Entities->m_Source[i],
            g_Entities->m_Destination[i],
            (Vector2){0, 0},
            0,
            WHITE);
    }
}

static void RenderBackground()
{
    Rectangle source = {
        .x = 0,
        .y = 0,
        .width = g_Background.width,
        .height = g_Background.height,
    };
    Rectangle destination = {
        .x = 0,
        .y = 0,
        .width = g_Config.m_ScreenWidth,
        .height = g_Config.m_ScreenHeight,
    };
    DrawTexturePro(g_Background, source, destination, (Vector2){0,0}, 0, WHITE);
}

static void RenderGui()
{
    assert(false);
}

void InitRender()
{
    InitWindow(g_Config.m_ScreenWidth, g_Config.m_ScreenHeight, "Asteroids");
    g_Background = LoadTexture("../assets/sprites/Background.png");
}

void Render()
{
    BeginDrawing();
    RenderBackground();
    RenderEntities();
    EndDrawing();
}
