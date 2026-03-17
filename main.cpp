#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

int main(int, char**) {
    std::cout << "Hello, World!" << std::endl;
    // SDL初始化
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // 创建窗口
    SDL_Window *window = SDL_CreateWindow("Hello World!", 800, 600, 0);
    // 创建渲染器
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    // SDL3_Image不需要手动初始化

    // 加载图片
    SDL_Texture *texture = IMG_LoadTexture(renderer, "assets/image/bg.png");

    // SDL_Mixer初始化
    if (!MIX_Init()) {
        std::cerr << "MIX_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // 创建Mixer
    MIX_Mixer *mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

    // 创建针对音乐的音轨
    MIX_Track *music_track = MIX_CreateTrack(mixer);

    // 读取音乐数据(第一个参数可以为空)
    MIX_Audio *music_data = MIX_LoadAudio(mixer, "assets/music/03_Racing_Through_Asteroids_Loop.ogg", false);
    // 将音乐数据加载到音轨中
    MIX_SetTrackAudio(music_track, music_data);
    // 播放音乐(播放一次)
    // MIX_PlayTrack(music_track, 0);

    // 播放音乐（无限循环）
    SDL_PropertiesID play_props = SDL_CreateProperties();   // 创建一个空的属性容器
    SDL_SetNumberProperty(play_props, MIX_PROP_PLAY_LOOPS_NUMBER, -1);  // 设置循环次数为-1，表示无限循环
    MIX_PlayTrack(music_track, play_props);  // 播放音轨，传入属性容器
    SDL_DestroyProperties(play_props);  // 播放后可以销毁属性容器，Mixer会复制需要的数据

    // 读取音效数据
    MIX_Audio *effect_data = MIX_LoadAudio(mixer, "assets/sound/eff5.wav", true);

    // SDL_TTF初始化
    if (!TTF_Init()) {
        std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // 加载字体
    TTF_Font *font = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf", 24);

    // 创建文本纹理
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, "Hello, SDL! 中文也可以", 0, color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, surface);

    // Do something with the window and renderer here...
    // 渲染循环
    while (true) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                break;
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                // 播放音效
                MIX_PlayAudio(mixer, effect_data);
            }
        }

        // 清屏
        SDL_RenderClear(renderer);
        // 画一个长方形
        SDL_FRect rect = {100, 100, 200, 200};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        

        // 画图片
        SDL_FRect dstrect = {200, 200, 200, 200};
        SDL_RenderTexture(renderer, texture, NULL, &dstrect);

        // 画文本
        SDL_FRect textRect = {300, 300, static_cast<float>(surface->w), static_cast<float>(surface->h)};
        SDL_RenderTexture(renderer, textTexture, NULL, &textRect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 

        // 更新屏幕
        SDL_RenderPresent(renderer);
        

        
    }

    // 清理图片资源
    SDL_DestroyTexture(texture);

    // 清理音乐资源
    MIX_DestroyAudio(music_data);   // 销毁音乐数据
    // MIX_DestroyTrack(music_track);   // 销毁音轨
    MIX_DestroyMixer(mixer);    // 销毁Mixer设备
    MIX_Quit();

    // 清理字体资源
    SDL_DestroySurface(surface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    TTF_Quit();

    // 清理并退出
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}