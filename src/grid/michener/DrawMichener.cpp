#include "../Grid.h"

void Grid::DrawMichener( MousePair coords )
{
    int iDeltaX = coords.begin.x - coords.end.x;
    int iDeltaY = coords.begin.y - coords.end.y;

    float fRadius = sqrt( pow( iDeltaX, 2 ) + pow( iDeltaY, 2 ) );

    int iRadius = (int)fRadius;

    DrawCircle( coords.begin, iRadius );
}

void Grid::DrawCircle( MouseClick center, int iRadius )
{
    int iRelativeX = iRadius;
    int iRelativeY = 0;

    int iCheck = 1 - iRadius;

    while( iRelativeX >= iRelativeY )
    {
        DrawPixelOctant( center, iRelativeX, iRelativeY );

        iRelativeY++;

        if( iCheck < 0 )
        {
            iCheck += 2 * iRelativeY + 3;
        }
        else
        {
            iCheck += 2 * ( iRelativeY - iRelativeX ) + 1;

            iRelativeX--;
        }
    }
}