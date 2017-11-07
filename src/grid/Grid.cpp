#include "Grid.h"

Grid::Grid()
{
    m_Renderer = NULL;

    m_eCurState = NumStates;

    m_bHasChanged = false;
    
    m_GridPos.x = 0;
    m_GridPos.y = 0;
    m_GridPos.w = 0;
    m_GridPos.h = 0;

    m_uiPixelSize = 0;

    m_ppbPixelStatus = NULL;
    m_uiPixelCountWidth = 0;;
    m_uiPixelCountHeight = 0;

    m_pvMouseClicks = NULL;
}

Grid::~Grid()
{
    for( unsigned int i = 0; i < m_uiPixelCountWidth; i++ )
    {
        delete[] m_ppbPixelStatus[i];
    }
    delete[] m_ppbPixelStatus;

    delete m_pvMouseClicks;

    m_ppbPixelStatus = NULL;
    m_pvMouseClicks = NULL;
}

void Grid::Init( pugi::xml_document* pConstants, SDL_Renderer* pNewRenderer )
{
    m_Renderer = pNewRenderer;

    m_eCurState = Bresenham;

    m_bHasChanged = true;

    pugi::xml_node xGridPos = pConstants->first_child().child( "GridPos" );

    m_GridPos.x = xGridPos.child( "x" ).text().as_int();
    m_GridPos.y = xGridPos.child( "y" ).text().as_int();
    m_GridPos.w = xGridPos.child( "w" ).text().as_int();
    m_GridPos.h = xGridPos.child( "h" ).text().as_int();

    m_uiPixelSize = pConstants->first_child().child( "GridScale" ).child( "Initial" ).text().as_uint();

    int iSmallest = pConstants->first_child().child( "GridScale" ).child( "VerySmall" ).text().as_int();
    m_uiPixelCountWidth = m_GridPos.w / iSmallest;
    m_uiPixelCountHeight = m_GridPos.h / iSmallest;

    m_ppbPixelStatus = new bool*[m_uiPixelCountWidth];
    for( unsigned int i = 0; i < m_uiPixelCountWidth; i++ )
    {
        m_ppbPixelStatus[i] = new bool[m_uiPixelCountHeight];
    }
    ClearStatus();

    m_pvMouseClicks = new vector<MousePair>;
}

void Grid::Draw()
{
    if( !m_bHasChanged )
    {
        return;
    }

    if( !m_pvMouseClicks->empty() && m_uiPixelSize != 1 )
    {
        Calculate();
    }

    DrawGrid();
    DrawPixelStatus();
    DrawLines();

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

void Grid::DrawGrid()
{
    SDL_SetRenderDrawColor( m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderFillRect( m_Renderer, &m_GridPos );
    
    if( m_uiPixelSize != 1 )
    {
        SDL_SetRenderDrawColor( m_Renderer, 0x00, 0x00, 0x00, 0xFF );

        SDL_Rect temp;
        temp.w = m_uiPixelSize;
        temp.h = m_uiPixelSize;

        for( int iX = m_GridPos.x; iX < m_GridPos.x + m_GridPos.w; iX += m_uiPixelSize )
        {
            for( int iY = m_GridPos.y; iY < m_GridPos.y + m_GridPos.h; iY += m_uiPixelSize )
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
    if( m_uiPixelSize != 1 )
    {
        SDL_SetRenderDrawColor( m_Renderer, 0xA0, 0xA0, 0xA0, 0xFF );

        SDL_Rect temp;
        temp.w = m_uiPixelSize - 2;
        temp.h = m_uiPixelSize - 2;

        for( int iX = m_GridPos.x; iX < m_GridPos.x + m_GridPos.w; iX += m_uiPixelSize )
        {
            for( int iY = m_GridPos.y; iY < m_GridPos.y + m_GridPos.h; iY += m_uiPixelSize )
            {
                int iSquarePosX = ( iX - m_GridPos.x ) / m_uiPixelSize;
                int iSquarePosY = ( iY - m_GridPos.y ) / m_uiPixelSize;

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

void Grid::DrawLines()
{
    vector<MousePair>::iterator it;
    
    int x1, y1, x2, y2;

    SDL_SetRenderDrawColor( m_Renderer, 0x00, 0x00, 0x00, 0xFF );
    
    for( it = m_pvMouseClicks->begin(); it != m_pvMouseClicks->end(); it++ )
    {
        x1 = it->begin.x;
        y1 = it->begin.y;
        x2 = it->end.x;
        y2 = it->end.y;

        SDL_RenderDrawLine( m_Renderer, x1, y1, x2, y2 );
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
    if( m_pvMouseClicks->empty()
        || m_pvMouseClicks->back().end.x != -1 )
    {
        MousePair mpTemp;
        mpTemp.begin = click;
        mpTemp.end.x = -1;
        mpTemp.end.y = -1;
        m_pvMouseClicks->push_back( mpTemp );
    }
    else
    {
        m_bHasChanged = true;

        if( m_pvMouseClicks->back().begin.x < click.x )
        {
            m_pvMouseClicks->back().end = click;
        }
        else
        {
            m_pvMouseClicks->back().end = m_pvMouseClicks->back().begin;
            m_pvMouseClicks->back().begin = click;
        }
    }
}

void Grid::Calculate()
{
    CalcBresenham( m_pvMouseClicks->back() );
}

void Grid::Recalculate()
{
    vector<MousePair>::iterator it;
    
    for( it = m_pvMouseClicks->begin(); it != m_pvMouseClicks->end(); it++ )
    {
        CalcBresenham( *it );
    }
}

void Grid::PutPixel( int iX, int iY )
{
    int iSquarePosX = ( iX - m_GridPos.x ) / m_uiPixelSize;
    int iSquarePosY = ( iY - m_GridPos.y ) / m_uiPixelSize;

    m_ppbPixelStatus[iSquarePosX][iSquarePosY] = true;
}