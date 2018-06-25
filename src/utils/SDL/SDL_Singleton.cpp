#include "SDL_Singleton.h"

SDL_Wrapper* SDL_Singleton::ScreenController = NULL;

SDL_Singleton::SDL_Singleton() {
}

SDL_Singleton::~SDL_Singleton() {
}

SDL_Wrapper* SDL_Singleton::getScreenController() {
    if( NULL == ScreenController ) {
        ScreenController = new SDL_Wrapper();
    }

    return ScreenController;
}