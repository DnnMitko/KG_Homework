#ifndef __HOMEWORK_H__
#define __HOMEWORK_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "../pugixml/pugixml.hpp"

#include "Grid.h"

#include <cstdio>

class Homework
{
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

    pugi::xml_document* m_xmlConstants;

    Grid* m_pGrid;
};

#endif //__HOMEWORK_H__