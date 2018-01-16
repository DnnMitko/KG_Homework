#include "../Grid.h"
#include "spline.h"

void Grid::DrawLargeDot( int x, int y ) {
    SDL_Rect rect;
    rect.x = x - 5;
    rect.y = y - 5;
    rect.w = 10;
    rect.h = 10;

    SDL_SetRenderDrawColor( m_Renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( m_Renderer, &rect );
}

void Grid::DrawSpline() {
    vector<double> X(5), Y(5);

    for( int i = 0; i < 5; i++ ) {
        X[i] = (*m_pvMouseClicks)[i].x;
        Y[i] = (*m_pvMouseClicks)[i].y;
        // DrawLargeDot( (*m_pvMouseClicks)[i].x, (*m_pvMouseClicks)[i].y );
    }

    tk::spline s;
    s.set_points(X,Y);

    DrawCurve( s );

    m_pvMouseClicks->clear();

    m_bReadyToDrawSpline = false;
}

void Grid::DrawCurve( tk::spline& s ) {
    for( int i = 125; i < 1225; i++ ) {
        DrawPixel( i, s(i) );
    }
}