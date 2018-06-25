#ifndef __SDL_SINGLETON_H__
#define __SDL_SINGLETON_H__

#include "SDL_Wrapper.h"

class SDL_Singleton {
public:
    SDL_Singleton();
    ~SDL_Singleton();
public:
    static SDL_Wrapper* getScreenController();
private:
    static SDL_Wrapper* ScreenController;
}

#endif //__SDL_SINGLETON_H__