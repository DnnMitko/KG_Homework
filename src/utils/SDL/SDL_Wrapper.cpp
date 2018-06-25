#include "SDL_Wrapper.h"

SDL_Wrapper::SDL_Wrapper() {
    if( false == Init() ) {
        exit(-1);
    }
}

SDL_Wrapper::~SDL_Wrapper() {
    Deinit();
}

bool SDL_Wrapper::Init() {
    window = NULL;
    renderer = NULL;

    bool hasProblem = false;

    if( false == InitSDL() ) {
        hasProblem = true;
    }
    else {
        hasProblem = false;
        
        SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderClear( renderer );
    }

    return hasProblem;
}

void SDL_Wrapper::Deinit() {
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void SDL_Wrapper::DestroyTexture( SDL_Texture* texture ) {
    SDL_DestroyTexture( texture );
}

void SDL_Wrapper::Render( SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destinationRect ) {
    SDL_RenderCopy( renderer, texture, sourceRect, destinationRect );
}

SDL_Surface* SDL_Wrapper::MakeSurfaceFromText( std::string text, TTF_Font* font, SDL_Color color ) {
    SDL_Surface* surface = TTF_RenderText_Blended( font, text.c_str(), color );

    return surface;
}

void SDL_Wrapper::DestroySurface( SDL_Surface* surface ) {
    SDL_FreeSurface( surface );
}

SDL_Texture* SDL_Wrapper::MakeTextureFromSurface( SDL_Surface* surface ) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );

    return texture;
}

void SDL_Wrapper::FillRect( SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a ) {
    SDL_SetRenderDrawColor( renderer, r, g, b, a );
    SDL_RenderFillRect( renderer, &rect );
}

SDL_Texture* SDL_Wrapper::LoadTexture( std::string textureAddress ) {
    SDL_Texture* texture = IMG_LoadTexture( renderer, textureAddress.c_str() );

    return texture;
}

int SDL_Wrapper::PollEvents( SDL_Event* event ) {
    return SDL_PollEvent( event );
}

TTF_Font* SDL_Wrapper::OpenFont( std::string fontAddress, int fontSize ) {
    TTF_Font* font = TTF_OpenFont( fontAddress.c_str(), fontSize );

    return font;
}

void SDL_Wrapper::CloseFont( TTF_Font* font ) {
    TTF_CloseFont( font );
}

void SDL_Wrapper::ClearScreen() {
    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( renderer );
}

void SDL_Wrapper::Present() {
    SDL_RenderPresent( renderer );
}

bool SDL_Wrapper::InitSDL() {
    bool isSuccessful = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "Couldn't initialize SDL! Error: %s\n", SDL_GetError() );
        isSuccessful = false;
    }
    else {
        if( false == ( InitWindow() && InitImage() && InitTTF() ) ) {
            isSuccessful = false;
        }
    }

    return isSuccessful;
}

bool SDL_Wrapper::InitWindow() {
    bool isSuccessful = true;

    if( false == SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
        printf( "Warning: Linear texture filtering not enabled!\n" );
    }

    int screenHeight = Settings.ReadInt( "ScreenHeight" );
    int screenWidth = Settings.ReadInt( "ScreenWidth" );
    std::string windowName = Settings.ReadString( "WindowName" );

    window = SDL_CreateWindow( windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               screenWidth, screenHeight, SDL_WINDOW_SHOWN );
    if( window == NULL ) {
        printf( "Couldn't create window! Error: %s\n", SDL_GetError() );
        isSuccessful = false;
    }
    else {
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        if( renderer == NULL ) {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            isSuccessful = false;
        }
    }

    return isSuccessful;
}

bool SDL_Wrapper::InitImage() {
    bool isSuccessful = true;
    int flags = IMG_INIT_PNG;

    if( ( IMG_Init( flags ) & flags ) != flags ) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        isSuccessful = false;
    }

    return isSuccessful;
}

bool SDL_Wrapper::InitTTF() {
    bool isSuccessful = true;

    if( TTF_Init() == -1 ) {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        isSuccessful = false;
    }

    return isSuccessful;
}

SDL_Wrapper ScreenController;