#include "Grid.h"

void Grid::DrawExpansion() {
    vector<SpreadMap>::iterator it;

    for( it = m_pvSpreadMaps->begin(); it != m_pvSpreadMaps->end(); it++ ) {
        if( (*it).isFinished == false ) {
            Expand( (*it) );
        }
    }
}

void Grid::Expand( SpreadMap& spread ) {
    static int iPeriod = 10;

    while( spread.isFinished == false ) {

        if( iPeriod == 10 ) {
            iPeriod = 0;
            ProcessPoint( spread );
        }
        else {
            iPeriod++;
        }

        DrawPixelStatus();
        SDL_RenderPresent( m_Renderer );
    }

    iPeriod = 10;
}

// void Grid::Expand( SpreadMap& spread ) {
//     static int iPeriod = 10;

//     while( spread.isFinished == false ) {
//         ProcessPoint( spread );

//         if( iPeriod == 10 ) {
//             iPeriod = 0;
//             DrawPixelStatus();
//             SDL_RenderPresent( m_Renderer );
//         }
//         else {
//             iPeriod++;
//         }
//     }

//     iPeriod = 10;
// }

void Grid::ProcessPoint( SpreadMap& spread ) {
    if( spread.points.empty() ) {
        spread.isFinished = true;
        return;
    }

    int x = spread.points.top().x;
    int y = spread.points.top().y;
    spread.points.pop();

    if( GetPixelStatus( x, y ) != '1' && GetPixelStatus( x, y ) != '2' && GetPixelStatus( x, y ) != ' ' ) {
        int xLeft = x;
        int xRight = x;

        while( GetPixelStatus( xLeft - m_iPixelSize, y ) != '1'
            && GetPixelStatus( xLeft - m_iPixelSize, y ) != ' ' ) {
                xLeft -= m_iPixelSize;
            }

        while( GetPixelStatus( xRight + m_iPixelSize, y ) != '1'
            && GetPixelStatus( xRight + m_iPixelSize, y ) != ' ' ) {
                xRight += m_iPixelSize;
            }
        DrawRow( xLeft, xRight, y );

        bool bOldBPoint = true;
        for( int i = xLeft; i <= xRight; i++ ) {
            if( GetPixelStatus( i, y + m_iPixelSize ) == '1'
                || GetPixelStatus( i, y + m_iPixelSize ) == ' ' ) {
                bOldBPoint = true;
            }
            else {
                if( bOldBPoint ) {
                    bOldBPoint = false;
                    if( GetPixelStatus( i, y + m_iPixelSize ) != '2' ) {
                        MouseClick temp;
                        temp.x = x;
                        temp.y = y + m_iPixelSize;
                        spread.points.push( temp );
                    }
                }
            }
        }

        bOldBPoint = true;
        for( int i = xLeft; i <= xRight; i++ ) {
            if( GetPixelStatus( i, y - m_iPixelSize ) == '1'
                || GetPixelStatus( i, y - m_iPixelSize ) == ' ' ) {
                    bOldBPoint = true;
            }
            else {
                if( bOldBPoint ) {
                    bOldBPoint = false;
                    if( GetPixelStatus( i, y - m_iPixelSize ) != '2' ) {
                        MouseClick temp;
                        temp.x = x;
                        temp.y = y - m_iPixelSize;
                        spread.points.push( temp );
                    }
                }
            }
        }
    }
}

// void Grid::ProcessPoint( SpreadMap& spread ) {
//     if( spread.points.empty() ) {
//         spread.isFinished = true;
//         return;
//     }

//     int x = spread.points.top().x;
//     int y = spread.points.top().y;
//     spread.points.pop();

//     if( GetPixelStatus( x, y ) != '1' && GetPixelStatus( x, y ) != '2' && GetPixelStatus( x, y ) != ' ' ) {
//         SetPixel( x, y, '2' );

//         MouseClick temp;

//         temp.x = x - m_iPixelSize;
//         temp.y = y;
//         spread.points.push( temp );

//         temp.x = x + m_iPixelSize;
//         temp.y = y;
//         spread.points.push( temp );

//         temp.x = x;
//         temp.y = y - m_iPixelSize;
//         spread.points.push( temp );

//         temp.x = x;
//         temp.y = y + m_iPixelSize;
//         spread.points.push( temp );
//     }
// }

void Grid::DrawRow( int xLeft, int xRight, int y ) {
    for( int i = xLeft; i <= xRight; i++ ) {
        SetPixel( i, y, '2' );
    }
}