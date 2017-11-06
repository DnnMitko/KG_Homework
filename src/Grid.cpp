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

bool Grid::Init( pugi::xml_document* pConstants, SDL_Renderer* pRenderer )
{
    m_Renderer = pRenderer;

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

    DrawGrid();
    DrawPixelStatus();
    DrawLines();
}

void Grid::EventHandler( SDL_Event& e )
{
    //TODO
}

void Grid::DrawGrid()
{
    SDL_SetRenderDrawColor( m_Renderer, 0, 0, 0, 255 );
    SDL_RenderClear( m_Renderer );

    SDL_SetRenderDrawColor( m_Renderer, 255, 255, 255, 255 );
    SDL_RenderFillRect( m_Renderer, &m_GridPos );
    
    if( m_uiPixelSize != 1 )
    {
        SDL_SetRenderDrawColor( m_Renderer, 0, 0, 0, 255 );

        SDL_Rect temp;
        temp.w = m_uiPixelSize;
        temp.h = m_uiPixelSize;

        for( unsigned int uiX = m_GridPos.x; uiX < m_GridPos.x + m_GridPos.w; uiX += m_uiPixelSize )
        {
            for( unsigned int uiY = m_GridPos.y; uiY < m_GridPos.y + m_GridPos.h; uiY += m_uiPixelSize )
            {
                temp.x = uiX;
                temp.y = uiY;
                SDL_RenderDrawRect( m_Renderer, &temp );
            }
        }
    }
}

void Grid::DrawPixelStatus()
{
    if( m_uiPixelSize != 1 )
    {
        SDL_SetRenderDrawColor( m_Renderer, 160, 160, 160, 255 );

        SDL_Rect temp;
        temp.w = m_uiPixelSize - 2;
        temp.h = m_uiPixelSize - 2;

        for( unsigned int uiX = m_GridPos.x; uiX < m_GridPos.x + m_GridPos.w; uiX += m_uiPixelSize )
        {
            for( unsigned int uiY = m_GridPos.y; uiY < m_GridPos.y + m_GridPos.h; uiY += m_uiPixelSize )
            {
                unsigned int uiSquarePosX = ( uiX - m_GridPos.x ) / m_uiPixelSize;
                unsigned int uiSquarePosY = ( uiY - m_GridPos.y ) / m_uiPixelSize;

                if( m_ppbPixelStatus[uiSquarePosX][uiSquarePosY] )
                {
                    temp.x = uiX + 1;
                    temp.y = uiY + 1;
                    SDL_RenderFillRect( m_Renderer, &temp );
                }
            }
        }
    }
}

void Grid::DrawLines()
{
    //TODO
}

void Grid::ClearStatus()
{
    for( unsigned int col = 0; col < m_uiPixelCountWidth; col++ )
    {
        for( unsigned int row = 0; row < m_uiPixelCountHeight; row++ )
        {
            if(col == 1)
            {
                m_ppbPixelStatus[col][row] = true;
                continue;
            }
            m_ppbPixelStatus[col][row] = false;
        }
    }
}