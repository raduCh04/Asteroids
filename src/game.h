#pragma once

#include <raylib.h>

#include <stdint.h>

struct GameConfig
{
    uint32_t m_ScreenWidth;
    uint32_t m_ScreenHeight;
};

enum class GameState
{
    Paused = 0,
    Running,
    GameOver,
    Menu,
};

struct Game
{
    GameConfig m_Config;
    GameState m_State;
};

extern GameConfig g_Config; 