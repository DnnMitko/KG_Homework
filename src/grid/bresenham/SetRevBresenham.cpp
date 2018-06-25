#include "Grid.h"

void Grid::SetRevBresenham( MousePair coords ) {
    int x1, x2;
    int iRun;

    x1 = coords.begin.x;
    x2 = coords.end.x;

    iRun = x2 - x1;

    if( iRun == 0 ) {
        SetRevVertical( coords );
    }
    else {
        SetRevSlope( coords );
    }
}

void Grid::SetRevVertical( MousePair coords ) {
    SortDownY( coords );

    int x = coords.begin.x;
    int y1 = coords.begin.y;
    int y2 = coords.end.y;

    int iX = x;

    for( int iY = y1; iY >= y2; iY -= m_iPixelSize ) {
        SetPixel( iX, iY );
    }
}

void Grid::SetRevSlope( MousePair coords ) {
    int x1 = coords.begin.x;
    int y1 = coords.begin.y;
    int x2 = coords.end.x;
    int y2 = coords.end.y;

    int iRise = y2 - y1;
    int iRun = x2 - x1;

    float fSlope = iRise / (float)iRun;

    if( fSlope >= -1 && fSlope <= 1 ) {
        SetRevSlopeNormal( coords, fSlope );
    }
    else {
        SetRevSlopeInverse( coords );
    }
}

void Grid::SetRevSlopeNormal( MousePair coords, float fSlope ) {
    SortDownX( coords );

    int x1 = coords.begin.x;
    int y1 = coords.begin.y;
    int x2 = coords.end.x;

    int iDirection = ( fSlope <= 0 ) ? 1 : -1;

    float fDelta = fabsf( fSlope );

    float fOffset = 0;

    int iThreshold = ( y1 - m_GridPos.y ) % m_iPixelSize;
    if( fSlope < 0 ) {
        iThreshold = m_iPixelSize - iThreshold;
    }

    int iY = y1;
    for( int iX = x1; iX >= x2; iX -= m_iPixelSize ) {
        SetPixel( iX, iY );

        fOffset += fDelta * m_iPixelSize;

        if( fOffset >= iThreshold ) {
            iY += iDirection * m_iPixelSize;
            iThreshold += m_iPixelSize;
        }
    }
}

void Grid::SetRevSlopeInverse( MousePair coords ) {
    SortDownY( coords );

    int x1 = coords.begin.x;
    int y1 = coords.begin.y;
    int x2 = coords.end.x;
    int y2 = coords.end.y;

    int iRise = y2 - y1;
    int iRun = x2 - x1;

    float fSlope = iRun / (float)iRise;

    int iDirection = ( fSlope <= 0 ) ? 1 : -1;

    float fDelta = fabsf( fSlope );

    float fOffset = 0;

    int iThreshold = ( x1 - m_GridPos.x ) % m_iPixelSize;
    if( fSlope < 0 ) {
        iThreshold = m_iPixelSize - iThreshold;
    }

    int iX = x1;
    for( int iY = y1; iY >= y2; iY -= m_iPixelSize ) {
        SetPixel( iX, iY );
        
        fOffset += fDelta * m_iPixelSize;

        if( fOffset >= iThreshold ) {
            iX += iDirection * m_iPixelSize;
            iThreshold += m_iPixelSize;
        }
    }
}