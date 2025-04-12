#ifndef OBJECT_H
#define OBJECT_H
#include <SDL.h>

enum class ItemType{
    Life,
    Shield,
    Time
};

struct Player{
    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0, 0};
    int width = 0;
    int height = 0;
    int speed = 500;
    int currentHealth = 3;
    int maxHealth = 3;
    Uint32 coolDown = 150;
    Uint32 lastShootTime = 0;
};

struct Enemy{
    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0, 0};
    int width = 0;
    int height = 0;
    int speed = 150;
    int currentHealth = 2;
    Uint32 coolDown = 1500;
    Uint32 lastShootTime = 0;
};

struct ProjectilePlayer{
    SDL_Texture* texture = nullptr;
    ProjectilePlayer* next = nullptr;
    SDL_FPoint position = {0, 0};
    int width = 0;
    int height = 0;
    int speed = 800;
    int damage = 1;
};

struct ProjectileEnemy{
    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0, 0};
    SDL_FPoint direction = {0, 0};
    int width = 0;
    int height = 0;
    int speed = 400;
    int damage = 1;
};

struct Explosion{
    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0, 0};
    int width = 0;
    int height = 0;
    int currentFrame = 0;
    int totlaFrame = 0;
    Uint32 startTime = 0;
    Uint32 FPS = 10;
};

struct Item{
    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0, 0};
    SDL_FPoint direction = {0, 0};
    int width = 0;
    int height = 0;
    int speed = 200;
    int bounceCount = 3;
    ItemType type = ItemType::Life;
};

struct Background{
    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0, 0};
    float offset = 0;
    int width = 0;
    int height = 0;
    int speed = 30;
};

#endif // OBJECT_H