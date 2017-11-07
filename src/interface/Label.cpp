#include "Label.h"

Label::Label()
{
    m_Renderer = NULL;

    m_TextureText = NULL;

    m_TextRect.x = 0;
    m_TextRect.y = 0;
    m_TextRect.w = 0;
    m_TextRect.h = 0;

    m_bHasChanged = false;
}

Label::~Label()
{
    SDL_DestroyTexture( m_TextureText );
    
    m_TextureText = NULL;
}

void Label::Init( SDL_Renderer* pNewRenderer )
{
    m_Renderer = pNewRenderer;

    m_TextureText = NULL;

    m_TextRect.x = 0;
    m_TextRect.y = 0;
    m_TextRect.w = 0;
    m_TextRect.h = 0;

    m_bHasChanged = true;
}

int Label::GetWidth() const
{
    return m_TextRect.w;
}

int Label::GetHeight() const
{
    return m_TextRect.h;
}

void Label::SetX( int iX )
{
    m_TextRect.x = iX;

    m_bHasChanged = true;
}

void Label::SetY( int iY )
{
    m_TextRect.y = iY;

    m_bHasChanged = true;
}

void Label::Draw()
{
    if( m_Renderer == NULL || m_TextureText == NULL )
    {
        return;
    }

    if( m_bHasChanged )
    {
        SDL_RenderCopy( m_Renderer, m_TextureText, NULL, &m_TextRect );
        m_bHasChanged = false;
    }
}

void Label::SetText( std::string newText, TTF_Font* font, SDL_Color color )
{
    SDL_DestroyTexture( m_TextureText );

    m_bHasChanged = true;

    SDL_Surface* tempSurface = TTF_RenderText_Blended( font, newText.c_str(), color );

    m_TextRect.w = tempSurface->w;
    m_TextRect.h = tempSurface->h;

    m_TextureText = SDL_CreateTextureFromSurface( m_Renderer, tempSurface );

    if( m_TextureText == NULL )
    {
        printf( "Unable to create texture from rendered text \"%s\"! SDL Error: %s\n", newText.c_str(), SDL_GetError() );

        m_TextRect.w = 0;
        m_TextRect.h = 0;
    }

    SDL_FreeSurface( tempSurface );
    tempSurface = NULL;
}
























