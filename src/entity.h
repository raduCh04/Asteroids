#pragma once

#include <raylib.h>
#include <stdint.h>

constexpr uint32_t kMaxEntities = 0xFFF;

enum { PLAYER_ID = 0 };

enum class EntityType
{
    None = 0,
    Player = 1,
    Asteroid = 2,
    Bullet = 3,
};

struct Entity
{
    Texture2D m_Texture[kMaxEntities];
    Rectangle m_Source[kMaxEntities];
    Rectangle m_Destination[kMaxEntities];

    Vector2 m_Position[kMaxEntities];
    Vector2 m_Velocity[kMaxEntities];

    int32_t m_Health[kMaxEntities];
    int32_t m_ID[kMaxEntities];

    EntityType m_Type[kMaxEntities];
};

extern Entity *g_Entities;

void InitEntities();
void HandleEntities(float dt);
void DestroyEntities();