#include "Grid.h"

void Grid::CalcBresenham( MousePair coords )
{
    int x1, y1, x2, y2;
    int iRun;
    
    x1 = coords.begin.x;
    y1 = coords.begin.y;
    x2 = coords.end.x;
    y2 = coords.end.y;

    iRun = x2 - x1;

    if( iRun == 0 )
    {
        SetVertical( coords );
    }
    else
    {
        SetSlope( coords );
    }
}

void Grid::SetVertical( MousePair coords )
{
    int x = coords.begin.x;
    int y1 = coords.begin.y;
    int y2 = coords.end.y;

    int iCol = ( x - m_GridPos.x ) / m_iPixelSize;

    int iRowStart, iRowEnd;

    if( y1 < y2 )
    {
        iRowStart = ( y1 - m_GridPos.y ) / m_iPixelSize;
        iRowEnd = ( y2 - m_GridPos.y ) / m_iPixelSize;
    }
    else
    {
        iRowStart = ( y2 - m_GridPos.y ) / m_iPixelSize;
        iRowEnd = ( y1 - m_GridPos.y ) / m_iPixelSize;
    }

    for( int iRow = iRowStart; iRow <= iRowEnd; iRow++ )
    {
        m_ppbPixelStatus[iCol][iRow] = true;
    }
}

void Grid::SetSlope( MousePair coords )
{
    int x1 = coords.begin.x;
    int y1 = coords.begin.y;
    int x2 = coords.end.x;
    int y2 = coords.end.y;

    int iRise = y2 - y1;
    int iRun = x2 - x1;

    float fSlope = iRise / (float)iRun;

    if( fSlope <= 1 && fSlope >= -1 )
    {
        SetSlopeNormal( coords, fSlope );
    }
    else
    {
        SetSlopeInverse( coords );
    }
}

void Grid::SetSlopeNormal( MousePair coords, float fSlope )
{
    SortX( coords );
    
    int x1 = coords.begin.x;
    int y1 = coords.begin.y;
    int x2 = coords.end.x;
    int y2 = coords.end.y;

    int iDirection = ( fSlope >= 0 ) ? 1 : -1;

    float fDelta = fabsf( fSlope );

    float fOffset = 0;

    float fThreshold = ( y1 - m_GridPos.y ) % m_iPixelSize;
    if( fSlope > 0 )
    {
        fThreshold = m_iPixelSize - fThreshold;
    }
    
    int iY = y1;
    for( int iX = x1; iX <= x2; iX += m_iPixelSize )
    {
        PutPixel( iX, iY );

        fOffset += fDelta * m_iPixelSize;
        if( fOffset > fThreshold )
        {
            iY += iDirection * m_iPixelSize;
            fThreshold += m_iPixelSize;
        }
    }
}

void Grid::SetSlopeInverse( MousePair coords )
{
    SortY( coords );

    int x1 = coords.begin.x;
    int y1 = coords.begin.y;
    int x2 = coords.end.x;
    int y2 = coords.end.y;

    int iRise = y2 - y1;
    int iRun = x2 - x1;

    float fSlope = iRun / (float)iRise;

    int iDirection = ( fSlope >= 0 ) ? 1 : -1;

    float fDelta = fabsf( fSlope );

    float fOffset = 0;

    float fThreshold = ( x1 - m_GridPos.x ) % m_iPixelSize;
    if( fSlope > 0 )
    {
        fThreshold = m_iPixelSize - fThreshold;
    }

    int iX = x1;
    for( int iY = y1; iY <= y2; iY += m_iPixelSize )
    {
        PutPixel( iX, iY );
        
        fOffset += fDelta * m_iPixelSize;
        if( fOffset >= fThreshold )
        {
            iX += iDirection * m_iPixelSize;
            fThreshold += m_iPixelSize;
        }
    }
}

void Grid::SortX( MousePair& coords )
{
    if( coords.begin.x > coords.end.x )
    {
        MouseClick temp = coords.begin;
        coords.begin = coords.end;
        coords.end = temp;
    }
}

void Grid::SortY( MousePair& coords )
{
    if( coords.begin.y > coords.end.y )
    {
        MouseClick temp = coords.begin;
        coords.begin = coords.end;
        coords.end = temp;
    }
}