#ifndef __GRID_H__
#define __GRID_H__

#include "SDL2/SDL.h"

#include "../pugixml/pugixml.hpp"

#include <vector>
#include <cmath>

using std::vector;

class Grid
{
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
    enum State
    {
        Bresenham,
        NumStates
    };
public:
    Grid();
    ~Grid();
public:
    void Init( pugi::xml_document*, SDL_Renderer* );

    void Draw();
    void EventHandler( SDL_Event& );

    void SetState( State );

    void SetGridScale( std::string );
    void ClearGrid();

    bool ToggleDrawBresenham();
private:
    void DrawGrid();
    void DrawPixelStatus();
    void DrawLines( bool );

    void ClearStatus();

    bool IsInGrid( MouseClick );
    void AddClick( MouseClick );

    void Calculate( MousePair );
    void Recalculate();
    void SetPixel( int, int );
    void DrawPixel( int, int );

    void SortUpX( MousePair& );
    void SortUpY( MousePair& );
    void SortDownX( MousePair& );
    void SortDownY( MousePair& );

    // SetBresenham.cpp
    void SetBresenham( MousePair );
    void SetVertical( MousePair );
    void SetSlope( MousePair );
    void SetSlopeNormal( MousePair, float );
    void SetSlopeInverse( MousePair );

    // DrawBresenham.cpp
    void DrawBresenham( MousePair );
    void DrawVertical( MousePair );
    void DrawSlope( MousePair );
    void DrawSlopeNormal( MousePair, float );
    void DrawSlopeInverse( MousePair );

    // DrawRevBresenham.cpp
    void DrawRevBresenham( MousePair );
    void DrawRevVertical( MousePair );
    void DrawRevSlope( MousePair );
    void DrawRevSlopeNormal( MousePair, float );
    void DrawRevSlopeInverse( MousePair );
private:
    SDL_Renderer* m_Renderer;

    pugi::xml_document* m_xmlConstants;

    State m_eCurState;

    bool m_bHasChanged;

    SDL_Rect m_GridPos;
    int m_iPixelSize;

    bool m_bUseNormalBresenham;

    bool** m_ppbPixelStatus;
    unsigned int m_uiPixelCountWidth;
    unsigned int m_uiPixelCountHeight;

    vector<MousePair>* m_pvMousePairs;
};

#endif //__GRID_H__