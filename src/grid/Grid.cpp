#include "Grid.h"

Grid::Grid()
{
    m_Renderer = NULL;

    m_xmlConstants = NULL;

    m_eCurState = NumStates;

    m_bHasChanged = false;

    m_GridPos.x = 0;
    m_GridPos.y = 0;
    m_GridPos.w = 0;
    m_GridPos.h = 0;

    m_iPixelSize = 0;

    m_bUseNormalBresenham = true;

    m_ppbPixelStatus = NULL;
    m_iPixelCountWidth = 0;
    m_iPixelCountHeight = 0;

    m_pvMousePairs = NULL;
    m_pvSpreadMaps = NULL;
}

Grid::~Grid()
{
    for( int i = 0; i < m_iPixelCountWidth; i++ )
    {
        delete[] m_ppbPixelStatus[i];
    }
    delete[] m_ppbPixelStatus;

    delete m_pvMousePairs;
    delete m_pvSpreadMaps;

    m_ppbPixelStatus = NULL;
    m_pvMousePairs = NULL;
    m_pvSpreadMaps = NULL;
}

void Grid::Init( pugi::xml_document* pConstants, SDL_Renderer* pNewRenderer )
{
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

    int iSmallest = m_xmlConstants->first_child().child( "GridScale" ).child( "VerySmall" ).text().as_int();
    m_iPixelCountWidth = m_GridPos.w / iSmallest;
    m_iPixelCountHeight = m_GridPos.h / iSmallest;

    m_ppbPixelStatus = new bool*[m_iPixelCountWidth];
    for( int i = 0; i < m_iPixelCountWidth; i++ )
    {
        m_ppbPixelStatus[i] = new bool[m_iPixelCountHeight];
    }
    ClearStatus();

    m_pvMousePairs = new vector<MousePair>;
    m_pvSpreadMaps = new vector<SpreadMap>;
}

void Grid::Draw()
{
    if( !m_bHasChanged )
    {
        return;
    }

    DrawGrid();
    DrawPixelStatus();
    DrawSim( m_bUseNormalBresenham );

    m_bHasChanged = false;
}

void Grid::EventHandler( SDL_Event& e )
{
    if( e.type == SDL_MOUSEBUTTONDOWN )
    {
        MouseClick click;
        SDL_GetMouseState( &( click.x ), &( click.y ) );

        if( IsInGrid( click ) )
        {
            if( m_eCurState != BoundryFill )
            {
                AddClick( click );
            }
            else
            {
                stack<MouseClick>* newStack = new stack<MouseClick>;
                newStack->push( click );

                SpreadMap newMap;
                newMap.points = *newStack;
                newMap.isFinished = false;

                m_pvSpreadMaps->push_back( newMap );

                m_bHasChanged = true;
            }
        }
    }
}

void Grid::SetState( State newState )
{
    m_eCurState = newState;

    ClearGrid();
}

void Grid::SetGridScale( std::string sNewScale )
{
    m_iPixelSize = m_xmlConstants->first_child().child( "GridScale" ).child( sNewScale.c_str() ).text().as_int();
    ClearStatus();
    if( sNewScale != "Initial" )
    {
        Recalculate();
    }

    m_bHasChanged = true;
}

void Grid::ClearGrid()
{
    ClearStatus();

    m_pvMousePairs->clear();
    m_pvSpreadMaps->clear();

    m_bHasChanged = true;

    if( m_eCurState == BoundryFill )
    {
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
}

bool Grid::ToggleDrawBresenham()
{
    m_bUseNormalBresenham = !m_bUseNormalBresenham;

    m_bHasChanged = true;
    
    if( m_iPixelSize != 1 )
    {
        ClearStatus();
        Recalculate();
    }

    return m_bUseNormalBresenham;
}

void Grid::DrawGrid()
{
    SDL_SetRenderDrawColor( m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderFillRect( m_Renderer, &m_GridPos );

    if( m_iPixelSize != 1 )
    {
        SDL_SetRenderDrawColor( m_Renderer, 0x00, 0x00, 0x00, 0xFF );

        SDL_Rect temp;
        temp.w = m_iPixelSize;
        temp.h = m_iPixelSize;

        for( int iX = m_GridPos.x; iX < m_GridPos.x + m_GridPos.w; iX += m_iPixelSize )
        {
            for( int iY = m_GridPos.y; iY < m_GridPos.y + m_GridPos.h; iY += m_iPixelSize )
            {
                temp.x = iX;
                temp.y = iY;
                SDL_RenderDrawRect( m_Renderer, &temp );
            }
        }
    }
}

void Grid::DrawPixelStatus()
{
    if( m_iPixelSize != 1 )
    {
        SDL_SetRenderDrawColor( m_Renderer, 0xA0, 0xA0, 0xA0, 0xFF );

        SDL_Rect temp;
        temp.w = m_iPixelSize - 2;
        temp.h = m_iPixelSize - 2;

        for( int iX = m_GridPos.x; iX < m_GridPos.x + m_GridPos.w; iX += m_iPixelSize )
        {
            for( int iY = m_GridPos.y; iY < m_GridPos.y + m_GridPos.h; iY += m_iPixelSize )
            {
                int iSquarePosX = ( iX - m_GridPos.x ) / m_iPixelSize;
                int iSquarePosY = ( iY - m_GridPos.y ) / m_iPixelSize;

                if( m_ppbPixelStatus[iSquarePosX][iSquarePosY] )
                {
                    temp.x = iX + 1;
                    temp.y = iY + 1;
                    SDL_RenderFillRect( m_Renderer, &temp );
                }
            }
        }
    }
}

void Grid::DrawSim( bool bUseNormalBresenham )
{
    vector<MousePair>::iterator it;

    SDL_SetRenderDrawColor( m_Renderer, 0x00, 0x00, 0x00, 0xFF );

    for( it = m_pvMousePairs->begin(); it != m_pvMousePairs->end(); it++ )
    {
        if( (*it).end.x == -1 )
        {
            break;
        }
        else
        {
            switch( m_eCurState )
            {
                case Bresenham:
                {
                    if( bUseNormalBresenham )
                    {
                        DrawBresenham( *it );
                    }
                    else
                    {
                        SplitLineDraw( *it );
                    }
                    break;
                }
                case Michener:
                {
                    DrawMichener( *it );
                    break;
                }
                case BoundryFill:
                {
                    break;
                }
                default:
                {
                    printf( "Error in recognizing state. Won't draw simulation figure.\n" );
                }
            }
        }
    }
}

void Grid::ClearStatus()
{
    for( int col = 0; col < m_iPixelCountWidth; col++ )
    {
        for( int row = 0; row < m_iPixelCountHeight; row++ )
        {
            m_ppbPixelStatus[col][row] = false;
        }
    }
}

bool Grid::IsInGrid( MouseClick click )
{
    if( click.x >= m_GridPos.x && click.x <= ( m_GridPos.x + m_GridPos.w ) )
    {
        if( click.y >= m_GridPos.y && click.y <= ( m_GridPos.y + m_GridPos.h ) )
        {
            return true;
        }
    }

    return false;
}

void Grid::AddClick( MouseClick click )
{
    if( m_pvMousePairs->empty()
        || m_pvMousePairs->back().end.x != -1 )
    {
        MousePair mpTemp;
        mpTemp.begin = click;
        mpTemp.end.x = -1;
        mpTemp.end.y = -1;
        m_pvMousePairs->push_back( mpTemp );
    }
    else
    {
        m_pvMousePairs->back().end = click;

        if( m_iPixelSize != 1 )
        {
            Calculate( m_pvMousePairs->back() );
        }

        m_bHasChanged = true;
    }
}

void Grid::Calculate( MousePair coords )
{
    switch( m_eCurState )
    {
        case Bresenham:
        {
            if( m_bUseNormalBresenham )
            {
                SetBresenham( coords );
            }
            else
            {
                SplitLineSet( coords );
            }
            break;
        }
        case Michener:
        {
            SetMichener( coords );
            break;
        }
        case BoundryFill:
        {
            break;
        }
        default:
        {
            printf( "Error in recognizing state. Won't calculate grid highlight.\n" );
        }
    }
}

void Grid::Recalculate()
{
    vector<MousePair>::iterator it;

    for( it = m_pvMousePairs->begin(); it != m_pvMousePairs->end(); it++ )
    {
        if( (*it).end.x != -1 )
        {
            Calculate( *it );
        }
    }
}

void Grid::DrawPixel( int x, int y )
{
    MouseClick temp;
    temp.x = x;
    temp.y = y;

    if( IsInGrid( temp ) )
    {
        SDL_RenderDrawPoint( m_Renderer, x, y );
    }
}

void Grid::SetPixel( int x, int y )
{
    MouseClick temp;
    temp.x = x;
    temp.y = y;

    if( IsInGrid( temp ) )
    {
        int iSquarePosX = ( x - m_GridPos.x ) / m_iPixelSize;
        int iSquarePosY = ( y - m_GridPos.y ) / m_iPixelSize;

        m_ppbPixelStatus[iSquarePosX][iSquarePosY] = true;
    }
}

void Grid::SetPixelByIndex( int x, int y )
{
    if( x >= 0 && x < m_iPixelCountWidth )
    {
        if( y >= 0 && y < m_iPixelCountHeight )
        {
            m_ppbPixelStatus[x][y] = true;
        }
    }
}

void Grid::SetPixelOctant( MouseClick center, int x, int y )
{
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

void Grid::DrawPixelOctant( MouseClick center, int x, int y )
{
    int x0 = center.x;
    int y0 = center.y;

    DrawPixel( x + x0, y + y0 );
    DrawPixel( y + x0, x + y0 );
    DrawPixel( -y + x0, x + y0 );
    DrawPixel( -x + x0, y + y0 );
    DrawPixel( -x + x0, -y + y0 );
    DrawPixel( -y + x0, -x + y0 );
    DrawPixel( y + x0, -x + y0 );
    DrawPixel( x + x0, -y + y0 );
}

void Grid::SortUpX( MousePair& coords )
{
    if( coords.begin.x > coords.end.x )
    {
        MouseClick temp = coords.begin;
        coords.begin = coords.end;
        coords.end = temp;
    }
}

void Grid::SortUpY( MousePair& coords )
{
    if( coords.begin.y > coords.end.y )
    {
        MouseClick temp = coords.begin;
        coords.begin = coords.end;
        coords.end = temp;
    }
}

void Grid::SortDownX( MousePair& coords )
{
    if( coords.begin.x < coords.end.x )
    {
        MouseClick temp = coords.begin;
        coords.begin = coords.end;
        coords.end = temp;
    }
}

void Grid::SortDownY( MousePair& coords )
{
    if( coords.begin.y < coords.end.y )
    {
        MouseClick temp = coords.begin;
        coords.begin = coords.end;
        coords.end = temp;
    }
}

void Grid::SplitLineDraw( MousePair coords )
{
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
void Grid::SplitLineSet( MousePair coords )
{
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