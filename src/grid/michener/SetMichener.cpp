#include "Grid.h"

void Grid::SetMichener( MousePair coords ) {
    int iDeltaX = coords.begin.x - coords.end.x;
    int iDeltaY = coords.begin.y - coords.end.y;

    float fRadius = sqrt( pow( iDeltaX, 2 ) + pow( iDeltaY, 2 ) );

    int iRadius = (int)fRadius;

    SetCircle( coords.begin, iRadius );
}

void Grid::SetCircle( MouseClick center, int iRadius ) {
    int iRelativeX = iRadius;
    int iRelativeY = 0;

    int iCheck = 1 - iRadius;

    while( iRelativeX >= iRelativeY ) {
        SetPixelOctant( center, iRelativeX, iRelativeY );

        iRelativeY += m_iPixelSize;

        if( iCheck < 0 ) {
            iCheck += 2 * iRelativeY + 3;
        }
        else {
            iCheck += 2 * ( iRelativeY - iRelativeX ) + 1;

            iRelativeX -= m_iPixelSize;
        }
    }

    SetPixelOctant( center, iRelativeX, iRelativeY );
}

void Grid::SetPixelOctant( MouseClick center, int x, int y ) {
    int iSquareCenterPosX = ( center.x - m_GridPos.x ) / m_iPixelSize;
    int iSquareCenterPosY = ( center.y - m_GridPos.y ) / m_iPixelSize;

    int iSquarePosX = ( x + center.x - m_GridPos.x ) / m_iPixelSize;
    int iSquarePosY = ( y + center.y - m_GridPos.y ) / m_iPixelSize;
    
    iSquarePosX -= iSquareCenterPosX;
    iSquarePosY -= iSquareCenterPosY;

    SetPixelByIndex( iSquarePosX + iSquareCenterPosX, iSquarePosY + iSquareCenterPosY );
    SetPixelByIndex( iSquarePosY + iSquareCenterPosX, iSquarePosX + iSquareCenterPosY );
    SetPixelByIndex( -iSquarePosY + iSquareCenterPosX, iSquarePosX + iSquareCenterPosY );
    SetPixelByIndex( -iSquarePosX + iSquareCenterPosX, iSquarePosY + iSquareCenterPosY );
    SetPixelByIndex( -iSquarePosX + iSquareCenterPosX, -iSquarePosY + iSquareCenterPosY );
    SetPixelByIndex( -iSquarePosY + iSquareCenterPosX, -iSquarePosX + iSquareCenterPosY );
    SetPixelByIndex( iSquarePosY + iSquareCenterPosX, -iSquarePosX + iSquareCenterPosY );
    SetPixelByIndex( iSquarePosX + iSquareCenterPosX, -iSquarePosY + iSquareCenterPosY );
}