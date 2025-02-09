#ifndef SCENE_H
#define SCENE_H

#include <SDL3/SDL.h>

class Game;

class Scene{
public:
    Scene();
    virtual ~Scene() = default;

    virtual void init() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void clean() = 0;
    virtual void handleEvent(SDL_Event* event) = 0;
protected:
    Game& game;
};

#endif // SCENE_H