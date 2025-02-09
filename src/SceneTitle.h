#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "Scene.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

class SceneTitle : public Scene
{
public:
    virtual void init() override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void clean() override;
    virtual void handleEvent(SDL_Event* event) override;

private:
    Mix_Music* bgm; // 背景音乐
    float timer = 0.0f; // 计时器
};



#endif // SCENE_TITLE_H