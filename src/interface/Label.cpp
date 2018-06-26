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
    screenController.getInstance()->DestroyTexture( textTexture );
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
        screenController.getInstance()->Render( textTexture, NULL, &textRect );
        hasChanged = false;
    }
}

void Label::SetText( std::string newText, TTF_Font* font, SDL_Color color ) {
    screenController.getInstance()->DestroyTexture( textTexture );

    SDL_Surface* tempSurface = screenController.getInstance()->MakeSurfaceFromText( newText, font, color );

    textRect.w = tempSurface->w;
    textRect.h = tempSurface->h;

    textTexture = screenController.getInstance()->MakeTextureFromSurface( tempSurface );

    hasChanged = true;

    screenController.getInstance()->DestroySurface( tempSurface );
    tempSurface = NULL;
}
























