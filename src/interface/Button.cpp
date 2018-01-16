#include "Button.h"

SDL_Texture* Button::m_TextureButton = NULL;

Button::Button() : TextField() {
    m_xmlConstants = NULL;

    m_TextureTextPressed = NULL;

    m_bIsPressed = false;
    m_bEnabled = true;
}

Button::~Button() {
    SDL_DestroyTexture( m_TextureTextPressed );
    m_TextureTextPressed = NULL;

    SDL_DestroyTexture( m_TextureButton );
    m_TextureButton = NULL;
}

void Button::Init( pugi::xml_document* pConstants, SDL_Renderer* pNewRenderer ) {
    TextField::Init( pNewRenderer );

    m_xmlConstants = pConstants;

    m_TextureTextPressed = NULL;

    m_bIsPressed = false;
    m_bEnabled = true;

    if( !m_TextureButton ) {
        std::string sSprite = m_xmlConstants->first_child().child( "Button" ).child( "Sprite" ).text().as_string();
        m_TextureButton = IMG_LoadTexture( m_Renderer, sSprite.c_str() );

        if( m_TextureButton == NULL ) {
            printf( "Failed to load TextureBackground! SDL Error: %s\n", IMG_GetError() );
        }
    }
}

void Button::Draw() {
    if( m_Renderer == NULL
        || m_TextureText == NULL
        || m_TextureTextPressed == NULL
        || m_TextureButton == NULL ) {
            return;
    }

    if( m_bHasChanged ) {
        m_bHasChanged = false;

        int iWidth = m_xmlConstants->first_child().child( "Button" ).child( "SpriteWidth" ).text().as_int();
        int iHeight = m_xmlConstants->first_child().child( "Button" ).child( "SpriteHeight" ).text().as_int();

        SDL_Rect tempRect;
        tempRect.w = iWidth;
        tempRect.h = iHeight;
        tempRect.x = 0;

        if( !m_bEnabled ) {
            tempRect.y = iHeight * 2;
        }
        else if( m_bIsPressed ) {
            tempRect.y = iHeight;
        }
        else {
            tempRect.y = 0;
        }

        SDL_RenderCopy( m_Renderer, m_TextureButton, &tempRect, &m_FieldRect );

        m_TextRect.x = m_FieldRect.x + ( m_FieldRect.w - m_TextRect.w ) / 2;
        m_TextRect.y = m_FieldRect.y + ( m_FieldRect.h - m_TextRect.h ) / 2;

        if( m_bIsPressed ) {
            SDL_RenderCopy( m_Renderer, m_TextureTextPressed, NULL, &m_TextRect );
        }
        else {
            SDL_RenderCopy( m_Renderer, m_TextureText, NULL, &m_TextRect );
        }
    }
}

void Button::SetText( std::string newText, TTF_Font* font, SDL_Color color ) {
    Label::SetText( newText, font, color );

    SDL_DestroyTexture( m_TextureTextPressed );

    SDL_Surface* tempSurface = TTF_RenderText_Blended( font, newText.c_str(), {0xFF, 0xFF, 0xFF, 0xFF} );

    m_TextureTextPressed = SDL_CreateTextureFromSurface( m_Renderer, tempSurface );

    if( m_TextureTextPressed == NULL ) {
        printf( "Unable to create texture from rendered text \"%s\"! SDL Error: %s\n", newText.c_str(), SDL_GetError() );
    }

    SDL_FreeSurface( tempSurface );
    tempSurface = NULL;
}

bool Button::IsIn( int iX, int iY ) const {
    if( iX < m_FieldRect.x || iX > ( m_FieldRect.x + m_FieldRect.w ) ) {
        return false;
    }
    else if( iY < m_FieldRect.y || iY > ( m_FieldRect.y + m_FieldRect.h ) ) {
        return false;
    }

    return true;
}

void Button::Enable() {
    m_bEnabled = true;
    m_bHasChanged = true;
}

void Button::Disable() {
    m_bEnabled = false;
    m_bHasChanged = true;
}

void Button::Press() {
    if( m_bEnabled ) {
        m_bIsPressed = true;
        m_bHasChanged =  true;
    }
}

void Button::Release() {
    if( m_bEnabled ) {
        m_bIsPressed = false;
        m_bHasChanged = true;
    }
}

bool Button::IsPressed() const {
    return m_bIsPressed;
}