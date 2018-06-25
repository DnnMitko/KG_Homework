#include "Label.h"

Label::Label() {
    Init();
}

Label::~Label() {
    Deinit();
}

void Label::Init() {
    textTexture = NULL;

    textRect.x = 0;
    textRect.y = 0;
    textRect.w = 0;
    textRect.h = 0;

    hasChanged = true;
}

void Label::Deinit() {
    renderTool.getScreenController()->DestroyTexture( textTexture );
    textTexture = NULL;
}

int Label::GetWidth() const {
    return textRect.w;
}

int Label::GetHeight() const {
    return textRect.h;
}

void Label::SetX( int newX ) {
    textRect.x = newX;

    hasChanged = true;
}

void Label::SetY( int newY ) {
    textRect.y = newY;

    hasChanged = true;
}

void Label::Draw() {
    if( NULL == textTexture ) {
        return;
    }

    if( hasChanged ) {
        renderTool.getScreenController()->Render( textTexture, NULL, &textRect );
        hasChanged = false;
    }
}

void Label::SetText( std::string newText, TTF_Font* font, SDL_Color color ) {
    renderTool.getScreenController()->DestroyTexture( textTexture );

    SDL_Surface* tempSurface = renderTool.getScreenController()->MakeSurfaceFromText( newText, font, color );

    textRect.w = tempSurface->w;
    textRect.h = tempSurface->h;

    textTexture = renderTool.getScreenController()->MakeTextureFromSurface( tempSurface );

    if( NULL == textTexture ) {
        printf( "Unable to create texture from rendered text \"%s\"! SDL Error: %s\n", newText.c_str(),
                                                                                       SDL_GetError() );

        textRect.w = 0;
        textRect.h = 0;
    }
    else {
        hasChanged = true;
    }

    renderTool.getScreenController()->DestroySurface( tempSurface );
    tempSurface = NULL;
}
























