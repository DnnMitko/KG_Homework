#ifndef __SCREENCONTROLLER_H__
#define __SCREENCONTROLLER_H__

#include "SDL_Wrapper.h"

class ScreenController {
public:
    ScreenController();
    ~ScreenController();
public:
    static SDL_Wrapper* getInstance();
private:
    static SDL_Wrapper* singleton;
};

#endif //__SCREENCONTROLLER_H__