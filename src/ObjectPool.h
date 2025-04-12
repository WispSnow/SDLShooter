#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include "Object.h"
#include <vector>
// 模版类

template<typename T>
class ObjectPool{
private:
    size_t poolSize;
    std::vector<T> pool;
    T* firstAvailable = nullptr;

public:
    // 构造函数（决定池子大小，并创建连续对象）
    ObjectPool(T Prototype, size_t pool_size = 20):poolSize(pool_size){
        // pool.resize(poolSize);      // reserve: 预留空间，但是vector的大小不变； resize: 不仅预留空间，而且改变vector的大小, 在这里用默认的初始化方法
        pool.resize(poolSize, Prototype); // 预留空间，并用原型对象初始化
        firstAvailable = &pool[0];
        for (size_t i = 0; i < poolSize - 1; i++){
            pool[i].next = &pool[i + 1];    // 角标不能超过poolSize - 1
        }
        pool[poolSize - 1].next = nullptr;
    }

	// 一个用来获取对象的函数（指针指向可用对象，然后链表删除节点）
    T* create(){
        if (firstAvailable == nullptr){
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "No more objects in pool");
            return nullptr;
        }
        T* result = firstAvailable;
        firstAvailable = firstAvailable->next;
        return result;
    }

    // 一个用来放回对象的函数（链表插入节点）
    void release(T* object){
        object->next = firstAvailable;
        firstAvailable = object;
    }
};

#endif
