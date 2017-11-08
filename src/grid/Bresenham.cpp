#include "Grid.h"

void Grid::CalcBresenham( MousePair coords )
{
    int x1, x2;
    int iRun;
    
    x1 = coords.begin.x;
    x2 = coords.end.x;

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
    SortY( coords );

    int x = coords.begin.x;
    int y1 = coords.begin.y;
    int y2 = coords.end.y;

    int iX = x;

    for( int iY = y1; iY <= y2; iY += m_iPixelSize )
    {
        SetPixel( iX, iY );
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

    if( fSlope >= -1 && fSlope <= 1 )
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

    int iThreshold = ( y1 - m_GridPos.y ) % m_iPixelSize;
    if( fSlope > 0 )
    {
        iThreshold = m_iPixelSize - iThreshold;
    }
    
    int iY = y1;
    for( int iX = x1; iX <= x2; iX += m_iPixelSize )
    {
        SetPixel( iX, iY );

        fOffset += fDelta * m_iPixelSize;

        if( fOffset >= iThreshold )
        {
            iY += iDirection * m_iPixelSize;
            iThreshold += m_iPixelSize;
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

    int iThreshold = ( x1 - m_GridPos.x ) % m_iPixelSize;
    if( fSlope > 0 )
    {
        iThreshold = m_iPixelSize - iThreshold;
    }

    int iX = x1;
    for( int iY = y1; iY <= y2; iY += m_iPixelSize )
    {
        SetPixel( iX, iY );
        
        fOffset += fDelta * m_iPixelSize;

        if( fOffset >= iThreshold )
        {
            iX += iDirection * m_iPixelSize;
            iThreshold += m_iPixelSize;
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

void Grid::DrawBresenham( MousePair coords )
{
    int x1, x2;
    int iRun;
    
    x1 = coords.begin.x;
    x2 = coords.end.x;

    iRun = x2 - x1;

    if( iRun == 0 )
    {
        DrawVertical( coords );
    }
    else
    {
        DrawSlope( coords );
    }
}

void Grid::DrawVertical( MousePair coords )
{
    SortY( coords );
    
    int x = coords.begin.x;
    int y1 = coords.begin.y;
    int y2 = coords.end.y;

    int iX = x;

    for( int iY = y1; iY <= y2; iY++ )
    {
        DrawPixel( iX, iY );
    }
}

void Grid::DrawSlope( MousePair coords )
{
    int x1 = coords.begin.x;
    int y1 = coords.begin.y;
    int x2 = coords.end.x;
    int y2 = coords.end.y;

    int iRise = y2 - y1;
    int iRun = x2 - x1;

    float fSlope = iRise / (float)iRun;

    if( fSlope >= -1 && fSlope <= 1 )
    {
        DrawSlopeNormal( coords, fSlope );
    }
    else
    {
        DrawSlopeInverse( coords );
    }
}

void Grid::DrawSlopeNormal( MousePair coords, float fSlope )
{
    SortX( coords );
    
    int x1 = coords.begin.x;
    int y1 = coords.begin.y;
    int x2 = coords.end.x;
    int y2 = coords.end.y;

    int iRise = y2 - y1;
    int iRun = x2 - x1;

    int iIncrement = ( fSlope >= 0 ) ? 1 : -1;

    // float fDelta = fabsf( fSlope );  * abs( iRun ) * 2
    int iDelta = abs( iRise ) * 2;

    int iOffset = 0;

    // float fThreshold = 0.5;          * abs( iRun ) * 2
    int iThreshold = abs( iRun );

    int iThresholdInc = abs( iRun ) * 2;
    
    int iY = y1;
    for( int iX = x1; iX <= x2; iX++ )
    {
        DrawPixel( iX, iY );

        iOffset += iDelta;

        if( iOffset >= iThreshold )
        {
            iY += iIncrement;
            // fThreshold += 1;         * abs( iRun ) * 2
            iThreshold += iThresholdInc;
        }
    }
}

void Grid::DrawSlopeInverse( MousePair coords )
{
    SortY( coords );
    
    int x1 = coords.begin.x;
    int y1 = coords.begin.y;
    int x2 = coords.end.x;
    int y2 = coords.end.y;

    int iRise = y2 - y1;
    int iRun = x2 - x1;

    float fSlope = iRun / (float)iRise;

    int iIncrement = ( fSlope >= 0 ) ? 1 : -1;

    // float fDelta = fabsf( fSlope );  * abs( iRise ) * 2
    int iDelta = abs( iRun ) * 2;

    int iOffset = 0;

    // float fThreshold = 0.5;          * abs( iRise ) * 2
    int iThreshold = abs( iRise );

    int iThresholdInc = abs( iRise ) * 2;
    
    int iX = x1;
    for( int iY = y1; iY <= y2; iY++ )
    {
        DrawPixel( iX, iY );

        iOffset += iDelta;

        if( iOffset >= iThreshold )
        {
            iX += iIncrement;
            // fThreshold += 1;         * abs( iRise ) * 2
            iThreshold += iThresholdInc;
        }
    }
}