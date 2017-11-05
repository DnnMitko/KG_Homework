#ifndef __HOMEWORK_H__
#define __HOMEWORK_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "../pugixml/pugixml.hpp"

#include <cstdio>

class Homework
{
    enum States
    {
        Bresenham,
        NumStates
    };
public:
    Homework();
    ~Homework();
public:
    void EventHandler( SDL_Event& );
    bool GetQuit() const;
    void Draw();
private:
    bool InitSDL();
    void DeInitSDL();

    void Create();
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

    bool m_bQuit;
    States m_eCurState;

    pugi::xml_document* m_xmlConstants;
};

#endif //__HOMEWORK_H__