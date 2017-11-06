#ifndef __GRID_H__
#define __GRID_H__

#include "SDL2/SDL.h"

#include "../pugixml/pugixml.hpp"

#include <vector>

using std::vector;

class Grid
{
    struct MouseClick
    {
        MouseClick() : x( -1 ), y( -1 ) {}
        int x;
        int y;
    };

    struct MousePair
    {
        MouseClick begin;
        MouseClick end;
    };
public:
    Grid();
    ~Grid();
public:
    bool Init( pugi::xml_document*, SDL_Renderer* );

    void Draw();
    void EventHandler( SDL_Event& );
private:
    void DrawGrid();
    void DrawPixelStatus();
    void DrawLines();
private:
    SDL_Renderer* m_Renderer;

    bool m_bHasChanged;

    SDL_Rect m_GridPos;
    unsigned int m_uiPixelSize;

    bool** m_ppbPixelStatus;
    unsigned int m_uiPixelCountWidth;
    unsigned int m_uiPixelCountHeight;

    vector<MousePair>* m_pvMouseClicks;
};

#endif //__GRID_H__