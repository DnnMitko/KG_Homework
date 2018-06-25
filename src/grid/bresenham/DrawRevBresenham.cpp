#include "Grid.h"

void Grid::DrawRevBresenham( MousePair coords ) {
    int x1, x2;
    int iRun;

    x1 = coords.begin.x;
    x2 = coords.end.x;

    iRun = x2 - x1;

    if( iRun == 0 ) {
        DrawRevVertical( coords );
    }
    else {
        DrawRevSlope( coords );
    }
}

void Grid::DrawRevVertical( MousePair coords ) {
    SortDownY( coords );
    
    int x = coords.begin.x;
    int y1 = coords.begin.y;
    int y2 = coords.end.y;

    int iX = x;

    for( int iY = y1; iY >= y2; iY-- ) {
        DrawPixel( iX, iY );
    }
}

void Grid::DrawRevSlope( MousePair coords ) {
    int x1 = coords.begin.x;
    int y1 = coords.begin.y;
    int x2 = coords.end.x;
    int y2 = coords.end.y;

    int iRise = y2 - y1;
    int iRun = x2 - x1;

    float fSlope = iRise / (float)iRun;

    if( fSlope >= -1 && fSlope <= 1 ) {
        DrawRevSlopeNormal( coords, fSlope );
    }
    else {
        DrawRevSlopeInverse( coords );
    }
}

void Grid::DrawRevSlopeNormal( MousePair coords, float fSlope ) {
    SortDownX( coords );

    int x1 = coords.begin.x;
    int y1 = coords.begin.y;
    int x2 = coords.end.x;
    int y2 = coords.end.y;

    int iRise = y2 - y1;
    int iRun = x2 - x1;

    int iIncrement = ( fSlope <= 0 ) ? 1 : -1;

    // float fDelta = fabsf( fSlope );  * abs( iRun ) * 2
    int iDelta = abs( iRise ) * 2;

    int iOffset = 0;

    // float fThreshold = 0.5;          * abs( iRun ) * 2
    int iThreshold = abs( iRun );

    int iThresholdInc = abs( iRun ) * 2;

    int iY = y1;
    for( int iX = x1; iX >= x2; iX-- ) {
        DrawPixel( iX, iY );

        iOffset += iDelta;

        if( iOffset >= iThreshold ) {
            iY += iIncrement;
            // fThreshold += 1;         * abs( iRun ) * 2
            iThreshold += iThresholdInc;
        }
    }
}

void Grid::DrawRevSlopeInverse( MousePair coords ) {
    SortDownY( coords );

    int x1 = coords.begin.x;
    int y1 = coords.begin.y;
    int x2 = coords.end.x;
    int y2 = coords.end.y;

    int iRise = y2 - y1;
    int iRun = x2 - x1;

    float fSlope = iRun / (float)iRise;

    int iIncrement = ( fSlope <= 0 ) ? 1 : -1;

    // float fDelta = fabsf( fSlope );  * abs( iRise ) * 2
    int iDelta = abs( iRun ) * 2;

    int iOffset = 0;

    // float fThreshold = 0.5;          * abs( iRise ) * 2
    int iThreshold = abs( iRise );

    int iThresholdInc = abs( iRise ) * 2;

    int iX = x1;
    for( int iY = y1; iY >= y2; iY-- ) {
        DrawPixel( iX, iY );

        iOffset += iDelta;

        if( iOffset >= iThreshold ) {
            iX += iIncrement;
            // fThreshold += 1;         * abs( iRise ) * 2
            iThreshold += iThresholdInc;
        }
    }
}