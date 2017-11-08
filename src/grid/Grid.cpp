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

    m_bUseBresenham = false;

    m_ppbPixelStatus = NULL;
    m_uiPixelCountWidth = 0;;
    m_uiPixelCountHeight = 0;

    m_pvMousePairs = NULL;
}

Grid::~Grid()
{
    for( unsigned int i = 0; i < m_uiPixelCountWidth; i++ )
    {
        delete[] m_ppbPixelStatus[i];
    }
    delete[] m_ppbPixelStatus;

    delete m_pvMousePairs;

    m_ppbPixelStatus = NULL;
    m_pvMousePairs = NULL;
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

    m_bUseBresenham = false;

    int iSmallest = m_xmlConstants->first_child().child( "GridScale" ).child( "VerySmall" ).text().as_int();
    m_uiPixelCountWidth = m_GridPos.w / iSmallest;
    m_uiPixelCountHeight = m_GridPos.h / iSmallest;

    m_ppbPixelStatus = new bool*[m_uiPixelCountWidth];
    for( unsigned int i = 0; i < m_uiPixelCountWidth; i++ )
    {
        m_ppbPixelStatus[i] = new bool[m_uiPixelCountHeight];
    }
    ClearStatus();

    m_pvMousePairs = new vector<MousePair>;
}

void Grid::Draw()
{
    if( !m_bHasChanged )
    {
        return;
    }

    DrawGrid();
    DrawPixelStatus();
    DrawLines( m_bUseBresenham );

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
            AddClick( click );
        }
    }
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

void Grid::ToggleDrawBresenham()
{
    m_bUseBresenham = !m_bUseBresenham;
    
    m_bHasChanged = true;
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

void Grid::DrawLines( bool bUseBresenham )
{
    vector<MousePair>::iterator it;
    
    int x1, y1, x2, y2;

    SDL_SetRenderDrawColor( m_Renderer, 0x00, 0x00, 0x00, 0xFF );
    
    for( it = m_pvMousePairs->begin(); it != m_pvMousePairs->end(); it++ )
    {
        if( (*it).end.x == -1 )
        {
            break;
        }
        else if( bUseBresenham )
        {
            DrawBresenham( *it );
        }
        else
        {
            x1 = it->begin.x;
            y1 = it->begin.y;
            x2 = it->end.x;
            y2 = it->end.y;

            SDL_RenderDrawLine( m_Renderer, x1, y1, x2, y2 );
        }
    }
}

void Grid::ClearStatus()
{
    for( unsigned int col = 0; col < m_uiPixelCountWidth; col++ )
    {
        for( unsigned int row = 0; row < m_uiPixelCountHeight; row++ )
        {
            m_ppbPixelStatus[col][row] = false;
        }
    }
}

bool Grid::IsInGrid( MouseClick click )
{
    if( click.x > m_GridPos.x && click.x < ( m_GridPos.x + m_GridPos.w ) )
    {
        if( click.y > m_GridPos.y && click.y < ( m_GridPos.y + m_GridPos.h ) )
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
            Calculate();
        }
        
        m_bHasChanged = true;
    }
}

void Grid::Calculate()
{
    CalcBresenham( m_pvMousePairs->back() );
}

void Grid::Recalculate()
{
    vector<MousePair>::iterator it;
    
    for( it = m_pvMousePairs->begin(); it != m_pvMousePairs->end(); it++ )
    {
        if( (*it).end.x != -1 )
        {
            CalcBresenham( *it );
        }
    }
}

void Grid::SetPixel( int x, int y )
{
    int iSquarePosX = ( x - m_GridPos.x ) / m_iPixelSize;
    int iSquarePosY = ( y - m_GridPos.y ) / m_iPixelSize;

    m_ppbPixelStatus[iSquarePosX][iSquarePosY] = true;
}

void Grid::DrawPixel( int x, int y )
{
    SDL_RenderDrawPoint( m_Renderer, x, y );
}