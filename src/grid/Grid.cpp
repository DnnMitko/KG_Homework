#include "Grid.h"

Grid::Grid() {
    m_Renderer = NULL;

    m_xmlConstants = NULL;

    m_eCurState = NumStates;

    m_bHasChanged = false;

    m_GridPos.x = -1;
    m_GridPos.y = -1;
    m_GridPos.w = -1;
    m_GridPos.h = -1;

    m_iPixelSize = 0;

    m_bUseNormalBresenham = true;
    m_bReadyToDrawSpline = false;

    m_ppbPixelStatus = NULL;
    m_iPixelCountWidth = 0;
    m_iPixelCountHeight = 0;

    m_pvMousePairs = NULL;
    m_pvClippedLines = NULL;
    m_pvSpreadMaps = NULL;
    m_pvMouseClicks = NULL;
}

Grid::~Grid() {
    for( int i = 0; i < m_iPixelCountWidth; i++ ) {
        delete[] m_ppbPixelStatus[i];
    }
    delete[] m_ppbPixelStatus;

    delete m_pvMousePairs;
    delete m_pvClippedLines;
    delete m_pvSpreadMaps;
    delete m_pvMouseClicks;

    m_ppbPixelStatus = NULL;
    m_pvMousePairs = NULL;
    m_pvClippedLines = NULL;
    m_pvSpreadMaps = NULL;
    m_pvMouseClicks = NULL;
}

void Grid::Init( pugi::xml_document* pConstants, SDL_Renderer* pNewRenderer ) {
    m_Renderer = pNewRenderer;

    m_xmlConstants = pConstants;

    m_eCurState = Bresenham;

    m_bHasChanged = true;

    pugi::xml_node xGridPos = m_xmlConstants->first_child().child( "GridPos" );

    m_GridPos.x = xGridPos.child( "x" ).text().as_int();
    m_GridPos.y = xGridPos.child( "y" ).text().as_int();
    m_GridPos.w = xGridPos.child( "w" ).text().as_int();
    m_GridPos.h = xGridPos.child( "h" ).text().as_int();

    m_iPixelSize = m_xmlConstants->first_child().child( "GridScale" ).child( "Initial" ).text().as_int();

    m_bUseNormalBresenham = true;
    m_bReadyToDrawSpline = false;

    int iSmallest = m_xmlConstants->first_child().child( "GridScale" ).child( "VerySmall" ).text().as_int();
    m_iPixelCountWidth = m_GridPos.w / iSmallest;
    m_iPixelCountHeight = m_GridPos.h / iSmallest;

    m_ppbPixelStatus = new char*[m_iPixelCountWidth];
    for( int i = 0; i < m_iPixelCountWidth; i++ ) {
        m_ppbPixelStatus[i] = new char[m_iPixelCountHeight];
    }
    ClearStatus();

    m_pvMousePairs = new vector<MousePair>;
    m_pvClippedLines = new vector<MousePair>;
    m_pvSpreadMaps = new vector<SpreadMap>;
    m_pvMouseClicks = new vector<MouseClick>;
}

void Grid::Draw() {
    if( !m_bHasChanged ) {
        return;
    }

    if( m_eCurState != Spline && m_eCurState != LiangBarsky ) {
        DrawGrid();
    }
    DrawPixelStatus();
    DrawSim( m_bUseNormalBresenham );
    if( m_eCurState == BoundryFill ) {
        DrawExpansion();
    }
    if( m_eCurState == Spline && m_bReadyToDrawSpline ) {
        DrawSpline();
    }

    m_bHasChanged = false;
}

void Grid::EventHandler( SDL_Event& e ) {
    if( e.type == SDL_MOUSEBUTTONDOWN ) {
        MouseClick click;
        SDL_GetMouseState( &( click.x ), &( click.y ) );

        if( IsInGrid( click ) ) {
            if( m_eCurState != BoundryFill && m_eCurState != Spline ) {
                AddClick( click );
            }
            else if( m_eCurState == BoundryFill ) {
                stack<MouseClick>* newStack = new stack<MouseClick>;
                newStack->push( click );

                SpreadMap newMap;
                newMap.points = *newStack;
                newMap.isFinished = false;

                m_pvSpreadMaps->push_back( newMap );

                m_bHasChanged = true;
            }
            else if( m_eCurState == Spline ) {
                static int iCount = 0;

                m_pvMouseClicks->push_back( click );

                m_bHasChanged = true;

                DrawLargeDot( click.x, click.y );

                iCount++;
                if( iCount == 5 ) {
                    iCount = 0;
                    m_bReadyToDrawSpline = true;
                }
            }
        }
    }
}

void Grid::SetState( State newState ) {
    m_eCurState = newState;

    ClearGrid();
}

void Grid::SetGridScale( std::string sNewScale ) {
    m_iPixelSize = m_xmlConstants->first_child().child( "GridScale" ).child( sNewScale.c_str() ).text().as_int();
    ClearStatus();
    if( sNewScale != "Initial" ) {
        Recalculate();
    }

    m_bHasChanged = true;
}

void Grid::ClearGrid() {
    ClearStatus();

    m_pvMousePairs->clear();
    m_pvClippedLines->clear();
    m_pvSpreadMaps->clear();
    m_pvMouseClicks->clear();

    m_bHasChanged = true;

    if( m_eCurState == BoundryFill ) {
        m_eCurState = Michener;

        MouseClick click;

        click.x = 150;
        click.y = 65;
        AddClick( click );
        click.x = 600;
        click.y = 300;
        AddClick( click );

        click.x = 1000;
        click.y = 65;
        AddClick( click );
        click.x = 500;
        click.y = 300;
        AddClick( click );

        click.x = 700;
        click.y = 500;
        AddClick( click );
        click.x = 700;
        click.y = 100;
        AddClick( click );

        m_eCurState = BoundryFill;
    }
    else if( m_eCurState == Spline ) {
        DrawGrid();
    }
    else if( m_eCurState == LiangBarsky ) {
        DrawGrid();

        SDL_Rect rect;
        rect.x = 420;
        rect.y = 220;
        rect.w = 500;
        rect.h = 340;

        SDL_SetRenderDrawColor( m_Renderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderDrawRect( m_Renderer, &rect );

        m_bHasChanged = true;
    }
}

bool Grid::ToggleDrawBresenham() {
    m_bUseNormalBresenham = !m_bUseNormalBresenham;

    m_bHasChanged = true;
    
    if( m_iPixelSize != 1 ) {
        ClearStatus();
        Recalculate();
    }

    return m_bUseNormalBresenham;
}

void Grid::DrawGrid() {
    SDL_SetRenderDrawColor( m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderFillRect( m_Renderer, &m_GridPos );

    if( m_iPixelSize != 1 ) {
        SDL_SetRenderDrawColor( m_Renderer, 0x00, 0x00, 0x00, 0xFF );

        SDL_Rect temp;
        temp.w = m_iPixelSize;
        temp.h = m_iPixelSize;

        for( int iX = m_GridPos.x; iX < m_GridPos.x + m_GridPos.w; iX += m_iPixelSize ) {
            for( int iY = m_GridPos.y; iY < m_GridPos.y + m_GridPos.h; iY += m_iPixelSize ) {
                temp.x = iX;
                temp.y = iY;
                SDL_RenderDrawRect( m_Renderer, &temp );
            }
        }
    }
}

void Grid::DrawPixelStatus() {
    if( m_iPixelSize != 1 ) {
        SDL_Rect temp;
        temp.w = m_iPixelSize - 2;
        temp.h = m_iPixelSize - 2;

        for( int iX = m_GridPos.x; iX < m_GridPos.x + m_GridPos.w; iX += m_iPixelSize ) {
            for( int iY = m_GridPos.y; iY < m_GridPos.y + m_GridPos.h; iY += m_iPixelSize ) {
                int iSquarePosX = ( iX - m_GridPos.x ) / m_iPixelSize;
                int iSquarePosY = ( iY - m_GridPos.y ) / m_iPixelSize;

                if( m_ppbPixelStatus[iSquarePosX][iSquarePosY] == '1' ) {
                    SDL_SetRenderDrawColor( m_Renderer, 0xA0, 0xA0, 0xA0, 0xFF );
                    temp.x = iX + 1;
                    temp.y = iY + 1;
                    SDL_RenderFillRect( m_Renderer, &temp );
                }
                else if( m_ppbPixelStatus[iSquarePosX][iSquarePosY] == '2' ) {
                    SDL_SetRenderDrawColor( m_Renderer, 0xFF, 0x00, 0x00, 0xFF );
                    temp.x = iX + 1;
                    temp.y = iY + 1;
                    SDL_RenderFillRect( m_Renderer, &temp );
                }
            }
        }
    }
}

void Grid::DrawSim( bool bUseNormalBresenham ) {
    vector<MousePair>::iterator it;
    vector<MousePair>::iterator it2;

    SDL_SetRenderDrawColor( m_Renderer, 0x00, 0x00, 0x00, 0xFF );

    for( it = m_pvMousePairs->begin(), it2 = m_pvClippedLines->begin(); it != m_pvMousePairs->end(); it++, it2++ ) {
        if( (*it).end.x == -1 ) {
            break;
        }
        else {
            switch( m_eCurState ) {
                case Bresenham:
                    if( bUseNormalBresenham ) {
                        DrawBresenham( *it );
                    }
                    else {
                        SplitLineDraw( *it );
                    }
                    break;
                case Michener:
                    DrawMichener( *it );
                    break;
                case BoundryFill:
                    break;
                case LiangBarsky:
                    DrawBresenham( *it );

                    if( it2->begin.x != -1 ) {
                        SDL_RenderPresent( m_Renderer );

                        if( std::next( it2 ) == m_pvClippedLines->end() ) {
                            SDL_Delay( 1000 );
                        }

                        SDL_SetRenderDrawColor( m_Renderer, 0xFF, 0x00, 0x00, 0xFF );
                        DrawBresenham( *it2 );

                        SDL_SetRenderDrawColor( m_Renderer, 0x00, 0x00, 0x00, 0xFF );
                    }

                    break;
                default:
                    printf( "Error in recognizing state. Won't draw simulation figure.\n" );
            }
        }
    }
}

void Grid::ClearStatus() {
    for( int col = 0; col < m_iPixelCountWidth; col++ ) {
        for( int row = 0; row < m_iPixelCountHeight; row++ ) {
            m_ppbPixelStatus[col][row] = '0';
        }
    }
}

bool Grid::IsInGrid( MouseClick click ) {
    if( click.x >= m_GridPos.x && click.x <= ( m_GridPos.x + m_GridPos.w ) ) {
        if( click.y >= m_GridPos.y && click.y <= ( m_GridPos.y + m_GridPos.h ) ) {
            return true;
        }
    }

    return false;
}

void Grid::AddClick( MouseClick click ) {
    if( m_pvMousePairs->empty()
        || m_pvMousePairs->back().end.x != -1 ) {
            MousePair mpTemp;
            mpTemp.begin = click;
            mpTemp.end.x = -1;
            mpTemp.end.y = -1;
            m_pvMousePairs->push_back( mpTemp );
    }
    else {
        m_pvMousePairs->back().end = click;

        if( m_iPixelSize != 1 ) {
            Calculate( m_pvMousePairs->back() );
        }

        if( m_eCurState == LiangBarsky ) {
            DrawClipping();
        }

        m_bHasChanged = true;
    }
}

void Grid::Calculate( MousePair coords ) {
    switch( m_eCurState ) {
        case Bresenham:
            if( m_bUseNormalBresenham ) {
                SetBresenham( coords );
            }
            else {
                SplitLineSet( coords );
            }
            break;
        case Michener:
            SetMichener( coords );
            break;
        case BoundryFill:
            break;
        default:
            printf( "Error in recognizing state. Won't calculate grid highlight.\n" );
    }
}

void Grid::Recalculate() {
    vector<MousePair>::iterator it;

    for( it = m_pvMousePairs->begin(); it != m_pvMousePairs->end(); it++ ) {
        if( (*it).end.x != -1 ) {
            Calculate( *it );
        }
    }
}

void Grid::DrawPixel( int x, int y ) {
    MouseClick temp;
    temp.x = x;
    temp.y = y;

    if( IsInGrid( temp ) ) {
        SDL_RenderDrawPoint( m_Renderer, x, y );
    }
}

void Grid::SetPixel( int x, int y, char val ) {
    MouseClick temp;
    temp.x = x;
    temp.y = y;

    if( IsInGrid( temp ) ) {
        int iSquarePosX = ( x - m_GridPos.x ) / m_iPixelSize;
        int iSquarePosY = ( y - m_GridPos.y ) / m_iPixelSize;

        m_ppbPixelStatus[iSquarePosX][iSquarePosY] = val;
    }
}

void Grid::SetPixelByIndex( int x, int y ) {
    if( x >= 0 && x < m_iPixelCountWidth ) {
        if( y >= 0 && y < m_iPixelCountHeight ) {
            m_ppbPixelStatus[x][y] = '1';
        }
    }
}

char Grid::GetPixelStatus( int x, int y ) {
    MouseClick temp;
    temp.x = x;
    temp.y = y;

    if( IsInGrid( temp ) ) {
        int iSquarePosX = ( x - m_GridPos.x ) / m_iPixelSize;
        int iSquarePosY = ( y - m_GridPos.y ) / m_iPixelSize;

        return m_ppbPixelStatus[iSquarePosX][iSquarePosY];
    }

    return ' ';
}

void Grid::SortUpX( MousePair& coords ) {
    if( coords.begin.x > coords.end.x ) {
        MouseClick temp = coords.begin;
        coords.begin = coords.end;
        coords.end = temp;
    }
}

void Grid::SortUpY( MousePair& coords ) {
    if( coords.begin.y > coords.end.y ) {
        MouseClick temp = coords.begin;
        coords.begin = coords.end;
        coords.end = temp;
    }
}

void Grid::SortDownX( MousePair& coords ) {
    if( coords.begin.x < coords.end.x ) {
        MouseClick temp = coords.begin;
        coords.begin = coords.end;
        coords.end = temp;
    }
}

void Grid::SortDownY( MousePair& coords ) {
    if( coords.begin.y < coords.end.y ) {
        MouseClick temp = coords.begin;
        coords.begin = coords.end;
        coords.end = temp;
    }
}

void Grid::SplitLineDraw( MousePair coords ) {
    SortUpX( coords );
    int iMiddleX = ( ( coords.end.x - coords.begin.x ) / 2 ) + coords.begin.x;

    SortUpY( coords );
    int iMiddleY = ( ( coords.end.y - coords.begin.y ) / 2 ) + coords.begin.y;

    SortUpX( coords );
    MousePair mpFirstHalf;
    mpFirstHalf.begin.x = coords.begin.x;
    mpFirstHalf.begin.y = coords.begin.y;
    mpFirstHalf.end.x = iMiddleX;
    mpFirstHalf.end.y = iMiddleY;

    MousePair mpSecondHalf;
    mpSecondHalf.begin.x = iMiddleX;
    mpSecondHalf.begin.y = iMiddleY;
    mpSecondHalf.end.x = coords.end.x;
    mpSecondHalf.end.y = coords.end.y;

    DrawBresenham( mpFirstHalf );

    DrawRevBresenham( mpSecondHalf );
}
void Grid::SplitLineSet( MousePair coords ) {
    SortUpX( coords );
    int iMiddleX = ( ( coords.end.x - coords.begin.x ) / 2 ) + coords.begin.x;

    SortUpY( coords );
    int iMiddleY = ( ( coords.end.y - coords.begin.y ) / 2 ) + coords.begin.y;

    SortUpX( coords );
    MousePair mpFirstHalf;
    mpFirstHalf.begin.x = coords.begin.x;
    mpFirstHalf.begin.y = coords.begin.y;
    mpFirstHalf.end.x = iMiddleX;
    mpFirstHalf.end.y = iMiddleY;

    MousePair mpSecondHalf;
    mpSecondHalf.begin.x = iMiddleX;
    mpSecondHalf.begin.y = iMiddleY;
    mpSecondHalf.end.x = coords.end.x;
    mpSecondHalf.end.y = coords.end.y;

    SetBresenham( mpFirstHalf );

    SetRevBresenham( mpSecondHalf );

    SetPixel( iMiddleX, iMiddleY );
}