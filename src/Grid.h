#ifndef __GRID_H__
#define __GRID_H__

#include "SDL2/SDL.h"

#include "pugixml/pugixml.hpp"

#include <vector>

using std::vector;

class Grid
{
    enum States
    {
        Bresenham,
        NumStates
    };
    
    struct MouseClick
    {
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
    void Init( pugi::xml_document*, SDL_Renderer* );

    void Draw();
    void EventHandler( SDL_Event& );
private:
    void DrawGrid();
    void DrawPixelStatus();
    void DrawLines();

    void ClearStatus();

    bool IsInGrid( MouseClick );
    void AddClick( MouseClick );

    void Calculate();
    void Recalculate();
    void PutPixel( int, int );

    // Bresenham
    void SetVertical( int, int, int );
    void SetSlope( int, int, int, int );
    void SetSlopeNormal( int, int, int, int, float );
    void SetSlopeInverse( int, int, int, int );
private:
    SDL_Renderer* m_Renderer;

    States m_eCurState;

    bool m_bHasChanged;

    SDL_Rect m_GridPos;
    unsigned int m_uiPixelSize;

    bool** m_ppbPixelStatus;
    unsigned int m_uiPixelCountWidth;
    unsigned int m_uiPixelCountHeight;

    vector<MousePair>* m_pvMouseClicks;
};

#endif //__GRID_H__