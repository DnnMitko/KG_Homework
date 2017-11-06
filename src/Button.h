#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <SDL2/SDL_image.h>
#include "TextField.h"

class Button: public TextField
{
public:
    Button();
    virtual ~Button();
public:
    void Init( SDL_Renderer* );
    
    void Draw();

    void SetText( std::string, TTF_Font*, SDL_Color );

    bool IsIn( int, int ) const;

    void Enable();
    void Disable();

    void Press();
    void Release();
    bool IsPressed() const;
private:
    bool m_bIsPressed;
    bool m_bEnabled;

    SDL_Texture* m_TextureTextPressed;
    static SDL_Texture* m_TextureButton;
};

#endif //__BUTTON_H__