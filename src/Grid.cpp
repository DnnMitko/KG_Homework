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

    m_uiPixelSize = pConstants->first_child().child( "GridScale" ).child( "Initial" ).text().as_int();

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
    int x1, y1, x2, y2;
    int iRun;
    
    x1 = m_pvMouseClicks->back().begin.x;
    y1 = m_pvMouseClicks->back().begin.y;
    x2 = m_pvMouseClicks->back().end.x;
    y2 = m_pvMouseClicks->back().end.y;

    iRun = x2 - x1;

    if( iRun == 0 )
    {
        SetVertical( x1, y1, y2 );
    }
    else
    {
        SetSlope( x1, y1, x2, y2 );
    }
}

void Grid::Recalculate()
{
    vector<MousePair>::iterator it;
    
    int x1, y1, x2, y2;
    int iRun;
    
    for( it = m_pvMouseClicks->begin(); it != m_pvMouseClicks->end(); it++ )
    {
        x1 = it->begin.x;
        y1 = it->begin.y;
        x2 = it->end.x;
        y2 = it->end.y;

        x1 = m_pvMouseClicks->back().begin.x;
        y1 = m_pvMouseClicks->back().begin.y;
        x2 = m_pvMouseClicks->back().end.x;
        y2 = m_pvMouseClicks->back().end.y;

        iRun = x2 - x1;

        if( iRun == 0 )
        {
            SetVertical( x1, y1, y2 );
        }
        else
        {
            SetSlope( x1, y1, x2, y2 );
        }
    }
}

void Grid::PutPixel( int iX, int iY )
{
    int iSquarePosX = ( iX - m_GridPos.x ) / m_uiPixelSize;
    int iSquarePosY = ( iY - m_GridPos.y ) / m_uiPixelSize;

    m_ppbPixelStatus[iSquarePosX][iSquarePosY] = true;
}

void Grid::SetVertical( int x, int y1, int y2 )
{
    int iCol = ( x - m_GridPos.x ) / m_uiPixelSize;

    int iRowStart, iRowEnd;

    if( y1 < y2 )
    {
        iRowStart = ( y1 - m_GridPos.y ) / m_uiPixelSize;
        iRowEnd = ( y2 - m_GridPos.y ) / m_uiPixelSize;
    }
    else
    {
        iRowStart = ( y2 - m_GridPos.y ) / m_uiPixelSize;
        iRowEnd = ( y1 - m_GridPos.y ) / m_uiPixelSize;
    }

    for( int iRow = iRowStart; iRow <= iRowEnd; iRow++ )
    {
        m_ppbPixelStatus[iCol][iRow] = true;
    }
}

void Grid::SetSlope( int x1, int y1, int x2, int y2 )
{
    int iRise = y2 - y1;
    int iRun = x2 - x1;

    float fSlope = iRise / (float)iRun;

    if( fSlope <= 1 && fSlope >= -1 )
    {
        SetSlopeNormal( x1, y1, x2, y2, fSlope );
    }
    else
    {
        SetSlopeInverse( x1, y1, x2, y2 );
    }
}

void Grid::SetSlopeNormal( int x1, int y1, int x2, int y2, float fSlope )
{
    int iDirection = ( fSlope >= 0 ) ? 1 : -1;

    float fDelta = fabsf( fSlope );

    float fOffset = 0;

    float fThreshold = ( y1 - m_GridPos.y ) % m_uiPixelSize;
    if( fSlope > 0 )
    {
        fThreshold = m_uiPixelSize - fThreshold;
    }
    
    int iY = y1;
    for( int iX = x1; iX <= x2; iX += m_uiPixelSize )
    {
        PutPixel( iX, iY );

        fOffset += fDelta * m_uiPixelSize;
        if( fOffset > fThreshold )
        {
            iY += iDirection * m_uiPixelSize;
            fThreshold += m_uiPixelSize;
        }
    }
}

void Grid::SetSlopeInverse( int x1, int y1, int x2, int y2 )
{
    int iRise = y2 - y1;
    int iRun = x2 - x1;

    float fSlope = iRun / (float)iRise;

    int iDirection = ( fSlope >= 0 ) ? 1 : -1;

    float fDelta = fabsf( fSlope );

    float fOffset = 0;

    float fThreshold = ( x1 - m_GridPos.x ) % m_uiPixelSize;
    if( fSlope > 0 )
    {
        fThreshold = m_uiPixelSize - fThreshold;
    }
    
    int iX;
    if( y1 < y2 )
    {
        iX = x1;
    }
    else
    {
        iX = x2;
        int iTemp = y1;
        y1 = y2;
        y2 = iTemp;
    }

    for( int iY = y1; iY <= y2; iY += m_uiPixelSize )
    {
        PutPixel( iX, iY );
        
        fOffset += fDelta * m_uiPixelSize;
        if( fOffset >= fThreshold )
        {
            iX += iDirection * m_uiPixelSize;
            fThreshold += m_uiPixelSize;
        }
    }
}