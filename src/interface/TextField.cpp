#include "TextField.h"

TextField::TextField() : Label() {
    Init();
}

TextField::~TextField() {
    Deinit();
}

void TextField::Init() {
    fieldRect.x = 0;
    fieldRect.y = 0;
    fieldRect.w = 0;
    fieldRect.h = 0;
}

void TextField::Deinit() {
}

int TextField::GetWidth() const {
    return fieldRect.w;
}

int TextField::GetHeight() const {
    return fieldRect.h;
}

void TextField::SetX( int newX ) {
    fieldRect.x = newX;

    CalculateTextPosition();

    hasChanged = true;
}

void TextField::SetY( int newY ) {
    fieldRect.y = newY;

    CalculateTextPosition();

    hasChanged = true;
}

void TextField::Draw() {
    if( NULL == textTexture ) {
        return;
    }

    if( hasChanged ) {
        ScreenController.FillRect( fieldRect, 0x00, 0x00, 0x00, 0xFF );

        ScreenController.Render( textTexture, NULL, &textRect );

        hasChanged = false;
    }
}

void TextField::SetText( std::string newText, TTF_Font* font, SDL_Color color ) {
    Label::SetText( newText, font, color );

    CalculateTextPosition();
}

void TextField::SetFieldSize( int newW, int newH ) {
    fieldRect.w = newW;
    fieldRect.h = newH;

    CalculateTextPosition();

    hasChanged = true;
}

void TextField::CalculateTextPosition() {
    textRect.x = fieldRect.x + ( fieldRect.w - textRect.w ) / 2;
    textRect.y = fieldRect.y + ( fieldRect.h - textRect.h ) / 2;
}