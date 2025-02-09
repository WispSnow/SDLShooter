#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include "Object.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <map>

class Game
{
public:
    static Game& getInstance(){
        static Game instance;
        return instance;
    }

    ~Game();
    void run();
    void init();
    void clean();
    void changeScene(Scene* scene);

    void handleEvent(SDL_Event *event);
    void update(float deltaTime);
    void render();

    // 渲染文字函数
    SDL_FPoint renderTextCentered(std::string text, float posY, bool isTitle);
    void renderTextPos(std::string text, float posX, float posY, bool isLeft = true);

    // setters
    void setFinalScore(int score) { finalScore = score; }
    void insertLeaderBoard(int score, std::string name); // 插入排行榜

    // getters
    SDL_Window* getWindow() { return window; }
    SDL_Renderer* getRenderer() { return renderer; }
    float getWindowWidth() { return windowWidth; }
    float getWindowHeight() { return windowHeight; }
    int getFinalScore() { return finalScore; }
    std::multimap<int, std::string, std::greater<int>>& getLeaderBoard() { return leaderBoard;} // 返回leaderBoard的引用
private:
    Game();
    // 删除拷贝与赋值构造函数
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    TTF_Font* titleFont;
    TTF_Font* textFont;

    bool isRunning = true;
    bool isFullscreen = false;
    Scene* currentScene = nullptr;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    float windowWidth = 600;
    float windowHeight = 800;
    int FPS = 60;
    Uint32 frameTime;
    float deltaTime;
    int finalScore = 0;

    Background nearStars;
    Background farStars;

    std::multimap<int, std::string, std::greater<int>> leaderBoard; // 使用multimap来存储分数和名字，分数作为键，名字作为值

    void backgroundUpdate(float deltaTime);
    void renderBackground();
    void saveData();
    void loadData();
};

#endif


