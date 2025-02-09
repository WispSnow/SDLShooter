#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "Scene.h"
#include "Object.h"
#include <list>
#include <random>
#include <map>
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>


class Game;

class SceneMain : public Scene {
public:

    void update(float deltaTime) override;
    void render() override;
    void handleEvent(SDL_Event* event) override;
    void init() override;
    void clean() override;

private:
    Player player;
    Mix_Music* bgm;
    SDL_Texture* uiHealth;
    TTF_Font* scoreFont;
    int score = 0;
    float timerEnd = 0.0f;

    bool isDead = false; // 玩家是否死亡
    std::mt19937 gen; // 随机数生成器
    std::uniform_real_distribution<float> dis; // 随机数分布器
    // 创建每个物体的模版
    Enemy enemyTemplate;
    ProjectilePlayer projectilePlayerTemplate;
    ProjectileEnemy projectileEnemyTemplate;
    Explosion explosionTemplate;
    Item itemLifeTemplate;

    // 创建每个物体的容器
    std::list<Enemy*> enemies;
    std::list<ProjectilePlayer*> projectilesPlayer;
    std::list<ProjectileEnemy*> projectilesEnemy;
    std::list<Explosion*> explosions;
    std::list<Item*> items;
    std::map<std::string, Mix_Chunk*> sounds; // 存储音效
    
    // 渲染相关
    void renderItems();
    void renderUI();
    void renderExplosions();
    void renderPlayerProjectiles();
    void renderEnemyProjectiles();
    void renderEnemies();

    // 更新相关
    void updateEnemies(float deltaTime);
    void updateEnemyProjectiles(float deltaTime);
    void updatePlayer(float deltaTime);
    void updateItems(float deltaTime);
    void updateExplosions(float deltaTime);
    void updatePlayerProjectiles(float deltaTime);
    void keyboardControl(float deltaTime);
    void spawEnemy();
    void changeSceneDelayed(float deltaTime, float delay);

    // 其它
    void playerGetItem(Item* item);
    void shootPlayer();
    void shootEnemy(Enemy* enemy);
    SDL_FPoint getDirection(Enemy* enemy);
    void enemyExplode(Enemy* enemy);
    void dropItem(Enemy* enemy);
    
};


#endif // SCENE_MAIN_H