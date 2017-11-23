#include "../Grid.h"

void Grid::SetMichener( MousePair coords )
{
    int iDeltaX = coords.begin.x - coords.end.x;
    int iDeltaY = coords.begin.y - coords.end.y;

    float fRadius = sqrt( pow( iDeltaX, 2 ) + pow( iDeltaY, 2 ) );

    int iRadius = (int)fRadius;

    SetCircle( coords.begin, iRadius );
}

void Grid::SetCircle( MouseClick center, int iRadius )
{
    int iRelativeX = iRadius;
    int iRelativeY = 0;

    int iCheck = 1 - iRadius;

    while( iRelativeX >= iRelativeY )
    {
        SetPixelOctant( center, iRelativeX, iRelativeY );

        iRelativeY += m_iPixelSize;

        if( iCheck < 0 )
        {
            iCheck += 2 * iRelativeY + 3;
        }
        else
        {
            iCheck += 2 * ( iRelativeY - iRelativeX ) + 1;

            iRelativeX -= m_iPixelSize;
        }
    }

    SetPixelOctant( center, iRelativeX, iRelativeY );
}