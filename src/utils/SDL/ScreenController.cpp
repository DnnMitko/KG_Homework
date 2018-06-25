#include "ScreenController.h"

SDL_Wrapper* ScreenController::singleton = NULL;

ScreenController::ScreenController() {
}

ScreenController::~ScreenController() {
}

SDL_Wrapper* ScreenController::getInstance() {
    if( NULL == singleton ) {
        singleton = new SDL_Wrapper();
    }

    return singleton;
}