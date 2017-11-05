#include "Grid.h"

Grid::Grid()
{
    m_Renderer = NULL;
    
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

    pugi::xml_node xGridPos = pConstants->first_child().child( "GridPos" );

    m_GridPos.x = xGridPos.child( "x" ).text().as_int();
    m_GridPos.y = xGridPos.child( "y" ).text().as_int();
    m_GridPos.w = xGridPos.child( "w" ).text().as_int();
    m_GridPos.h = xGridPos.child( "h" ).text().as_int();

    m_uiPixelSize = 1;

    m_ppbPixelStatus = NULL;
    m_uiPixelCountWidth = 0;;
    m_uiPixelCountHeight = 0;

    m_pvMouseClicks = new vector<MousePair>;
}