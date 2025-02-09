#include "Game.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <fstream>


Game::Game()
{
}

Game::~Game()
{
    saveData(); // Save data before closing
    clean();
}

void Game::run()
{
    while (isRunning)
    {
        auto frameStart = SDL_GetTicks();
        SDL_Event event;
        handleEvent(&event);
        update(deltaTime);
        render();
        auto frameEnd = SDL_GetTicks();
        auto diff = frameEnd - frameStart;
        if (diff < frameTime){
            SDL_Delay(frameTime - diff);
            deltaTime = frameTime / 1000.0f;
        }
        else{
            deltaTime = diff / 1000.0f;
        }
    }
    
}

void Game::init()
{
    frameTime = 1000 / FPS;
    // SDL 初始化
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    // 创建窗口
    window = SDL_CreateWindow("SDL Tutorial", windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    // 创建渲染器
    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    // 设置逻辑分辨率
    SDL_SetRenderLogicalPresentation(renderer, windowWidth, windowHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // 初始化SDL_mixer
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    
    // 打开音频设备
    if (!Mix_OpenAudio(0, NULL)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_mixer could not open audio! SDL_mixer Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    // 设置音效channel数量
    Mix_AllocateChannels(32);

    // 设置音乐音量
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    Mix_Volume(-1, MIX_MAX_VOLUME / 8);

    // 初始化SDL_ttf
    if (!TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", SDL_GetError());
        isRunning = false;
    }

    // 初始化背景卷轴
    nearStars.texture = IMG_LoadTexture(renderer, "assets/image/Stars-A.png");
    if (nearStars.texture == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_image could not initialize! SDL_image Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    SDL_GetTextureSize(nearStars.texture, &nearStars.width, &nearStars.height);   
    nearStars.height /= 2;
    nearStars.width /= 2;

    farStars.texture = IMG_LoadTexture(renderer, "assets/image/Stars-B.png");
    if (farStars.texture == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_image could not initialize! SDL_image Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    SDL_GetTextureSize(farStars.texture, &farStars.width, &farStars.height);
    farStars.height /= 2;
    farStars.width /= 2;
    farStars.speed = 20;

    // 载入字体
    titleFont = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf", 64);
    textFont = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf", 32);
    if (titleFont == nullptr || textFont == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_OpenFont: %s\n", SDL_GetError());
        isRunning = false;
    }

    // 载入得分
    loadData();

    currentScene = new SceneTitle();
    currentScene->init();
}

void Game::clean()
{
    if (currentScene != nullptr)
    {
        currentScene->clean();
        delete currentScene;
    }
    if (nearStars.texture != nullptr){
        SDL_DestroyTexture(nearStars.texture);
    }
    if (farStars.texture != nullptr){
        SDL_DestroyTexture(farStars.texture);
    }
    if (titleFont != nullptr){
        TTF_CloseFont(titleFont);
    }
    if (textFont != nullptr){
        TTF_CloseFont(textFont);
    }

    // 清理SDL_mixer
    Mix_CloseAudio();
    Mix_Quit();
    // 清理SDL_ttf
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::changeScene(Scene *scene)
{
    if (currentScene != nullptr)
    {
        currentScene->clean();
        delete currentScene;
    }
    currentScene = scene;
    currentScene->init();
}

void Game::handleEvent(SDL_Event *event)
{
    while (SDL_PollEvent(event))
    {
        if (event->type == SDL_EVENT_QUIT)
        {
            isRunning = false;
        }
        if (event->type == SDL_EVENT_KEY_DOWN){
            if (event->key.scancode == SDL_SCANCODE_F4){
                isFullscreen = !isFullscreen;
                if (isFullscreen){
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                }else{
                    SDL_SetWindowFullscreen(window, 0);
                }
            }
        }
        currentScene->handleEvent(event);
    }
}

void Game::update(float deltaTime)
{
    backgroundUpdate(deltaTime);
    currentScene->update(deltaTime);
}

void Game::render()
{
    // 清空
    SDL_RenderClear(renderer);
    // 渲染星空背景
    renderBackground();

    currentScene->render();
    // 显示更新
    SDL_RenderPresent(renderer);
}

SDL_FPoint Game::renderTextCentered(std::string text, float posY, bool isTitle)
{
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface;
    if (isTitle){
        surface = TTF_RenderText_Solid(titleFont, text.c_str(), 0, color);
    }else{
        surface = TTF_RenderText_Solid(textFont, text.c_str(), 0, color);
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    float y = (getWindowHeight() - surface->h) * posY;
    SDL_FRect rect = {getWindowWidth() / 2 - surface->w / 2,
                     y,
                     static_cast<float>(surface->w),
                     static_cast<float>(surface->h)};
    SDL_RenderTexture(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
    return {rect.x + rect.w, y};
}

void Game::renderTextPos(std::string text, float posX, float posY, bool isLeft)
{
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(textFont, text.c_str(), 0, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FRect rect;
    if (isLeft){
        rect = {posX, posY, static_cast<float>(surface->w), static_cast<float>(surface->h)};
    }else{
        rect = {getWindowWidth() - posX - static_cast<float>(surface->w), posY, static_cast<float>(surface->w), static_cast<float>(surface->h)};
    }
    SDL_RenderTexture(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

void Game::backgroundUpdate(float deltaTime)
{
    nearStars.offset += nearStars.speed * deltaTime;
    if (nearStars.offset >= 0)
    {
        nearStars.offset -= nearStars.height;
    }

    farStars.offset += farStars.speed * deltaTime;
    if (farStars.offset >= 0){
        farStars.offset -= farStars.height;
    }
}

void Game::renderBackground()
{
    // 渲染远处的星星
    for (float posY = farStars.offset; posY < getWindowHeight(); posY += farStars.height){
        for (float posX = 0; posX < getWindowWidth(); posX += farStars.width){
            SDL_FRect ds = {posX, posY, farStars.width, farStars.height};
            SDL_RenderTexture(renderer, farStars.texture, NULL, &ds);
        }
    }
    // 渲染近处的星星
    for (float posY = nearStars.offset; posY < getWindowHeight(); posY += nearStars.height)
    {
        for (float posX = 0; posX < getWindowWidth(); posX += nearStars.width)
        {
            SDL_FRect dstRect = {posX, posY, nearStars.width, nearStars.height};
            SDL_RenderTexture(renderer, nearStars.texture, NULL, &dstRect);
        }
        
    }
}

void Game::saveData()
{
    // 保存得分榜的数据
    std::ofstream file("assets/save.dat");
    if (!file.is_open()){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open save file");
        return;
    }
    for (const auto &entry : leaderBoard){
        file << entry.first << " " << entry.second << std::endl;
    }
}

void Game::loadData()
{
    // 加载得分榜的数据
    std::ifstream file("assets/save.dat");
    if (!file.is_open()){
        SDL_Log("Failed to open save file");
        return;
    }
    leaderBoard.clear();
    int score;
    std::string name;
    while (file >> score >> name){
        leaderBoard.insert({score, name});
    }
}

void Game::insertLeaderBoard(int score, std::string name)
{
    leaderBoard.insert({score, name});
    if (leaderBoard.size() > 8){
        leaderBoard.erase(--leaderBoard.end());
    }
}
