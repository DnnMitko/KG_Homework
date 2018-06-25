#ifndef __SDL_WRAPPER_H__
#define __SDL_WRAPPER_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <cstdio>

#include "../pugixml/XML_Wrapper.h"

class SDL_Wrapper {
public:
    SDL_Wrapper();
    ~SDL_Wrapper();
public:
    void DestroyTexture( SDL_Texture* );
    void Render( SDL_Texture*, SDL_Rect*, SDL_Rect* );
    SDL_Surface* MakeSurfaceFromText( std::string, TTF_Font*, SDL_Color );
    void DestroySurface( SDL_Surface* );
    SDL_Texture* MakeTextureFromSurface( SDL_Surface* );
    void FillRect( SDL_Rect, Uint8, Uint8, Uint8, Uint8 );
    SDL_Texture* LoadTexture( std::string );
    int PollEvents( SDL_Event* );
    TTF_Font* OpenFont( std::string, int );
    void CloseFont( TTF_Font* );
    void ClearScreen();
    void Present();
private:
    bool Init();
    bool InitSDL();
    bool InitWindow();
    bool InitImage();
    bool InitTTF();

    void Deinit();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif //__SDL_WRAPPER_H__