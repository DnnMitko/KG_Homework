#ifndef __GRID_H__
#define __GRID_H__

#include "SDL2/SDL.h"

#include "../pugixml/pugixml.hpp"

#include <vector>

using std::vector;

class Grid
{
    struct MousePair
    {
        MousePair() : x( -1 ), y( -1 ) {}
        int x;
        int y;
    };
public:
    Grid();
    ~Grid();
public:
    bool Init( pugi::xml_document*, SDL_Renderer* );

    void Draw();
    void EventHandler( SDL_Event& );
private:
    SDL_Renderer* m_Renderer;

    SDL_Rect m_GridPos;
    unsigned int m_uiPixelSize;

    bool** m_ppbPixelStatus;
    unsigned int m_uiPixelCountWidth;
    unsigned int m_uiPixelCountHeight;

    vector<MousePair>* m_pvMouseClicks;
};

#endif //__GRID_H__