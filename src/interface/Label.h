#ifndef __LABEL_H__
#define __LABEL_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Label
{
public:
    Label();
    virtual ~Label();
public:
    void Init( SDL_Renderer* );

    virtual int GetWidth() const;
    virtual int GetHeight() const;

    virtual void SetX( int );
    virtual void SetY( int );

    virtual void Draw();

    virtual void SetText( std::string, TTF_Font*, SDL_Color );
protected:
    SDL_Renderer* m_Renderer;
    
    SDL_Rect m_TextRect;
    SDL_Texture* m_TextureText;

    bool m_bHasChanged;
};

#endif //__LABEL_H__