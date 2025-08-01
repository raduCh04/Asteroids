#include "entity.h"

#include <assert.h>

#include "game.h"

GameConfig g_Config = {
    .m_ScreenWidth = 1024,
    .m_ScreenHeight = 800,
};

Entity *g_Entities;
static uint32_t g_Level = 0;

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
   assert(false); 
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
}


#include <stdio.h>
static void HandlePlayer()
{
}

void HandleEntities(float dt)
{
    for (uint32_t i = 0; i < kMaxEntities; i++)
    {
        if (g_Entities->m_Health[i] <= 0)
            continue;
        
        if (i == 0)
        {
            if (IsKeyDown(KEY_W))
            {
                g_Entities->m_Velocity[i].y = -3 * dt;
            }
            else if (IsKeyDown(KEY_S))
            {
                g_Entities->m_Velocity[i].y = 3 * dt;
            }
            else
            {
                g_Entities->m_Velocity[i].y = 0;
            }

            if (IsKeyDown(KEY_A))
            {
                g_Entities->m_Velocity[i].x = -3 * dt;
            }
            else if (IsKeyDown(KEY_D))
            {
                g_Entities->m_Velocity[i].x = 3 * dt;
            }
            else
            {
                g_Entities->m_Velocity[i].x = 0;
            }
        }
        
        g_Entities->m_Position[i].x += g_Entities->m_Velocity[i].x;
        g_Entities->m_Position[i].y += g_Entities->m_Velocity[i].y;
        

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
