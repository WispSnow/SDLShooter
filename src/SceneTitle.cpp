#include "SceneTitle.h"
#include "SceneMain.h"
#include "Game.h"
#include <string>

void SceneTitle::init()
{
    //载入并播放背景音乐
    bgm = MIX_LoadAudio(game.getMixer(), "assets/music/06_Battle_in_Space_Intro.ogg", false);
    if (bgm == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load music: %s", SDL_GetError());
    }
    bgmTrack = MIX_CreateTrack(game.getMixer());
    MIX_SetTrackAudio(bgmTrack, bgm);
    MIX_SetTrackGain(bgmTrack, 2.0f);
    MIX_SetTrackLoops(bgmTrack, -1);
    MIX_PlayTrack(bgmTrack, 0);

}

void SceneTitle::update(float deltaTime)
{
    timer += deltaTime;
    if (timer > 1.0f){
        timer -= 1.0f;
    }
}

void SceneTitle::render()
{
    //渲染标题文字
    std::string titleText = "SDL太空战机";
    game.renderTextCentered(titleText, 0.4, true);

    //渲染普通文字
    if (timer < 0.5f){
        std::string instructions = "按 J 键开始游戏";
        game.renderTextCentered(instructions, 0.8, false);
    }

}

void SceneTitle::clean()
{
    if (bgmTrack != nullptr){
        MIX_StopTrack(bgmTrack, 0);
        MIX_DestroyTrack(bgmTrack);
    }
    if (bgm != nullptr){
        MIX_DestroyAudio(bgm);
    }
}

void SceneTitle::handleEvent(SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN){
        if (event->key.scancode == SDL_SCANCODE_J){
            auto sceneMain = new SceneMain();
            game.changeScene(sceneMain);
        }
    }
}
