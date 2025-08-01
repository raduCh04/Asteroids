#include "entity.h"

#include <assert.h>

#include "game.h"

#include <stdio.h>

GameConfig g_Config = {
    .m_ScreenWidth = 1024,
    .m_ScreenHeight = 800,
};

enum class LevelAmount : uint32_t
{
    LEVEL1 = 128,
    LEVEL2 = LEVEL1 * 2,
    LEVEL3 = LEVEL2 * 2,
    LEVEL4 = LEVEL3 * 2,
};

Entity *g_Entities;
static uint32_t g_Level = 1;

static void InitPlayer()
{
    Texture2D playerTexture = LoadTexture("../assets/sprites/PlayerRed.png");
    float x_Pos = (g_Config.m_ScreenWidth / 2) - (playerTexture.width / 2);
    float y_Pos = (g_Config.m_ScreenHeight / 2) + (playerTexture.height / 2);

    Rectangle playerSource = (Rectangle){
        .x = 0,
        .y = 0,
        .width = (float)playerTexture.width,
        .height = (float)playerTexture.height,
    };

    Rectangle playerDestination = (Rectangle){
        .x = x_Pos,
        .y = y_Pos,
        .width = (float)playerTexture.width,
        .height = (float)playerTexture.height,
    };

    Vector2 playerStartPos = (Vector2){.x = x_Pos, .y = y_Pos};

    g_Entities->m_Health[PLAYER_ID] = 100;
    g_Entities->m_Type[PLAYER_ID] = EntityType::Player;

    g_Entities->m_Position[PLAYER_ID] = playerStartPos;
    g_Entities->m_Texture[PLAYER_ID] = playerTexture;
    g_Entities->m_Source[PLAYER_ID] = playerSource;
    g_Entities->m_Destination[PLAYER_ID] = playerDestination;
}

static void InitAsteroids()
{
    uint32_t asteroids_count = 0;
    switch (g_Level)
    {
        case 1:
            asteroids_count = (uint32_t)LevelAmount::LEVEL1;
            break;
        case 2:
            asteroids_count = (uint32_t)LevelAmount::LEVEL2;
            break;

        default:
            break;
    }

    Texture2D asteroids_texture[4];
    for (uint32_t i = 0; i < 4; i++)
        asteroids_texture[i] = LoadTexture(TextFormat("../assets/sprites/Asteroid0%d.png", i));

    for (uint32_t i = 1; i < asteroids_count; i++)
    {
        Texture2D texture = g_Entities->m_Texture[i] = asteroids_texture[GetRandomValue(0, 3)];        
        g_Entities->m_Type[i] = EntityType::Asteroid;
        g_Entities->m_Velocity[i].x = GetRandomValue(-2, 2);
        g_Entities->m_Velocity[i].y = GetRandomValue(-2, 2);
        uint32_t x_Pos = g_Entities->m_Position[i].x = GetRandomValue(0, g_Config.m_ScreenWidth);
        uint32_t y_Pos = g_Entities->m_Position[i].y = GetRandomValue(0, g_Config.m_ScreenHeight);
        g_Entities->m_Health[i] = 1;

        Rectangle source = (Rectangle){
            .x = 0,
            .y = 0,
            .width = (float)texture.width,
            .height = (float)texture.height,
        };

        Rectangle destination = (Rectangle){
            .x = (float)x_Pos,
            .y = (float)y_Pos,
            .width = (float)texture.width,
            .height = (float)texture.height,
        };

        g_Entities->m_Source[i] = source;
        g_Entities->m_Destination[i] = destination;
    }
}

static void InitBullets()
{
    assert(false);
}

void InitEntities()
{
    g_Entities = (Entity *)MemAlloc(sizeof(Entity));
    for (uint32_t i = 0; i < kMaxEntities; i++)
    {
        g_Entities->m_ID[i] = i;
    }
    InitPlayer();
    InitAsteroids();
}

static void HandlePlayer(uint32_t i)
{
    if (IsKeyDown(KEY_W))
    {
        g_Entities->m_Velocity[i].y = -3;
    }
    else if (IsKeyDown(KEY_S))
    {
        g_Entities->m_Velocity[i].y = 3;
    }
    else
    {
        g_Entities->m_Velocity[i].y *= 0.998;
    }

    if (IsKeyDown(KEY_A))
    {
        g_Entities->m_Velocity[i].x = -3;
    }
    else if (IsKeyDown(KEY_D))
    {
        g_Entities->m_Velocity[i].x = 3;
    }
    else
    {
        g_Entities->m_Velocity[i].x *= 0.998;
    }
}

void HandleEntities(float dt)
{
    for (uint32_t i = 0; i < kMaxEntities; i++)
    {
        if (g_Entities->m_Health[i] <= 0)
            continue;

        if (i == PLAYER_ID)
            HandlePlayer(i);

        g_Entities->m_Position[i].x += g_Entities->m_Velocity[i].x * dt;
        g_Entities->m_Position[i].y += g_Entities->m_Velocity[i].y * dt;

        if (g_Entities->m_Position[i].x < 0 || g_Entities->m_Position[i].x > g_Config.m_ScreenWidth)
        {
            g_Entities->m_Velocity[i].x *= -1;
        }
        if (g_Entities->m_Position[i].y < 0 || g_Entities->m_Position[i].y > g_Config.m_ScreenHeight)
        {
            g_Entities->m_Velocity[i].y *= -1;
        }

        g_Entities->m_Destination[i].x = g_Entities->m_Position[i].x;
        g_Entities->m_Destination[i].y = g_Entities->m_Position[i].y;
    }
}

void DestroyEntities()
{
    for (uint32_t i = 0; i < kMaxEntities; i++)
    {
        if (IsTextureValid(g_Entities->m_Texture[i]))
            UnloadTexture(g_Entities->m_Texture[i]);
    }
    MemFree(g_Entities);
}
