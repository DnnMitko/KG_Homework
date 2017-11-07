#ifndef __HOMEWORK_H__
#define __HOMEWORK_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "../pugixml/pugixml.hpp"

#include "../grid/Grid.h"
#include "Button.h"

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

    //HomeworkButtons.cpp
    void CreateButtons();
    void PositionButtons();
    bool ButtonEvents( SDL_Event& );
    void ReleaseButtons();
    void DeleteButtons();
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

    bool m_bQuit;

    pugi::xml_document* m_xmlConstants;

    Grid* m_pGrid;

    Button* m_ButtonGridInitial;
    Button* m_ButtonGridVerySmall;
    Button* m_ButtonGridSmall;
    Button* m_ButtonGridMedium;
    Button* m_ButtonGridLarge;
    Button* m_ButtonGridVeryLarge;
};

#endif //__HOMEWORK_H__