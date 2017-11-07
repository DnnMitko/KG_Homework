#ifndef __GRID_H__
#define __GRID_H__

#include "SDL2/SDL.h"

#include "../pugixml/pugixml.hpp"

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

    void SetGridScale( std::string );
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

    // Bresenham.cpp
    void CalcBresenham( MousePair );
    void SetVertical( MousePair );
    void SetSlope( MousePair );
    void SetSlopeNormal( MousePair, float );
    void SetSlopeInverse( MousePair );
    void SortX( MousePair& );
    void SortY( MousePair& );
private:
    SDL_Renderer* m_Renderer;

    pugi::xml_document* m_xmlConstants;

    States m_eCurState;

    bool m_bHasChanged;

    SDL_Rect m_GridPos;
    int m_iPixelSize;

    bool** m_ppbPixelStatus;
    unsigned int m_uiPixelCountWidth;
    unsigned int m_uiPixelCountHeight;

    vector<MousePair>* m_pvMouseClicks;
};

#endif //__GRID_H__