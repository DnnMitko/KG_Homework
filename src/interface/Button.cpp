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
        std::string sprite = Settings.ReadString( "Button", "Sprite" );
        buttonTexture = ScreenController.LoadTexture( sprite );

        if( NULL == buttonTexture ) {
            printf( "Failed to load TextureBackground! SDL Error: %s\n", IMG_GetError() );
        }
    }
}

void Button::Deinit() {
    ScreenController.DestroyTexture( textTexturePressed );
    textTexturePressed = NULL;

    ScreenController.DestroyTexture( buttonTexture );
    buttonTexture = NULL;
}

void Button::Draw() {
    if( NULL == textTexture
        || NULL == textTexturePressed
        || NULL == buttonTexture ) {
            return;
    }

    if( hasChanged ) {
        int width = Settings.ReadInt( "Button", "SpriteWidth" );
        int height = Settings.ReadInt( "Button", "SpriteHeight" );

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

        ScreenController.Render( buttonTexture, sourceRect, fieldRect );

        if( isPressed ) {
            ScreenController.Render( textTexturePressed, NULL, textRect );
        }
        else {
            ScreenController.Render( textTexture, NULL, textRect );
        }

        hasChanged = false;
    }
}

void Button::SetText( std::string newText, TTF_Font* font, SDL_Color color ) {
    Label::SetText( newText, font, color );

    ScreenController.DestroyTexture( textTexturePressed );

    SDL_Surface* tempSurface = ScreenController.MakeSurfaceFromText( newText, font, {0xFF, 0xFF, 0xFF, 0xFF} );

    textTexturePressed = ScreenController.MakeTextureFromSurface( tempSurface );

    if( NULL == textTexturePressed ) {
        printf( "Unable to create texture from rendered text \"%s\"! SDL Error: %s\n", newText.c_str(), SDL_GetError() );
    }

    ScreenController.DestroySurface( tempSurface );
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