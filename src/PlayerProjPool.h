#ifndef PLAYER_PROJ_POOL_H
#define PLAYER_PROJ_POOL_H

#include "Object.h"
#include <vector>

class PlayerProjPool{
private:
    int count = 0;
    size_t poolSize;
    std::vector<ProjectilePlayer> pool;
    ProjectilePlayer* firstAvailable = nullptr;

public:
    // 构造函数（决定池子大小，并创建连续对象）
    PlayerProjPool(ProjectilePlayer projectilePlayerPrototype, size_t pool_size = 20):poolSize(pool_size){
        pool.reserve(poolSize);
        firstAvailable = &pool[0];
        for (size_t i = 0; i < poolSize; i++){
            // 拷贝
            pool[i] = projectilePlayerPrototype;
            // 创建链表
            pool[i].next = &pool[i + 1];
        }
        pool[poolSize - 1].next = nullptr;
    }

	// 一个用来获取对象的函数（指针指向可用对象，然后链表删除节点）
    ProjectilePlayer* create(){
        if (firstAvailable == nullptr){
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "No more objects in pool");
            return nullptr;
        }
        ProjectilePlayer* result = firstAvailable;
        firstAvailable = firstAvailable->next;
        count++;
        SDL_Log("pool count: %d", count);
        return result;
    }

    // 一个用来放回对象的函数（链表插入节点）
    void release(ProjectilePlayer* object){
        object->next = firstAvailable;
        firstAvailable = object;
        count--;
    }
};

#endif