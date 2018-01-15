#ifndef __GRID_H__
#define __GRID_H__

#include "SDL2/SDL.h"

#include "../pugixml/pugixml.hpp"

#include "spline/spline.h"

#include <vector>
#include <stack>
#include <cmath>

using std::vector;
using std::stack;

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
    struct SpreadMap
    {
        stack<MouseClick> points;
        bool isFinished;
    };
public:
    enum State
    {
        Bresenham,
        Michener,
        BoundryFill,
        Spline,
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
    void DrawSim( bool );

    void ClearStatus();

    bool IsInGrid( MouseClick );
    void AddClick( MouseClick );

    void Calculate( MousePair );
    void Recalculate();

    void DrawPixel( int, int );
    void SetPixel( int, int, char = '1' );
    void SetPixelByIndex( int, int );
    char GetPixelStatus( int, int );

    void SetPixelOctant( MouseClick, int, int );
    void DrawPixelOctant( MouseClick, int, int );

    void SortUpX( MousePair& );
    void SortUpY( MousePair& );
    void SortDownX( MousePair& );
    void SortDownY( MousePair& );

    void SplitLineDraw( MousePair );
    void SplitLineSet( MousePair );

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
    
    // SetBresenham.cpp
    void SetBresenham( MousePair );
    void SetVertical( MousePair );
    void SetSlope( MousePair );
    void SetSlopeNormal( MousePair, float );
    void SetSlopeInverse( MousePair );

    // SetRevBresenham.cpp
    void SetRevBresenham( MousePair );
    void SetRevVertical( MousePair );
    void SetRevSlope( MousePair );
    void SetRevSlopeNormal( MousePair, float );
    void SetRevSlopeInverse( MousePair );

    // DrawMichener.cpp
    void DrawMichener( MousePair );
    void DrawCircle( MouseClick, int );

    // SetMichener.cpp
    void SetMichener( MousePair );
    void SetCircle( MouseClick, int );

    // Boundry_Full.cpp
    void DrawExpansion();
    void Expand( SpreadMap& );
    void ProcessPoint( SpreadMap& );
    void DrawRow( int, int, int );

    // Spline.cpp
    void DrawLargeDot( int, int );
    void DrawSpline();
    void DrawCurve( tk::spline& );
private:
    SDL_Renderer* m_Renderer;

    pugi::xml_document* m_xmlConstants;

    State m_eCurState;

    bool m_bHasChanged;

    SDL_Rect m_GridPos;
    int m_iPixelSize;

    bool m_bUseNormalBresenham;
    
    bool m_bReadyToDrawSpline;

    char** m_ppbPixelStatus;
    int m_iPixelCountWidth;
    int m_iPixelCountHeight;

    vector<MousePair>* m_pvMousePairs;

    vector<SpreadMap>* m_pvSpreadMaps;

    vector<MouseClick>* m_pvMouseClicks;
};

#endif //__GRID_H__