#include "Button.h"

SDL_Texture* Button::buttonTexture = NULL;

Button::Button() : TextField() {
    Init();
}

Button::~Button() {
    Deinit();
}

void Button::Init() {
    textTexturePressed = NULL;

    isPressed = false;
    isEnabled = true;

    fieldRect.x = 0;
    fieldRect.y = 0;
    fieldRect.w = 0;
    fieldRect.h = 0;

    if( NULL == buttonTexture ) {
        std::string sprite = global.GetSettings()->ReadString( "Button", "Sprite" );
        buttonTexture = global.GetScreenController()->LoadTexture( sprite );

        if( NULL == buttonTexture ) {
            printf( "Failed to load TextureBackground! SDL Error: %s\n", IMG_GetError() );
        }
    }
}

void Button::Deinit() {
    global.GetScreenController()->DestroyTexture( textTexturePressed );
    textTexturePressed = NULL;

    global.GetScreenController()->DestroyTexture( buttonTexture );
    buttonTexture = NULL;
}

void Button::Draw() {
    if( NULL == textTexture
        || NULL == textTexturePressed
        || NULL == buttonTexture ) {
            return;
    }

    if( hasChanged ) {
        int width = global.GetSettings()->ReadInt( "Button", "SpriteWidth" );
        int height = global.GetSettings()->ReadInt( "Button", "SpriteHeight" );

        SDL_Rect sourceRect;
        sourceRect.w = width;
        sourceRect.h = height;
        sourceRect.x = 0;

        if( false == isEnabled ) {
            sourceRect.y = height * 2;
        }
        else if( isPressed ) {
            sourceRect.y = height;
        }
        else {
            sourceRect.y = 0;
        }

        global.GetScreenController()->Render( buttonTexture, &sourceRect, &fieldRect );

        if( isPressed ) {
            global.GetScreenController()->Render( textTexturePressed, NULL, &textRect );
        }
        else {
            global.GetScreenController()->Render( textTexture, NULL, &textRect );
        }

        hasChanged = false;
    }
}

void Button::SetText( std::string newText, TTF_Font* font, SDL_Color color ) {
    Label::SetText( newText, font, color );

    global.GetScreenController()->DestroyTexture( textTexturePressed );

    SDL_Surface* tempSurface = global.GetScreenController()->MakeSurfaceFromText( newText, font, {0xFF, 0xFF, 0xFF, 0xFF} );

    textTexturePressed = global.GetScreenController()->MakeTextureFromSurface( tempSurface );

    if( NULL == textTexturePressed ) {
        printf( "Unable to create texture from rendered text \"%s\"! SDL Error: %s\n", newText.c_str(), SDL_GetError() );
    }

    global.GetScreenController()->DestroySurface( tempSurface );
    tempSurface = NULL;
}

bool Button::IsIn( int x, int y ) const {
    if( x < fieldRect.x || x > ( fieldRect.x + fieldRect.w ) ) {
        return false;
    }
    else if( y < fieldRect.y || y > ( fieldRect.y + fieldRect.h ) ) {
        return false;
    }

    return true;
}

void Button::Enable() {
    isEnabled = true;
    hasChanged = true;
}

void Button::Disable() {
    isEnabled = false;
    hasChanged = true;
}

void Button::Press() {
    if( isEnabled ) {
        isPressed = true;
        hasChanged =  true;
    }
}

void Button::Release() {
    if( isEnabled ) {
        isPressed = false;
        hasChanged = true;
    }
}

bool Button::IsPressed() const {
    return isPressed;
}