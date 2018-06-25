#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "../utils/SDL/SDL_Singleton.h"

#include "Panel.h"

class Interface {
public:
    Interface();
    ~Interface();
public:
    void EventHandler( SDL_Event& );
    bool GetQuit() const;
    void Draw();
private:
    void Init();
    void DeInit();
private:
    bool readyToQuit;

    SDL_Singleton renderTool;

    Panel* panel;
};

#endif //__INTERFACE_H__